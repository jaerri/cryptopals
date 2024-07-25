#include <map>
#include <string>
#include <iostream>

#include "hex.hpp"
#include "singlekeyxor.hpp"

using namespace std;

int main()
{
    freopen("4.txt", "r", stdin);

    string input;
    multimap<int, string> results;
    while (getline(cin, input))
    {
        string text = hexToText(input);
        results.insert(breakSingleKeyXOR(text));
    }
    cout<<results.begin()->second;

    return 0;
}