#include "DataManagement.h"

std::vector<Product> DataManagement::getProductList()
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
			const int id = _result->getInt("product_id");
			const std::string code = _result->getString("product_code");
			const std::string name = _result->getString("product_name");
			const std::string unit = _result->getString("product_unit");
			const int count = _result->getInt("product_count");
			const int need = _result->getInt("product_need");
			const int package = _result->getInt("product_package");
			const double retailPr = _result->getDouble("product_retailpr");
			const double wholePr = _result->getDouble("product_wholepr");

			Product pr = ProductBuilder::build().id(id)
				.code(convertToWString(code.c_str()))
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

void DataManagement::addProductToDb(const Product & product)
{
	try {
		_driver = get_driver_instance();
		_connection = _driver->connect(_host + _port, _username, _password);
		_connection->setSchema(_dbName);

		_prepStatement = _connection->prepareStatement("INSERT INTO Products (product_code, \
		product_name, \
		product_unit, \
		product_count, \
		product_need, \
		product_package, \
		product_retailpr, \
		product_wholepr) \
		VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
		
		_prepStatement->setString(1, convertToString(product.getCCode()));
		_prepStatement->setString(2, convertToString(product.getCName()));
		_prepStatement->setString(3, convertToString(product.getCUnit()));
		_prepStatement->setInt(4, product.getCount());
		_prepStatement->setInt(5, product.getNeeded());
		_prepStatement->setInt(6, product.getPackage());
		_prepStatement->setDouble(7, product.getRetailPrice());
		_prepStatement->setDouble(8, product.getWholesalePrice());

		_prepStatement->execute();
	}
	catch (sql::SQLException & e)
	{
		MessageBoxA(NULL, e.what(), "Mysql Error", MB_OK | MB_ICONERROR);
		return;
	}
}
