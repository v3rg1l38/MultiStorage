#pragma once

#include <string>

class ClientInfo
{
	std::string _name;
	std::string _oib;
	std::string _address;
	std::string _owner;
	std::string _iban;

public:
	std::string getName() const { return _name; }
	std::string getOib() const { return _oib; }
	std::string getAddress() const { return _address; }
	std::string getOwner() const { return _owner; }
	std::string getIban() const { return _iban; }

	friend class ClientBuilder;
};

class ClientBuilder
{
	ClientInfo _cli;

public:
	ClientInfo & client;

	ClientBuilder() : client(_cli) {}

	static ClientBuilder build() { return ClientBuilder::ClientBuilder(); }

	ClientBuilder & name(const std::string & name) noexcept;
	ClientBuilder & oib(const std::string & oib) noexcept;
	ClientBuilder & iban(const std::string & iban) noexcept;
	ClientBuilder & owner(const std::string & owner) noexcept;
	ClientBuilder & address(const std::string & address) noexcept;

	operator ClientInfo()
	{
		return std::move(client);
	}
};