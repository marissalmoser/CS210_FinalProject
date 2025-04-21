#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <list>

using namespace std;

string SearchInCSV(string filename, string cc, string cn, bool hasHeader = true);
string SearchInCache(string cc, string cn);
void StartSearch(string cc, string cn);
void promptUser();

list<pair<string, string>> cacheList;
unordered_map<string, list<pair<string, string>>::iterator> cacheMap;

int main()
{
    std::cout << "hello!" << endl;
    promptUser();
}

string SearchInCache(string cc, string cn)
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

string SearchInCSV(string filename, string cc, string cn, bool hasHeader)
{
    ifstream file(filename);
    string line, word;
    fstream fout;
    string pop = "";

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return pop;
    }

    //check if first line should be skipped
    if (hasHeader)
    {
        getline(file, line);
    }

    //read file line by line
    while (getline(file, line))
    {
        stringstream ss(line);
        string data;

        //gets country code, checks for match
        getline(ss, data, ',');
        if (data != cc)
        {
            continue;
        }

        //gets city name, checks for match
        getline(ss, data, ',');
        if (data != cn)
        {
            continue;
        }

        //at this point, the country code and city name should match
        getline(ss, pop, ',');
        break;
    }

    file.close();
    return pop;
}

void promptUser()
{
    string cc;
    string cn;

    cout << "--------------------------------------\n"
        "Input a Country Code: \n    ";

    cin >> cc;

    cout <<
        "Input a City Name: \n    ";

    cin.ignore();
    getline(cin, cn);

    cout << "Searching...\n";

    StartSearch(cc, cn);
}

void StartSearch(string cc, string cn)
{
    string pop = SearchInCache(cc, cn);
    
    //validate data
    if (pop == "")
    {
        cout << "City was not found\n";
    }
    else
    {
        cout << "City found with population of " << pop << "\n";
    }
    
    cout << "--------------------------------------\n" << endl;

    promptUser();
}