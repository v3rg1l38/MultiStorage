#pragma once
#define UNICODE

#include <windows.h>
#include <string>
#include <fstream>
#include <unordered_map>

namespace Localization
{
	extern std::unordered_map<std::wstring, std::wstring> localization_;
	const std::wstring localString(const std::wstring & string);
	bool loadLanguage(const TCHAR * filePath);
}