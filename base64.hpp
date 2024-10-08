#pragma once

#include <stdexcept>
#include <unordered_map>
#include <string>
#include "byteutils.hpp"

using namespace std;

constexpr char base64Table[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "0123456789+/";
inline string base64Encode(bytec bytes)
{
    string result(((bytes.size()+2)/3)*4, '=');
    int accumulator=0, accumulator_size=0, indexpos=0; 

    for (unsigned long i=0; i<bytes.size(); i++)
    {
        accumulator = accumulator << 8 | (bytes[i] & 0xffu);
        accumulator_size += 8;
        while (accumulator_size >= 6)
            result[indexpos++] = base64Table[accumulator>>(accumulator_size-=6) & 0x3fu];
    }
    if (accumulator_size>0)
        result[indexpos++] = base64Table[accumulator<<(6-accumulator_size) & 0x3fu];
    return result;
}
static unordered_map<char, unsigned char> reverseTable;
inline void generateReverseTable()
{
    for (unsigned char c='A'; c<='Z'; c++)
        reverseTable.insert({c, c-'A'});
    for (unsigned char c='a'; c<='z'; c++)
        reverseTable.insert({c, c-'a'+26});
    for (unsigned char c='0'; c<='9'; c++)
        reverseTable.insert({c, c-'0'+52});
    reverseTable.insert({'+', 62});
    reverseTable.insert({'/', 63});
}
inline bytec base64Decode(string data)
{
    if (reverseTable.empty()) generateReverseTable();
    bytec res;
    
    int accumulator=0, accumulator_size=0;
    for (unsigned long i=0; i<data.size(); i++)
    {
        if (data[i] == '=' || data[i] == '\n') continue;
        string error = "not legal base64 char"; error+=data[i];
        if (reverseTable.find(data[i]) == reverseTable.end()) throw runtime_error(error);
        accumulator = (accumulator << 6) | (reverseTable[data[i]] & 0x3fu);
        accumulator_size += 6;
        while (accumulator_size >= 8)
            res.push_back(accumulator >> (accumulator_size-=8) & 0xffu);
    }
    if (accumulator_size>0)
        res.push_back(reverseTable[accumulator<<(8-accumulator_size) & 0xffu]);

    return res;
}