#pragma once

#include <Always.h>

#include <Pipe.h>
#include <RandomStraw.h>
#include <PKey.h>
#include <BlowPipe.h>

class PKPipe : public Pipe
{
public:
	enum CryptControl
	{
		ENCRYPT,
		DECRYPT
	};

	explicit PKPipe(CryptControl control, RandomStraw& rnd) noexcept;

	CLASS_NOCOPY(PKPipe);
	CLASS_CANMOVE(PKPipe);

	virtual ~PKPipe() override;

	virtual void Put_To(Pipe* pipe) override;
	virtual int Put(const void* source, int slen) override;

	void Key(const PKey* key);

private:
	int Encrypted_Key_Length() const;
	int Plain_Key_Length() const;

private:
	enum 
	{
		BLOWFISH_KEY_SIZE = BlowfishEngine::MAX_KEY_LENGTH,
		MAX_KEY_BLOCK_SIZE = 256		// Maximum size of pk encrypted blowfish key.
	};

	bool IsGettingKey;

	/*
	**	This is the random straw that is needed to generate the
	**	blowfish key.
	*/
	RandomStraw& Rand;
	BlowPipe BF;
	CryptControl Control;
	PKey const* CipherKey;
	char Buffer[MAX_KEY_BLOCK_SIZE];
	int Counter;
	int BytesLeft;
};