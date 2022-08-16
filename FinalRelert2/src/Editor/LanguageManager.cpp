#include <LanguageManager.h>

#include <codecvt>

#include <Conquer.h>

LanguageManager LanguageManager::Current;

bool LanguageManager::Load(const char* file)
{
	class locale_codecvt : public std::codecvt_byname<wchar_t, char, std::mbstate_t>
	{
	public:
		locale_codecvt() : codecvt_byname{ std::locale("").name() } {}
	};
	static std::wstring_convert<locale_codecvt> converter;

	if (TextManagerClass::Load(file))
	{	
		for (auto& item : Texts)
			TranslatedTexts[item.first] = converter.to_bytes(item.second);

		TextManagerClass::Clear();
		return true;
	}
	return false;
}

void LanguageManager::Clear()
{
	TranslatedTexts.clear();
}

const char* LanguageManager::Fetch(const char* label, const char* file, int line)
{
	auto itr = TranslatedTexts.find(label);
	if (itr == TranslatedTexts.end())
	{
		char buffer[0x104] = "MISSING:";
		strcat(buffer, label);
		itr = TranslatedTexts.emplace_hint(itr, label, buffer);
		Log_String("***NO_STRING*** '%s' -> file:%s line:%d\n", label, file, line);
	}
	return itr->second.c_str();
}

const char* LanguageManager::operator[](const char* label)
{
	return Fetch(label);
}