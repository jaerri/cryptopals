#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <utility>
#include <vector>

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