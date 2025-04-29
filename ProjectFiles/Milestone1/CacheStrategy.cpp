#pragma once

#include "CacheStrategy.h"

using namespace std;

std::string CacheStrategy::SearchInCache(std::string cc, std::string cn)
{
    return std::string();
}

string CacheStrategy::SearchInCSV(string filename, string cc, string cn, bool hasHeader)
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

void CacheStrategy::displayCache() {}
