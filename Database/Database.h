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
	inline void setPort(const std::string & port) noexcept { _port = ":" + port; }
	inline void setUsername(const std::string & username) noexcept { _username = username; }
	inline void setPassword(const std::string & password) noexcept { _password = password; }
	inline void setHost(const std::string & host) noexcept { _host = "tcp://" + host; }
	inline void setSqlCommand(const std::string & sql) noexcept { _sql = sql; }
	inline void setDbName(const std::string & dbName) noexcept { _dbName = dbName; }
	std::vector<Product> & getProductList() { return _products; }
	void executeQuery();

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