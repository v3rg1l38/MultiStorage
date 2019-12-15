#include "ClientInfo.h"

ClientBuilder & ClientBuilder::name(const std::string & name) noexcept
{
	_cli._name = name;
	return *this;
}

ClientBuilder & ClientBuilder::oib(const std::string & oib) noexcept
{
	_cli._oib = oib;
	return *this;
}

ClientBuilder & ClientBuilder::iban(const std::string & iban) noexcept
{
	_cli._iban = iban;
	return *this;
}

ClientBuilder & ClientBuilder::owner(const std::string & owner) noexcept
{
	_cli._owner = owner;
	return *this;
}

ClientBuilder & ClientBuilder::address(const std::string & address) noexcept
{
	_cli._address = address;
	return *this;
}
