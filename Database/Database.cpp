#include "Database.h"

int Database::sendQuery(const std::string & dbPath, 
	std::string & sql, 
	int (__stdcall *fp)(void *, int, char **, char **),
	void * data)
{
	sqlite3 *db;

	int rc;
	char * zErrMsg = nullptr;

	rc = sqlite3_open(dbPath.c_str(), &db);
	if (rc)
	{
		char buffer[MAX_PATH] = "";
		sprintf_s(buffer, MAX_PATH, "Can't open database: %s\n", sqlite3_errmsg(db));
		MessageBoxA(NULL, buffer, "Info", MB_OK);
		sqlite3_close(db);
		return -1;
	}

	rc = sqlite3_exec(db, sql.c_str(), fp, data, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		MessageBoxA(NULL, zErrMsg, "Error", MB_OK);
		sqlite3_free(zErrMsg);
		return -1;
	}

	sqlite3_close(db);
	return rc;
}

std::wstring MySql::convertToWString(const char * string)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(string);
}

std::string MySql::convertToString(const wchar_t * string)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(string);
}

MySql & MySql::setProp(const std::string & propValue, DB_PROPS prop) noexcept
{
	switch (prop)
	{
	case DB_HOST:
	{
		std::string sHost = "tcp://" + propValue;
		_host = sHost;
	}
	return *this;

	case DB_PORT:
	{
		std::string sPort = ":" + propValue;
		_port = sPort;
	}
	return *this;

	case DB_NAME:
		_dbName = propValue;
		return *this;

	case DB_PASSWORD:
		_password = propValue;
		return *this;

	case DB_USER:
		_username = propValue;
		return *this;

	default:
		return *this;
	}

	return *this;
}

inline const std::string MySql::getProp(DB_PROPS prop) noexcept
{
	switch (prop)
	{
	case DB_HOST:
		return _host;

	case DB_PORT:
		return _port;

	case DB_NAME:
		return _dbName;

	case DB_USER:
		return _username;

	case DB_PASSWORD:
		return _password;

	default:
		return std::string();
	}

	return std::string();
}

void MySql::loadDbSettings()
{
	std::string host = convertToString(AppData::g_AppParams.getProp(AppData::APP_PROPS::AP_DB_HOST));
	std::string port = convertToString(AppData::g_AppParams.getProp(AppData::APP_PROPS::AP_DB_PORT));
	std::string user = convertToString(AppData::g_AppParams.getProp(AppData::APP_PROPS::AP_DB_USER));
	std::string db = convertToString(AppData::g_AppParams.getProp(AppData::APP_PROPS::AP_DB_NAME));
	std::string passwd = convertToString(AppData::g_AppParams.getProp(AppData::APP_PROPS::AP_DB_PASSWORD));

	_host = host;
	_port = ":" + port;
	_username = user;
	_dbName = db;
	_password = passwd;
}
