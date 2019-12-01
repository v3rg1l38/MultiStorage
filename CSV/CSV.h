#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class CSV
{
public:
	static std::string parseData(const std::string & line, const int & column);
	static void loadCount2(const char * filepath);
	static void loadCount15(const char * filepath);
	static void loadName(const char * filepath);
};