#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void SearchInCSV(string filename, string cc, string cn, bool hasHeader = true);
void promptUser();

struct City
{
    std::string countryCode;
    std::string cityName;
    int population;
};

int main()
{
    std::cout << "hello!" << endl;
    promptUser();
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
        cout << "City found with population of " << pop << endl;
        break;
    }

    file.close();
    promptUser();
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

    cin >> cn;

    cout << "Searching...\n";

    SearchInCSV("world_cities.csv", cc, cn);

    cout << "--------------------------------------\n" << endl;
}