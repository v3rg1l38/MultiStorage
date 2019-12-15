#pragma once

#include <string>

class Product {
	std::string _code;
	std::string _name;
	std::string _description;
	int _count;
	float _retailPrice;
	float _wholesalePrice;
	friend class ProductBuilder;

public:
	inline std::string getName() const { return _name; }
	inline std::string getCode() const { return _code; }
	inline std::string getDescription() const { return _description; }
	inline int getCount() const { return _count; }
	inline float getRetailPrice() const { return _retailPrice; }
	inline float getWholesalePrice() const { return _wholesalePrice; }
};

class ProductBuilder
{
	Product _product;
public:
	Product& pr;

	ProductBuilder() : pr(_product) {}

	ProductBuilder& code(const std::string code) noexcept
	{
		_product._code = code;
		return *this;
	}
	ProductBuilder& name(const std::string & name) noexcept 
	{ 
		_product._name = name;
		return *this;
	}
	ProductBuilder& count(const int & count) noexcept
	{
		_product._count = count;
		return *this;
	}
	ProductBuilder& description(const std::string & description) noexcept
	{
		_product._description = description;
		return *this;
	}
	ProductBuilder& retailPrice(const float & retPrice) noexcept
	{
		_product._retailPrice = retPrice;
		return *this;
	}
	ProductBuilder& wholesalePrice(const float & wPrice) noexcept
	{
		_product._wholesalePrice = wPrice;
		return *this;
	}
	
	static ProductBuilder build()
	{
		return ProductBuilder::ProductBuilder();
	}

	operator Product()
	{
		return std::move(_product);
	}
};