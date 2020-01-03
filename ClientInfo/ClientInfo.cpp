#include "ClientInfo.h"

ClientBuilder & ClientBuilder::name(const std::wstring & name) noexcept
{
	_cli._name = name;
	return *this;
}

ClientBuilder & ClientBuilder::name(const TCHAR * name) noexcept
{
	_cli._name = name;
	return *this;
}

ClientBuilder & ClientBuilder::oib(const std::wstring & oib) noexcept
{
	_cli._oib = oib;
	return *this;
}

ClientBuilder & ClientBuilder::oib(const TCHAR * oib) noexcept
{
	_cli._oib = oib;
	return *this;
}

ClientBuilder & ClientBuilder::iban(const std::wstring & iban) noexcept
{
	_cli._iban = iban;
	return *this;
}

ClientBuilder & ClientBuilder::iban(const TCHAR * iban) noexcept
{
	_cli._iban = iban;
	return *this;
}

ClientBuilder & ClientBuilder::owner(const std::wstring & owner) noexcept
{
	_cli._owner = owner;
	return *this;
}

ClientBuilder & ClientBuilder::owner(const TCHAR * owner) noexcept
{
	_cli._owner = owner;
	return *this;
}

ClientBuilder & ClientBuilder::address(const std::wstring & address) noexcept
{
	_cli._address = address;
	return *this;
}

ClientBuilder & ClientBuilder::address(const TCHAR * address) noexcept
{
	_cli._address = address;
	return *this;
}

ClientBuilder & ClientBuilder::id(const int & nId) noexcept
{
	_cli._id = nId;
	return *this;
}

ClientBuilder & ClientBuilder::discount(const int & nDiscount) noexcept
{
	_cli._discount = nDiscount;
	return *this;
}
