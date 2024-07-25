#include <cstdint>
#include <map>
#include <string>
#include <iostream>
#include <utility>

#include "hex.hpp"
#include "xorcipher.hpp"

using namespace std;

int main()
{
    freopen("4.txt", "r", stdin);

    string input;
    multimap<int, pair<string, uint8_t>> results;
    while (getline(cin, input))
        results.insert(breakSingleKeyXOR(hexDecode(input)));
    cout<<results.begin()->second.first;

    return 0;
}