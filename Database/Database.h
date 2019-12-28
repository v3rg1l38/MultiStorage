#pragma once
#define UNICODE

#include <Windows.h>
#include <string>
#include <codecvt>
#include <vector>
#include <winsqlite/winsqlite3.h>
#include <mysql/jdbc.h>
#include "../Product/Product.h"

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
		int (__stdcall *fp)(void *, int, char **, char **) = NULL,
		void * data = NULL);
};

class MySql
{
public:
	MySql() {}
	MySql(const sql::SQLString & host, const sql::SQLString & username, const sql::SQLString & password, const sql::SQLString & port)
	{
		_host = "tcp://" + host;
		_port = ":" + port;
		_username = username;
		_password = password;
	}

	std::wstring convertToWString(const char * string);
	std::string convertToString(const wchar_t * string);
	inline MySql & Port(const std::string & port) noexcept { _port = ":" + port; return *this; }
	inline MySql & Username(const std::string & username) noexcept { _username = username; return *this; }
	inline MySql & Password(const std::string & password) noexcept { _password = password; return *this; }
	inline MySql & Host(const std::string & host) noexcept { _host = "tcp://" + host; return *this; }
	inline MySql & SqlCommand(const std::string & sql) noexcept { _sql = sql; return *this; }
	inline MySql & DbName(const std::string & dbName) noexcept { _dbName = dbName; return *this; }
	std::vector<Product> & getProductList() { return _products; }
	void fetchData();

private:
	MySql(const MySql &) = delete;
	MySql & operator=(const MySql &) = delete;

	sql::Driver * _driver;
	sql::Connection * _connection;
	sql::Statement * _statement;
	sql::ResultSet * _result;
	std::string _host;
	std::string _username;
	std::string _password;
	std::string _port;
	std::string _sql;
	std::string _dbName;
	std::vector<Product> _products;
};