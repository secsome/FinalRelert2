#include "BlowPipe.h"

BlowPipe::BlowPipe(CryptControl control) noexcept
	: BF{ nullptr }
	, Counter{ 0 }
	, Control{ control }
{
}

BlowPipe::~BlowPipe()
{
	delete BF;
	BF = nullptr;
}

int BlowPipe::Flush()
{
	int total = 0;
	if (Counter > 0 && BF != nullptr)
		total += Pipe::Put(Buffer, Counter);
	Counter = 0;
	total += Pipe::Flush();
	return total;
}

int BlowPipe::Put(const void* source, int slen)
{
	if (source == nullptr || slen < 1)
		return Pipe::Put(source, slen);

	if (BF == nullptr)
		return Pipe::Put(source, slen);

	int total = 0;
	if (Counter) 
	{
		int sublen = MIN((int)(sizeof(Buffer) - Counter), slen);
		memmove(&Buffer[Counter], source, sublen);
		Counter += sublen;
		source = ((char*)source) + sublen;
		slen -= sublen;

		if (Counter == sizeof(Buffer)) 
		{
			if (Control == DECRYPT)
				BF->Decrypt(Buffer, sizeof(Buffer), Buffer);
			else
				BF->Encrypt(Buffer, sizeof(Buffer), Buffer);
			total += Pipe::Put(Buffer, sizeof(Buffer));
			Counter = 0;
		}
	}

	while (slen >= sizeof(Buffer)) 
	{
		if (Control == DECRYPT)
			BF->Decrypt(source, sizeof(Buffer), Buffer);
		else
			BF->Encrypt(source, sizeof(Buffer), Buffer);
		total += Pipe::Put(Buffer, sizeof(Buffer));
		source = ((char*)source) + sizeof(Buffer);
		slen -= sizeof(Buffer);
	}

	if (slen > 0)
	{
		memmove(Buffer, source, slen);
		Counter = slen;
	}

	return total;
}

void BlowPipe::Key(void const* key, int length)
{
	if (BF == nullptr)
		BF = new BlowfishEngine;

	if (BF != nullptr)
		BF->Submit_Key(key, length);
}