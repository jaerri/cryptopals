#pragma once
#include <string>

using namespace std;

namespace std { 
    typedef std::basic_string<unsigned char> bytec; // byteContainer
}
inline bytec string2Bytec(const string& string)
{
    return bytec(string.begin(), string.end());
}
inline string bytec2String(const bytec& bytes)
{
    return string(bytes.begin(), bytes.end());
}
