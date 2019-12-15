#pragma once

#include "../Product/Product.h"
#include "../ClientInfo/ClientInfo.h"
#include <string>
#include <vector>

class Invoice
{
	std::vector<Product> _products;
	ClientInfo _client;

public:
	Invoice() {}

	inline void addProductToList(const Product & product) { _products.emplace_back(product); }
	void printInvoice();
};