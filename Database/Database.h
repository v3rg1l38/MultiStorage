#pragma once

#include <Windows.h>
#include <string>
#include <winsqlite/winsqlite3.h>

class Database
{
public:

private:
	/*
		dbPath - path of the db file
		sql - sql query
		fp - callback function
	*/
	int sendQuery(const std::string & dbPath, 
		std::string & sql, 
		int (__stdcall *fp)(void *, int, char **, char**) = NULL,
		void * data = NULL);
};