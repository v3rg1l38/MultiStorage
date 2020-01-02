#include "Localization.h"

namespace Localization
{
	std::unordered_map<std::wstring, std::wstring> localization_;

	const TCHAR * getLocalString(const std::wstring & id)
	{
		return localization_[id].c_str();
	}

	bool loadLanguage(const TCHAR * filePath)
	{
		std::wifstream inFile(filePath);

		if (!inFile.is_open())
		{
			MessageBox(NULL, L"Unable to load Language", L"Error: loadLanguage", MB_OK | MB_ICONERROR);
			return false;
		}

		std::wstring line;
		while (std::getline(inFile, line))
		{
			const size_t index = line.find(L"=");
			const std::wstring id = line.substr(0, index);
			const std::wstring localString = line.substr(index + 1, line.length());

			localization_.insert(std::make_pair<std::wstring, std::wstring>(static_cast<std::wstring>(id), 
				static_cast<std::wstring>(localString)));
		 }

		inFile.close();
		return true;
	}
}
