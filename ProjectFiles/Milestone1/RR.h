#pragma once

#include "CacheStrategy.h"

#include <unordered_map>
#include <vector>

class RR : public CacheStrategy
{
public:
	std::string SearchInCache(std::string cc, std::string cn) override;
private:
	void displayCache() override;
	std::vector<std::pair<std::string, std::string>> cacheList;
	std::unordered_map<std::string, int> cacheMap;
};

