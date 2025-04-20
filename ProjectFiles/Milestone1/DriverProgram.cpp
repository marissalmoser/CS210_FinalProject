#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void SearchInCSV(string filename, string cc, string cn, bool hasHeader = true);

struct City
{
    std::string countryCode;
    std::string cityName;
    int population;
};

int main()
{
	std::cout << "hello!";
    SearchInCSV("world_cities.csv", "ad", "encamp");
}

void SearchInCSV(string filename, string cc, string cn, bool hasHeader)
{
    ifstream file(filename);
    string line, word;
    fstream fout;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
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
        string pop;
        getline(ss, pop, ',');
        cout << "City found: " << cc << ", " << cn << ", " << pop << endl;
    }

    file.close();
}