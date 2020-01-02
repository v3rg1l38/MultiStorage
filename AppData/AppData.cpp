#include "AppData.h"

namespace AppData
{
	bool loadAppParams(AppParams & appParams)
	{
		std::wifstream appFile;
		appFile.open(APPDATA_FILE, std::ios::binary | std::ios::in);

		if (!appFile.is_open())
		{
			MessageBox(NULL, L"Unable to load App Data", L"Error: loadAppParams", MB_OK | MB_ICONERROR);
			return false;
		}

		appFile.read(reinterpret_cast<wchar_t*>(&appParams), sizeof(appParams));

		appFile.close();
		return true;
	}

	bool saveAppParams(AppParams appParams)
	{
		std::wofstream appFile;
		appFile.open(APPDATA_FILE, std::ios::binary | std::ios::out);

		if (!appFile.is_open())
		{
			MessageBox(NULL, L"Unable to save App Data", L"Error: saveAppParams", MB_OK | MB_ICONERROR);
			return false;
		}
		appFile.write(reinterpret_cast<wchar_t*>(&appParams), sizeof(appParams));

		appFile.close();
		return true;
	}

	AppParams & AppParams::languageFilePath(const TCHAR * filePath)
	{
		lstrcpyn(_languageFilePath, filePath, sizeof(_languageFilePath));
		return *this;
	}

	AppParams & AppParams::databaseHost(const TCHAR * host)
	{
		lstrcpyn(_databaseHost, host, sizeof(_databaseHost));
		return *this;
	}

	AppParams & AppParams::databasePort(const TCHAR * port)
	{
		lstrcpyn(_databasePort, port, sizeof(_databasePort));
		return *this;
	}

	AppParams & AppParams::databaseUser(const TCHAR * user)
	{
		lstrcpyn(_databaseUser, user, sizeof(_databaseUser));
		return *this;
	}

	AppParams & AppParams::databaseName(const TCHAR * dbName)
	{
		lstrcpyn(_databaseName, dbName, sizeof(_databaseName));
		return *this;
	}

	AppParams & AppParams::databasePassword(const TCHAR * password)
	{
		lstrcpyn(_databasePassword, password, sizeof(_databasePassword));
		return *this;
	}
}

