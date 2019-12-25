#pragma once
#define UNICODE

#include <Windows.h>
#include <string>

class ClientInfo
{
public:
	std::wstring getName() const { return _name; }
	std::wstring getOib() const { return _oib; }
	std::wstring getAddress() const { return _address; }
	std::wstring getOwner() const { return _owner; }
	std::wstring getIban() const { return _iban; }
	int getDiscount() const { return _discount; }

	friend class ClientBuilder;

private:

	std::wstring _name;
	std::wstring _oib;
	std::wstring _address;
	std::wstring _owner;
	std::wstring _iban;
	int _discount;
};

class ClientBuilder
{
	ClientInfo _cli;

public:
	ClientInfo & client;

	ClientBuilder() : client(_cli) {}

	static ClientBuilder build() { return ClientBuilder::ClientBuilder(); }

	ClientBuilder & name(const std::wstring & name) noexcept;
	ClientBuilder & name(const TCHAR * name) noexcept;
	ClientBuilder & oib(const std::wstring & oib) noexcept;
	ClientBuilder & oib(const TCHAR * oib) noexcept;
	ClientBuilder & iban(const std::wstring & iban) noexcept;
	ClientBuilder & iban(const TCHAR * iban) noexcept;
	ClientBuilder & owner(const std::wstring & owner) noexcept;
	ClientBuilder & owner(const TCHAR * owner) noexcept;
	ClientBuilder & address(const std::wstring & address) noexcept;
	ClientBuilder & address(const TCHAR * address) noexcept;

	operator ClientInfo()
	{
		return std::move(client);
	}
};