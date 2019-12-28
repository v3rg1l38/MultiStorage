#pragma once
#define UNICODE

#include <Windows.h>
#include <string>

class Product {
public:
	inline std::wstring getName() const { return _name; }
	inline const TCHAR * getCName() const { return _name.c_str(); }
	inline std::wstring getCode() const { return _code; }
	inline const TCHAR * getCCode() const { return _code.c_str(); }
	inline std::wstring getDescription() const { return _description; }
	inline const TCHAR * getCDescription() const { return _description.c_str(); }
	inline int getCount() const { return _count; }
	inline int getNeeded() const { return _needed; }
	inline int getPackage() const { return _package; }
	inline float getRetailPrice() const { return _retailPrice; }
	inline float getWholesalePrice() const { return _wholesalePrice; }

private:

	std::wstring _code;
	std::wstring _name;
	std::wstring _description;
	std::wstring _unit;
	int _count;
	int _needed;
	int _package;
	float _retailPrice;
	float _wholesalePrice;
	friend class ProductBuilder;
};

class ProductBuilder
{
	Product _product;
public:
	Product& pr;

	ProductBuilder() : pr(_product) {}

	ProductBuilder & code(const std::wstring & code) noexcept;
	ProductBuilder & code(const TCHAR * code) noexcept;
	ProductBuilder & name(const std::wstring & name) noexcept;
	ProductBuilder & name(const TCHAR * name) noexcept;
	ProductBuilder & count(const int & count) noexcept;
	ProductBuilder & description(const std::wstring & description) noexcept;
	ProductBuilder & description(const TCHAR * description) noexcept;
	ProductBuilder & retailPrice(const float & retPrice) noexcept;
	ProductBuilder & wholesalePrice(const float & wPrice) noexcept;
	ProductBuilder & needed(const int & needed) noexcept;
	ProductBuilder & package(const int & package) noexcept;
	ProductBuilder & unit(const TCHAR * unit) noexcept;
	ProductBuilder & unit(const std::wstring & unit) noexcept;
	static ProductBuilder build() { return ProductBuilder::ProductBuilder(); }

	operator Product()
	{
		return std::move(_product);
	}
};