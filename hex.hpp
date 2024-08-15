#pragma once

#include <string>
#include "byteutils.hpp"

using namespace std;

inline bytec hexDecode(const string& hexString)
{
    bytec bytes;
    for (unsigned int i = 0; i < hexString.length(); i += 2) {
        string byteString = hexString.substr(i, 2);
        unsigned char byte = (unsigned char)stoll(byteString, nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}
constexpr char hexmap[] = "0123456789abcdef";
inline string hexEncode(const bytec& bytes)
{
    string res;
    for (unsigned long i=0; i<bytes.size(); i++)
    {
        res += hexmap[bytes[i] >> 4];
        res += hexmap[bytes[i] & 0xfu];
    }
    return res;
}