#include "LFU.h"

using namespace std;


std::string LFU::SearchInCache(std::string cc, std::string cn)
{
    std::cout << "In cache...\n";

    //check cache for key
    string key = cn + "," + cc;
    auto it = keyToNode.find(key);//- returns iterator pointing to pair in map

    //key is in cache
    if (it != keyToNode.end())// - end iterator points to invalid 
    {
        //update cache freq
        updateFrequency(it->second);
        //return population
        return it->second->pop;
    }
    //look in csv
    else
    {
        cout << "In csv file...\n";
        string pop = SearchInCSV("world_cities.csv", cc, cn);

        //checks if not found, prevents invalid data in cache
        if (pop == "")
        {
            return pop;
        }

        //if cache is at capacity
        if (keyToNode.size() >= 10)
        {
            // Find the LFU list using minFreq
            auto& lfuList = freqToNodes[minFreq];

            // Remove the oldest entry in the lowest freq list
            Node* toRemove = lfuList.front();
            keyToNode.erase(toRemove->key);
            lfuList.pop_front();
            delete toRemove; // free memory

            // If the list is now empty, erase it from freqToNodes
            if (lfuList.empty())
            {
                freqToNodes.erase(minFreq);
            }
        }

        // add new city to cache
        Node* newNode = new Node(key, pop);         // Create node with freq=1
        freqToNodes[1].push_back(newNode);          // Insert into freq list
        newNode->iter = --freqToNodes[1].end();     // Store iterator for O(1) removal
        keyToNode[key] = newNode;                   // Map key to node
        minFreq = 1;                                // Reset minFreq because new node starts at 1

        return pop;
    }
}

void LFU::updateFrequency(Node* node)
{
    //get frequency and remove from old frequency group
    int freq = node->freq;
    freqToNodes[freq].erase(node->iter);

    //if old frequency group is npow empty, update minFreq
    if (freqToNodes[freq].empty())
    {
        freqToNodes.erase(freq);
        if (minFreq == freq)
        {
            ++minFreq;
        }
    }

    //update frequency and iterator, and add to new group in order
    ++node->freq;
    freqToNodes[node->freq].push_back(node);
    node->iter = --freqToNodes[node->freq].end();
}

void LFU::displayCache()
{
    //display cache:
    std::cout << "Cache:\n";
    std::cout << std::left;
    std::cout << std::setw(25) << "City"
        << std::setw(20) << "Population"
        << std::setw(10) << "Frequency" << "\n";

    for (auto& i : keyToNode)
    {
        std::cout << std::setw(25) << i.second->key
            << std::setw(20) << i.second->pop
            << std::setw(10) << i.second->freq << "\n";
    }

    cout << endl;
}



