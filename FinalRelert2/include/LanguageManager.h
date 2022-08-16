#pragma once

#include <Always.h>

#include <TextManager.h>

class LanguageManager : private TextManagerClass
{
public:
	static LanguageManager Current;

	explicit LanguageManager() noexcept = default;

	CLASS_NOCOPY(LanguageManager);
	CLASS_NOMOVE(LanguageManager);

	virtual ~LanguageManager() = default;

	bool Load(const char* file);
	void Clear();

	const char* Fetch(const char* label, const char* file = __FILE__, int line = __LINE__);

	const char* operator[](const char* label);

private:
	std::map<std::string, std::string, labelcomp> TranslatedTexts;
};