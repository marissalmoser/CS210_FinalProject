#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <list>

#include "CacheStrategy.h"
#include "FIFO.h"
#include "LFU.h"
#include "RR.h"

using namespace std;

void mainMenu();
void promptUser();
void StartSearch(string cc, string cn);

CacheStrategy* cache;

int main()
{
    std::cout << "hello!" << endl;
    mainMenu();
}

void mainMenu()
{
    cout << "------------------------------------\n"
        "Select 1, 2, or 3 to search using cache strategy or 4: \n" <<
        "1. LFU (Least Frequently Used)\n" <<
        "2. FIFO (First-In, First-Out)\n" <<
        "3. Random Replacement\n" <<
        "4. Exit\n" <<
        "------------------------------------\n" << endl;

    int input;
    cin >> input;

    switch (input)
    {
    case 1:
        cout << "You selected (Least Frequently Used).\n" << endl;
        cache = new LFU();
        break;
    case 2:
        cout << "You selected FIFO (First-In, First-Out).\n" << endl;
        cache = new FIFO();
        break;
    case 3:
        cout << "You selected Random Replacement.\n" << endl;
        cache = new RR();
        break;
    default:
        cout << "You selected to exit.\n" << endl;
        return;
    }

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

    cin.ignore();
    getline(cin, cn);

    cout << "Searching...\n";

    StartSearch(cc, cn);
}

void StartSearch(string cc, string cn)
{
    string pop = cache->SearchInCache(cc, cn);
    
    //validate data
    if (pop == "")
    {
        cout << "City was not found\n";
    }
    else
    {
        cout << "City found with population of " << pop << "\n" << endl;
    }

    cache->displayCache();
    
    //cout << "--------------------------------------\n" << endl;

    promptUser();
}