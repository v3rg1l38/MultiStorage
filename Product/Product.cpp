#include "Product.h"

ProductBuilder & ProductBuilder::code(const std::wstring & code) noexcept
{
	_product._code = code;
	return *this;
}

ProductBuilder & ProductBuilder::code(const TCHAR * code) noexcept
{
	_product._code = code;
	return *this;
}

ProductBuilder & ProductBuilder::name(const std::wstring & name) noexcept
{
	_product._name = name;
	return *this;
}

ProductBuilder & ProductBuilder::name(const TCHAR * name) noexcept
{
	_product._name = name;
	return *this;
}

ProductBuilder & ProductBuilder::count(const int & count) noexcept
{
	_product._count = count;
	return *this;
}

ProductBuilder & ProductBuilder::description(const std::wstring & description) noexcept
{
	_product._description = description;
	return *this;
}

ProductBuilder & ProductBuilder::description(const TCHAR * description) noexcept
{
	_product._description = description;
	return *this;
}

ProductBuilder & ProductBuilder::retailPrice(const float & retPrice) noexcept
{
	_product._retailPrice = retPrice;
	return *this;
}

ProductBuilder & ProductBuilder::wholesalePrice(const float & wPrice) noexcept
{
	_product._wholesalePrice = wPrice;
	return *this;
}

ProductBuilder & ProductBuilder::needed(const int & needed) noexcept
{
	_product._needed = needed;
	return *this;
}

ProductBuilder & ProductBuilder::package(const int & package) noexcept
{
	_product._package = package;
	return *this;
}
