#include "RR.h"

#include <random>

using namespace std;

std::string RR::SearchInCache(std::string cc, std::string cn)
{
    //check map for key
    cout << "In cache(" << cacheList.size() << ")...\n";
    string key = cn + "," + cc;
    auto it = cacheMap.find(key);//- returns iterator pointing to pair in map

    if (it != cacheMap.end())// - end iterator points to invalid 
    {
        return cacheList[it->second].second;
    }
    else
    {
        cout << "In csv file...\n";
        string pop = SearchInCSV("world_cities.csv", cc, cn);

        //checks if not found, prevents invalid data in cache
        if (pop == "")
        {
            return pop;
        }

        //if cache is full, overright new city at random index
        if (cacheList.size() >= 10)
        {
            int index = rand() % cacheList.size();

            // Remove old entry from map
            std::string oldKey = cacheList[index].first;
            cacheMap.erase(oldKey);

            // Overwrite vector slot and update map
            cacheList[index] = { key, pop };
            cacheMap[key] = index;
        }
        else
        {
            // Add to vector and map
            cacheList.push_back({ key, pop });
            cacheMap[key] = cacheList.size() - 1;
        }

        return pop;
    }
}

void RR::displayCache()
{
    //display cache:
    std::cout << "Cache:\n";
    std::cout << std::left;
    std::cout << std::setw(25) << "City"
        << std::setw(20) << "Population" << "\n";

    for (auto& i : cacheList)
    {
        std::cout << std::setw(25) << i.first
            << std::setw(20) << i.second << "\n";
    }

    cout << endl;
}
