#pragma once

#include <string>

class Product {
	std::string _code;
	std::string _name;
	std::string _description;
	int _count;
	int _needed;
	int _package;
	float _retailPrice;
	float _wholesalePrice;
	friend class ProductBuilder;

public:
	inline std::string getName() const { return _name; }
	inline std::string getCode() const { return _code; }
	inline std::string getDescription() const { return _description; }
	inline int getCount() const { return _count; }
	inline int getNeeded() const { return _needed; }
	inline int getPackage() const { return _package; }
	inline float getRetailPrice() const { return _retailPrice; }
	inline float getWholesalePrice() const { return _wholesalePrice; }
};

class ProductBuilder
{
	Product _product;
public:
	Product& pr;

	ProductBuilder() : pr(_product) {}

	ProductBuilder & code(const std::string code) noexcept;
	ProductBuilder & name(const std::string & name) noexcept;
	ProductBuilder & count(const int & count) noexcept;
	ProductBuilder & description(const std::string & description) noexcept;
	ProductBuilder & retailPrice(const float & retPrice) noexcept;
	ProductBuilder & wholesalePrice(const float & wPrice) noexcept;
	ProductBuilder & needed(const int & needed) noexcept;
	ProductBuilder & package(const int & package) noexcept;
	static ProductBuilder build() { return ProductBuilder::ProductBuilder(); }

	operator Product()
	{
		return std::move(_product);
	}
};