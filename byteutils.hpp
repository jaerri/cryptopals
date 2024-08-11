#pragma once

#include <cassert>

#include <vector>
#include <string>

using namespace std;

inline vector<unsigned char> xorBytes(const vector<unsigned char>& bin1, const vector<unsigned char>& bin2)
{
    assert(bin1.size() == bin2.size());
    vector<unsigned char> res(bin1.size());
    
    for (unsigned long i=0; i<bin1.size(); i++)
        res[i] = bin1[i] ^ bin2[i];
    return res;
}

inline vector<unsigned char> stringToBytes(const string& string)
{
    return vector<unsigned char>(string.begin(), string.end());
}
inline string bytesToString(const vector<unsigned char>& bytes)
{
    return string(bytes.begin(), bytes.end());
}