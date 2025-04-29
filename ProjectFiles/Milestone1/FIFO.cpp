#include "FIFO.h"

using namespace std;

std::string FIFO::SearchInCache(std::string cc, std::string cn)
{
    //check map for key
    cout << "In cache(" << cacheList.size() << ")...\n";
    string key = cn + "," + cc;
    auto it = cacheMap.find(key);//- returns iterator pointing to pair in map

    if (it != cacheMap.end())// - end iterator points to invalid 
    {
        //move node to front of list
        cacheList.splice(cacheList.begin(), cacheList, it->second);

        return it->second->second;
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

        //checks size of cache
        if (cacheList.size() >= 10)
        {
            //remove last visited node from list and map
            auto city = cacheList.back();
            cacheMap.erase(city.first);
            cacheList.pop_back();
        }

        //add new city to front of list and add pointer to map
        cacheList.push_front({ key, pop });
        cacheMap[key] = cacheList.begin();
        return pop;
    }
}

void FIFO::displayCache()
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

