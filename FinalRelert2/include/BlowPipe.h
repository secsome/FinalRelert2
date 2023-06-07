#pragma once

#include <Always.h>

#include <Pipe.h>
#include <Blowfish.h>

class BlowPipe : public Pipe
{
public:
	enum CryptControl
	{
		ENCRYPT,
		DECRYPT
	};

	explicit BlowPipe(CryptControl control) noexcept;

	CLASS_NOCOPY(BlowPipe);
	CLASS_CANMOVE(BlowPipe);

	virtual ~BlowPipe() override;

	virtual int Flush() override;
	virtual int Put(const void* source, int slen) override;

	void Key(const void* key, int length);

private:
	BlowfishEngine* BF;
	char Buffer[8];
	int Counter;
	CryptControl Control;
};