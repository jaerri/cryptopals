#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <bitset>
#include <cstdint>

#include "byteutils.hpp"
#include "englishness.hpp"

using namespace std;

inline pair<double, pair<string, uint8_t>> breakSingleKeyXOR(vector<uint8_t> ciphertext)
{
    multimap<double, pair<string, uint8_t>> result;
    for (int key=0; key<256; key++)
    {
        string decodedText;
        for (char c : ciphertext)
            decodedText+=(c^(char)key);
        double score = englishness(decodedText);
        result.insert({score, {decodedText, key}});
    }
    return *result.begin();
}
inline vector<uint8_t> repeatingKeyXOR(const vector<uint8_t>& bytes, const vector<uint8_t>& key)
{
    vector<uint8_t> res;
    for (unsigned long i=0; i<bytes.size(); i++)
    {
        uint8_t keyc = key[i % (key.size())];
        res.push_back(bytes[i] ^ keyc);
    }
    return res;
}

inline int hammingDistance(const vector<uint8_t>& bin1, const vector<uint8_t>& bin2)
{
    vector<uint8_t> xored = xorBytes(bin1, bin2);
    int result = 0;
    for (uint8_t byte : xored)
        result += static_cast<bitset<8>>(byte).count();
    return result;
}
inline multimap<double, int> findKeysize(const vector<uint8_t>& bytes, unsigned long maxsize)
{
    multimap<double, int> sizeRating;
    for (unsigned long keysize=2; keysize<=min(maxsize, bytes.size()); keysize++)
    {
        double avgscore = -1;
        for (unsigned long j=0; j<=bytes.size()/keysize-1; j+=keysize)
        {
            auto begin = bytes.begin()+j;
            auto end = begin+keysize;
            vector<uint8_t> extract1(begin, end);
            vector<uint8_t> extract2(end, end+keysize);
            double score = (double)hammingDistance(extract1, extract2)/keysize;
            avgscore = avgscore==-1 ? score : (score+avgscore)/2;
        }
        sizeRating.insert({avgscore, keysize});
    }
    // for (const auto& pair : sizeRating)
    //     cout<<pair.second<<" ("<<pair.first<<')'<<endl;
    return sizeRating;
}
inline map<vector<uint8_t>, vector<uint8_t>> breakRepeatingKeyXOR(const vector<uint8_t>& bytes)
{
    auto keysizes = findKeysize(bytes, 40);

    map<vector<uint8_t>, vector<uint8_t>> res;
    int count = 0;
    const int tries = 2;
    for (auto it=keysizes.begin(); it!=keysizes.end() && count < tries; it++, count++)
    {
        int keysize = it->second;
        vector<uint8_t> key;
        for (int i=0; i<keysize; i++)
        {
            vector<uint8_t> block;
            for (unsigned long j=i; j<bytes.size(); j+=keysize)
            {
                block.push_back(bytes[j]);
            }
            auto blockResult = breakSingleKeyXOR(block);
            key.push_back((char)blockResult.second.second);
        }
        res.insert({repeatingKeyXOR(bytes, key), key});
    }
    return res;
}