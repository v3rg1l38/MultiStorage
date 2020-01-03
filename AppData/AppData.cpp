#include "AppData.h"

namespace AppData
{
	AppParams g_AppParams;

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

	AppParams & AppParams::setProp(const TCHAR * propValue, APP_PROPS prop)
	{
		switch (prop)
		{
		case AP_DB_HOST:
			lstrcpyn(_databaseHost, propValue, sizeof(_databaseHost));
			return *this;

		case AP_DB_PORT:
			lstrcpyn(_databasePort, propValue, sizeof(_databasePort));
			return *this;

		case AP_DB_USER:
			lstrcpyn(_databaseUser, propValue, sizeof(_databaseUser));
			return *this;

		case AP_DB_PASSWORD:
			lstrcpyn(_databasePassword, propValue, sizeof(_databasePassword));
			return *this;

		case AP_DB_NAME:
			lstrcpyn(_databaseName, propValue, sizeof(_databaseName));
			return *this;

		case AP_LANG:
			lstrcpyn(_languageFilePath, propValue, sizeof(_languageFilePath));
			return *this;

		default:
			return *this;
		}

		return *this;
	}

	const TCHAR * AppParams::getProp(APP_PROPS prop)
	{
		switch (prop)
		{
		case AP_DB_HOST:
			return _databaseHost;

		case AP_DB_PORT:
			return _databasePort;

		case AP_DB_NAME:
			return _databaseName;

		case AP_DB_USER:
			return _databaseUser;

		case AP_DB_PASSWORD:
			return _databasePassword;

		case AP_LANG:
			return _languageFilePath;

		default:
			return nullptr;
		}

		return nullptr;
	}
}

