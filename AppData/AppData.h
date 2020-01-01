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
		AppParams & languageFilePath(const TCHAR * filePath);
		AppParams & databaseHost(const TCHAR * host);
		AppParams & databasePort(const TCHAR * port);
		AppParams & databaseUser(const TCHAR * user);
		AppParams & databaseName(const TCHAR * dbName);
		AppParams & databasePassword(const TCHAR * password);

	private:
		TCHAR _languageFilePath[MAX_APP_LENGTH] = L"";
		TCHAR _databaseHost[MAX_APP_LENGTH] = L"";
		TCHAR _databasePort[MAX_APP_LENGTH] = L"";
		TCHAR _databaseUser[MAX_APP_LENGTH] = L"";
		TCHAR _databaseName[MAX_APP_LENGTH] = L"";
		TCHAR _databasePassword[MAX_APP_LENGTH] = L"";
	};

	void loadAppParams(AppParams & appParams);
	void saveAppParams(AppParams appParams);
}