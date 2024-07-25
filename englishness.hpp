#pragma once

#include <string>
#include <map>

using namespace std;

const map<char, double> englishCharFreq = {
    {'a', 0.0651738}, {'b', 0.0124248}, {'c', 0.0217339},
    {'d', 0.0349835}, {'e', 0.1041440}, {'f', 0.0197881},
    {'g', 0.0158610}, {'h', 0.0492888}, {'i', 0.0558094},
    {'j', 0.0009033}, {'k', 0.0050529}, {'l', 0.0331490},
    {'m', 0.0202124}, {'n', 0.0564513}, {'o', 0.0596302},
    {'p', 0.0137645}, {'q', 0.0008606}, {'r', 0.0497563},
    {'s', 0.0515760}, {'t', 0.0729357}, {'u', 0.0225134},
    {'v', 0.0082903}, {'w', 0.0171272}, {'x', 0.0013692},
    {'y', 0.0145984}, {'z', 0.0007836}, {' ', 0.1918182}
};
inline double englishness(const string& s)
{
    map<char, int> charFreq;
    for (char c : s)
    {
        c = tolower(c);
        if (charFreq[c]) charFreq[c]++;
        else charFreq[c]=1;
    }

    double chi2 = 0;
    for (auto it = charFreq.begin(); it!=charFreq.end(); it++)
    {
        int occurance = it->second;
        double expected;
        auto expectedFreqIt = englishCharFreq.find(it->first);
        if (expectedFreqIt == englishCharFreq.end())
            expected = 0.00001;
        else expected = expectedFreqIt->second * s.size();

        double difference = occurance - expected;
        chi2 += (difference*difference) / expected;
    }

    return chi2;
}
