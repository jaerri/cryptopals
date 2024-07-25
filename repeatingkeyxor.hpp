#pragma once

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <bitset>
#include <cstdint>

#include "byteutils.hpp"
#include "singlekeyxor.hpp"

using namespace std;

inline int hammingDistance(const vector<uint8_t>& bin1, const vector<uint8_t>& bin2)
{
    vector<uint8_t> xored = xorBytes(bin1, bin2);
    int result = 0;
    for (uint8_t byte : xored)
        result += static_cast<bitset<8>>(byte).count();
    return result;
}
inline int findKeysize(const vector<uint8_t>& bytes, unsigned long maxsize)
{
    assert(bytes.size()!=0);
    multimap<double, int> sizeRating;
    for (unsigned long keysize=2; keysize<=min(maxsize, bytes.size()); keysize++)
    {
        auto begin = bytes.begin();
        auto second = bytes.begin()+keysize;
        vector<uint8_t> extract1(begin, second);
        vector<uint8_t> extract2(second, second+keysize);
        // for (uint8_t c : extract1)
        //     cout<<c;
        // cout<<endl;
        // for (uint8_t c : extract2)
        //     cout<<c;
        // cout<<endl;

        double score = (double)hammingDistance(extract1, extract2)/keysize;
        sizeRating.insert({score, keysize});
    }
    for (const auto& pair : sizeRating)
        cout<<pair.second<<" ("<<pair.first<<')'<<endl;
    return sizeRating.begin()->second;
}

inline void breakRepeatingKeyXOR(const vector<uint8_t>& bytes)
{
    int keysize = findKeysize(bytes, 40);
    multimap<int, pair<string, uint8_t>> result;

    cout<<keysize<<endl;
    for (int i=0; i<keysize; i++)
    {
        vector<uint8_t> block;
        for (unsigned long j=i; j<bytes.size(); j+=keysize)
        {
            block.push_back(bytes[j]);
        }
        breakSingleKeyXOR(block);
    }
    // for (auto& pair : result)
        // cout<<pair.second.first<<endl<<"==============================================="<<endl;
}

inline vector<uint8_t> repeatingKeyXOR(const vector<uint8_t>& bytes, string key)
{
    vector<uint8_t> res;
    for (unsigned long i=0; i<bytes.size(); i++)
    {
        uint8_t keyc = key[i % (key.size())];
        res.push_back(bytes[i] ^ keyc);
    }
    return res;
}