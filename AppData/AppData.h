#pragma once
#define UNICODE

#include <Windows.h>
#include <string>
#include <fstream>

#define APPDATA_FILE L"App.bin"
#define MAX_APP_LENGTH 512

namespace AppData
{
	enum APP_PROPS
	{
		AP_DB_HOST,
		AP_DB_PORT,
		AP_DB_NAME,
		AP_DB_PASSWORD,
		AP_DB_USER,
		AP_LANG
	};

	class AppParams
	{
	public:
		AppParams() {};
		AppParams & setProp(const TCHAR * propValue, APP_PROPS prop);
		const TCHAR * getProp(APP_PROPS prop);

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
	bool saveAppParams(AppParams & appParams);
}