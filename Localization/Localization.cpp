#include "Localization.h"

const std::wstring Localization::localString(const std::wstring & string)
{
	std::wifstream inFile(L"Language.lang");
	std::wstring line;
	std::wstring retWord = L"";

	if (!inFile.is_open())
		return std::wstring();

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
