#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

class CacheStrategy
{
public:
	virtual std::string SearchInCache(std::string cc, std::string cn);
	virtual void displayCache();
protected:
	std::string SearchInCSV(std::string filename, std::string cc, std::string cn, bool hasHeader = true);
};

