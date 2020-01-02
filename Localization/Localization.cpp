#include "Localization.h"

namespace Localization
{
	std::unordered_map<std::wstring, std::wstring> localization_;

	const std::wstring localString(const std::wstring & string)
	{
		std::wifstream inFile(L"Language.lang");
		
		if (!inFile.is_open())
			return std::wstring();
		
		std::wstring line;
		std::wstring retWord = L"";

		while (std::getline(inFile, line))
		{
			size_t index = line.find(L"=");
			std::wstring id = line.substr(0, index);

			if (id == string)
			{
				retWord = line.substr(index + 1, line.length());
				break;
			}
		}

		inFile.close();

		return retWord;
	}

	void loadLanguage(const TCHAR * filePath)
	{
		std::wifstream inFile(filePath);

		if (!inFile.is_open())
		{
			MessageBox(NULL, L"Unable to load Language", L"Error: loadLanguage", MB_OK | MB_ICONERROR);
			return;
		}

		std::wstring line;
		while (std::getline(inFile, line))
		{
			size_t index = line.find(L"=");
			const std::wstring id = line.substr(0, index);
			const std::wstring localString = line.substr(index + 1, line.length());

			localization_.insert(std::make_pair<std::wstring, std::wstring>(static_cast<std::wstring>(id), 
				static_cast<std::wstring>(localString)));
		 }

		inFile.close();
	}
}
