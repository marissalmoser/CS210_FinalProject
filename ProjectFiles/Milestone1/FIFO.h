#pragma once

#include "CacheStrategy.h"

#include <unordered_map>
#include <list>

class FIFO : public CacheStrategy
{
public:
	std::string SearchInCache(std::string cc, std::string cn) override;
private:
	void displayCache() override;
	std::list<std::pair<std::string, std::string>> cacheList;
	std::unordered_map<std::string, std::list<std::pair<std::string, std::string>>::iterator> cacheMap;
};

