#pragma once

#include "../Database/Database.h"

class DataManagement : public MySql
{
public:

	std::vector<Product>  getProductList();
	void addProductToDb(const Product & product);
};