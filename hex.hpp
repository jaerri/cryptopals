#pragma once

#include <cstdint>
#include <vector>
#include <string>

using namespace std;

inline vector<uint8_t> hexDecode(const string& hexString)
{
    vector<uint8_t> bytes;
    for (unsigned int i = 0; i < hexString.length(); i += 2) {
        string byteString = hexString.substr(i, 2);
        char byte = (char)stoll(byteString, nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}
inline string hexToText(const string& hexString)
{
    vector<uint8_t> bin = hexDecode(hexString);
    string res;
    for (unsigned long i=0; i<bin.size(); i++)
        res += bin[i];

    return res; 
}
constexpr char hexmap[] = "0123456789abcdef";
inline string hexEncode(const vector<uint8_t>& bytes)
{
    string res;
    for (unsigned long i=0; i<bytes.size(); i++)
    {
        res += hexmap[bytes[i] >> 4];
        res += hexmap[bytes[i] & 0xfu];
    }
    return res;
}