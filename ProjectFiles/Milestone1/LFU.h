#pragma once

#include "CacheStrategy.h"

#include <unordered_map>

class LFU : public CacheStrategy
{
public:
	std::string SearchInCache(std::string cc, std::string cn) override;
private:
    struct Node {
        std::string key;
        std::string pop;
        int freq;
        std::list<Node*>::iterator iter;

        Node(const std::string& k, std::string& v) : key(k), pop(v), freq(1) {}
    };

    int minFreq;
    std::unordered_map<std::string, Node*> keyToNode;
    std::unordered_map<int, std::list<Node*>> freqToNodes;

    void updateFrequency(Node* node);
    void displayCache() override;
};

