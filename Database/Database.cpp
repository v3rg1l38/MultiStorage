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

std::vector<Product> MySql::getProductList()
{
	std::vector<Product> products;

	try {
		_driver = get_driver_instance();
		_connection = _driver->connect(_host + _port, _username, _password);
		_connection->setSchema(_dbName);
		
		_statement = _connection->createStatement();
		_result = _statement->executeQuery("SELECT * FROM Products");

		while (_result->next())
		{
			const std::string code = _result->getString("product_code");
			const std::string name = _result->getString("product_name");
			const std::string unit = _result->getString("product_unit");
			const int count = _result->getInt("product_count");
			const int need = _result->getInt("product_need");
			const int package = _result->getInt("product_package");
			const double retailPr = _result->getDouble("product_retailpr");
			const double wholePr = _result->getDouble("product_wholepr");

			Product pr = ProductBuilder::build().code(convertToWString(code.c_str()))
				.name(convertToWString(name.c_str()))
				.count(count)
				.needed(need)
				.package(package)
				.unit(convertToWString(unit.c_str()))
				.retailPrice(retailPr)
				.wholesalePrice(wholePr);
			products.emplace_back(pr);
		}

		delete _result;
		delete _statement;
		delete _connection;

		return products;
	} 
	catch (sql::SQLException & e)
	{
		MessageBoxA(NULL, e.what(), "MySQL Error", MB_OK);
		return std::vector<Product>();
	}
}
