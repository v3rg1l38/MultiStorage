#pragma once
#define UNICODE

#include <Windows.h>
#include <string>
#include <fstream>

#define APPDATA_FILE L"App.bin"
#define MAX_APP_LENGTH 512

namespace AppData
{
	class AppParams
	{
	public:
		AppParams() {};
		AppParams & languageFilePath(const TCHAR * filePath);
		AppParams & databaseHost(const TCHAR * host);
		AppParams & databasePort(const TCHAR * port);
		AppParams & databaseUser(const TCHAR * user);
		AppParams & databaseName(const TCHAR * dbName);
		AppParams & databasePassword(const TCHAR * password);

		inline const TCHAR * getLanguageFilePath() { return _languageFilePath; }
		inline const TCHAR * getDbHost() { return _databaseHost; }
		inline const TCHAR * getDbPort() { return _databasePort; }
		inline const TCHAR * getDbUser() { return _databaseUser; }
		inline const TCHAR * getDbPassword() { return _databasePassword; }
		inline const TCHAR * getDbName() { return _databaseName; }

	private:
		AppParams(const AppParams &) = delete;
		AppParams operator=(const AppParams &) = delete;

		TCHAR _languageFilePath[MAX_APP_LENGTH] = L"";
		TCHAR _databaseHost[MAX_APP_LENGTH] = L"";
		TCHAR _databasePort[MAX_APP_LENGTH] = L"";
		TCHAR _databaseUser[MAX_APP_LENGTH] = L"";
		TCHAR _databaseName[MAX_APP_LENGTH] = L"";
		TCHAR _databasePassword[MAX_APP_LENGTH] = L"";
	};

	extern class AppParams g_AppParams;

	bool loadAppParams(AppParams & appParams);
	bool saveAppParams(AppParams appParams);
}