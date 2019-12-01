#include "Database.h"

int Database::sendQuery(const std::string & dbPath, 
	std::string & sql, 
	int (__stdcall *fp)(void *, int, char **, char**),
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
		MessageBox(NULL, buffer, "Info", MB_OK);
		sqlite3_close(db);
		return -1;
	}

	rc = sqlite3_exec(db, sql.c_str(), fp, data, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		MessageBox(NULL, zErrMsg, "Error", MB_OK);
		sqlite3_free(zErrMsg);
		return -1;
	}

	sqlite3_close(db);
	return rc;
}
