#include "PKPipe.h"

PKPipe::PKPipe(CryptControl control, RandomStraw& rnd) noexcept
	: IsGettingKey { true }
	, Rand{ rnd }
	, BF{ (control == ENCRYPT) ? BlowPipe::ENCRYPT : BlowPipe::DECRYPT }
	, Control{ control }
	, CipherKey{ nullptr }
	, Counter{ 0 }
	, BytesLeft{ 0 }
{
}

PKPipe::~PKPipe()
{
}

void PKPipe::Put_To(Pipe* pipe)
{
	if (BF.ChainTo != pipe) 
	{
		if (pipe != nullptr && pipe->ChainFrom != nullptr)
		{
			pipe->ChainFrom->Put_To(nullptr);
			pipe->ChainFrom = nullptr;
		}
		if (BF.ChainTo != nullptr)
			BF.ChainTo->ChainFrom = nullptr;
		BF.ChainTo = pipe;
		if (pipe != nullptr)
			pipe->ChainFrom = &BF;
		BF.ChainFrom = this;
		ChainTo = &BF;
	}
}

void PKPipe::Key(PKey const* key)
{
	if (key == nullptr) 
	{
		Flush();
		IsGettingKey = false;
	}
	CipherKey = key;

	if (CipherKey != nullptr) 
	{
		IsGettingKey = true;
		if (Control == DECRYPT)
			Counter = BytesLeft = Encrypted_Key_Length();
	}
}

int PKPipe::Put(const void* source, int length)
{
	if (source == nullptr || length < 1 || CipherKey == nullptr)
		return Pipe::Put(source, length);

	int total = 0;
	if (IsGettingKey)
	{
		if (Control == ENCRYPT)
		{
			 char buffer[MAX_KEY_BLOCK_SIZE];
			 memset(buffer, '\0', sizeof(buffer));
			 // Rand.Get(buffer, BLOWFISH_KEY_SIZE);
			 unsigned char buf[] =
			 {
				 50, 162, 158, 75, 164, 35, 26, 246,
				 215, 11, 217, 24, 24, 24, 24, 24,
				 24, 24, 24, 24, 24, 24, 24, 24,
				 24, 24, 24, 24, 24, 24, 24, 24,
				 55, 45, 87, 170, 134, 194, 172, 4,
				 244, 84, 186, 187, 187, 187, 187, 187, 
				 187, 187, 187, 187, 187, 187, 187, 187
			 };
			 memcpy(Buffer, buf, BLOWFISH_KEY_SIZE);
			 int didput = CipherKey->Encrypt(buffer, Plain_Key_Length(), Buffer);
			 total += Pipe::Put(Buffer, didput);
			 BF.Key(buffer, BLOWFISH_KEY_SIZE);
			 IsGettingKey = false;
		}
		else
		{
			int toget = (BytesLeft < length) ? BytesLeft : length;
			memmove(&Buffer[Counter - BytesLeft], source, toget);
			length -= toget;
			BytesLeft -= toget;
			source = (char*)source + toget;

			if (BytesLeft == 0)
			{
				char buffer[MAX_KEY_BLOCK_SIZE];
				CipherKey->Decrypt(Buffer, Counter, buffer);
				BF.Key(buffer, BLOWFISH_KEY_SIZE);
				IsGettingKey = false;
			}
		}
	}

	total += Pipe::Put(source, length);
	return total;
}

int PKPipe::Encrypted_Key_Length() const
{
	if (CipherKey == nullptr) 
		return 0;
	return CipherKey->Block_Count(BLOWFISH_KEY_SIZE) * CipherKey->Crypt_Block_Size();
}

int PKPipe::Plain_Key_Length() const
{
	if (CipherKey == nullptr) 
		return 0;
	return CipherKey->Block_Count(BLOWFISH_KEY_SIZE) * CipherKey->Plain_Block_Size();
}
