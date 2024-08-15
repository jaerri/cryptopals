#pragma once

#include <cassert>
#include <map>
#include <utility>
#include <string>
#include <bitset>

#include "englishness.hpp"
#include "byteutils.hpp"

using namespace std;

inline bytec xorBytes(const bytec& bin1, const bytec& bin2)
{
    assert(bin1.size() == bin2.size());
    bytec res;
    
    for (unsigned long i=0; i<bin1.size(); i++)
        res += bin1[i] ^ bin2[i];
    return res;
}
inline pair<double, pair<string, unsigned char>> breakSingleKeyXOR(bytec ciphertext)
{
    multimap<double, pair<string, unsigned char>> result;
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
inline bytec repeatingKeyXOR(const bytec& bytes, const bytec& key)
{
    bytec res;
    for (unsigned long i=0; i<bytes.size(); i++)
    {
        unsigned char keyc = key[i % (key.size())];
        res.push_back(bytes[i] ^ keyc);
    }
    return res;
}

inline int hammingDistance(const bytec& bin1, const bytec& bin2)
{
    bytec xored = xorBytes(bin1, bin2);
    int result = 0;
    for (unsigned char byte : xored)
        result += static_cast<bitset<8>>(byte).count();
    return result;
}
inline multimap<double, int> findKeysize(const bytec& bytes, unsigned long maxsize)
{
    multimap<double, int> sizeRating;
    for (unsigned long keysize=2; keysize<=min(maxsize, bytes.size()); keysize++)
    {
        double avgscore = -1;
        for (unsigned long j=0; j<=bytes.size()/keysize-1; j+=keysize)
        {
            auto begin = bytes.begin()+j;
            auto end = begin+keysize;
            bytec extract1(begin, end);
            bytec extract2(end, end+keysize);
            double score = (double)hammingDistance(extract1, extract2)/keysize;
            avgscore = avgscore==-1 ? score : (score+avgscore)/2;
        }
        sizeRating.insert({avgscore, keysize});
    }
    // for (const auto& pair : sizeRating)
    //     cout<<pair.second<<" ("<<pair.first<<')'<<endl;
    return sizeRating;
}
inline map<string, bytec> breakRepeatingKeyXOR(const bytec& bytes)
{
    auto keysizes = findKeysize(bytes, 40);

    map<string, bytec> res;
    int count = 0;
    const int tries = 2;
    for (auto it=keysizes.begin(); it!=keysizes.end() && count < tries; it++, count++)
    {
        int keysize = it->second;
        bytec key;
        for (int i=0; i<keysize; i++)
        {
            bytec block;
            for (unsigned long j=i; j<bytes.size(); j+=keysize)
            {
                block.push_back(bytes[j]);
            }
            auto blockResult = breakSingleKeyXOR(block);
            key.push_back((char)blockResult.second.second);
        }
        res.insert({bytec2String(repeatingKeyXOR(bytes, key)), key});
    }
    return res;
}