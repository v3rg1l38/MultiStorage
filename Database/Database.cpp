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

void MySql::executeQuery()
{
	try {
		_driver = get_driver_instance();
		_connection = _driver->connect(_host + _port, _username, _password);
		_connection->setSchema(_dbName);
		
		_statement = _connection->createStatement();
		_result = _statement->executeQuery(_sql);

		while (_result->next())
		{
			_list.emplace_back(_result->getString("Name"));
		}

		delete _result;
		delete _statement;
		delete _connection;
	} 
	catch (sql::SQLException & e)
	{
		MessageBoxA(NULL, e.what(), "MYSQL Error", MB_OK);
	}
}
