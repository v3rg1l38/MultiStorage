#pragma once

#include <string>
#include <iostream>

class generic_string
{
	std::string string;

	generic_string(const generic_string & gs) = delete;
	generic_string(const generic_string && gs) = delete;
public:
	generic_string() {}
	generic_string(const std::string& str) : string(str) {}
	generic_string(const char * str) : string(str) {}
	void operator=(const std::string& std);
	void operator=(const char * std);
	friend std::ostream& operator<<(std::ostream& o, const generic_string& gs);
	void to_lowercase();
	void to_uppercase();
};