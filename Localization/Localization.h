#pragma once
#define UNICODE

#include <windows.h>
#include <string>
#include <fstream>
#include <unordered_map>
#include <codecvt>
#include <locale>

namespace Localization
{
	extern std::unordered_map<std::wstring, std::wstring> g_Localization;
	const TCHAR * getLocalString(const std::wstring & id);
	bool loadLanguage(const TCHAR * filePath);
}
