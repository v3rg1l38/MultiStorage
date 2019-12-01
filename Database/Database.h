#pragma once

#include <Windows.h>
#include <string>
#include <winsqlite/winsqlite3.h>

class Database
{
public:

private:
	int sendQuery(const std::string & dbPath, 
		std::string & sql, 
		int (__stdcall *fp)(void *, int, char **, char**) = NULL,
		void * data = NULL);
};