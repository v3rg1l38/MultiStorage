#include "GenericString.h"

void generic_string::operator=(const std::string& std)
{
	string = std;
}

void generic_string::operator=(const char * std)
{
	string = std;
}


void generic_string::to_lowercase()
{
	for (auto & c : string)
	{
		if (c >= 65 && c <= 90)
			c += 32;
	}
}

void generic_string::to_uppercase()
{
	for (auto & c : string)
	{
		if (c >= 97 && c <= 122)
			c -= 32;
	}
}

std::ostream & operator<<(std::ostream & o, const generic_string & gs)
{
	o << gs.string;
	return o;
}
