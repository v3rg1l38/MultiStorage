#pragma once
#define UNICODE

#include <Windows.h>
#include <string>
#include <codecvt>
#include <vector>
#include <winsqlite/winsqlite3.h>
#include <mysql/jdbc.h>
#include "../Product/Product.h"
#include "../AppData/AppData.h"

/*
Database Structure

Tables:

Clients ->	client_id int PRIMARY KEY AUTO_INCREMENT NOT NULL
			client_name varchar(30) NOT NULL
			client_oib varchar(20) NOT NULL
			client_iban varchar(20) NOT NULL
			client_discount int NOT NULL
			client_adress varchar(255) NOT NULL

Invoice ->	invoice_id int PRIMARY KEY NOT NULL AUTO_INCREMENT
			invoice_number int NOT NULL
			invoice_buyer int FOREIGN KEY Client.client_id NOT NULL
			invoice_seller int FOREIGN KEY Sellers.seller_id NOT NULL
			invoice_prodList BLOB

Products ->	product_id int PRIMARY KEY AUTO_INCREMENT NOT NULL
			product_name varchar(255) NOT NULL
			product_unit varchar(10) NOT NULL
			product_count int NOT NULL
			product_package int NOT NULL
			product_need int NOT NULL
			product_retailpr decimal(18,2) NOT NULL
			product_wholepr decimal(18,2) NOT NULL
			product_code varchar(30) NOT NULL

Sellers ->	seller_id int PRIMARY KEY AUTO_INCREMENT NOT NULL
			seller_firstName varchar(30) NOT NULL
			seller_lastName varchar(30) NOT NULL
			seller_description text NOT NULL

*/

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

enum DB_PROPS
{
	DB_HOST,
	DB_PORT,
	DB_USER,
	DB_PASSWORD,
	DB_NAME
};

class MySql
{
public:
	MySql() {}
	MySql(const std::string & host, const std::string & username, const std::string & password, const std::string & port)
	{
		_host = "tcp://" + host;
		_port = ":" + port;
		_username = username;
		_password = password;
	}

	std::wstring convertToWString(const char * string);
	std::string convertToString(const wchar_t * string);
	std::vector<Product>  getProductList();
	inline MySql & setProp(const std::string & propValue, DB_PROPS prop) noexcept;
	inline const std::string getProp(DB_PROPS prop) noexcept;
	void loadDbSettings(); // Load settings from loaded AppData

private:
	MySql(const MySql &) = delete;
	MySql & operator=(const MySql &) = delete;

	sql::Driver * _driver;
	sql::Connection * _connection;
	sql::Statement * _statement;
	sql::PreparedStatement * _prepStatement;
	sql::ResultSet * _result;
	std::string _host;
	std::string _username;
	std::string _password;
	std::string _port;
	std::string _sql;
	std::string _dbName;
};