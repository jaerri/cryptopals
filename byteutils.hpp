#pragma once

#include <cassert>
#include <cstdint>
#include <vector>
#include <string>

using namespace std;

inline vector<uint8_t> xorBytes(const vector<uint8_t>& bin1, const vector<uint8_t>& bin2)
{
    assert(bin1.size() == bin2.size());
    vector<uint8_t> res(bin1.size());
    
    for (unsigned long i=0; i<bin1.size(); i++)
        res[i] = bin1[i] ^ bin2[i];
    return res;
}

inline vector<uint8_t> stringToBytes(const string& string)
{
    return vector<uint8_t>(string.begin(), string.end());
}
inline string bytesToString(const vector<uint8_t>& bytes)
{
    return string(bytes.begin(), bytes.end());
}