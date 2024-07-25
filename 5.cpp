#include <string>
#include <iostream>

#include "hex.hpp"
#include "repeatingkeyxor.hpp"
#include "byteutils.hpp"

using namespace std;

const string key = "ICE";

int main()
{
    freopen("5.txt", "r", stdin);
    
    istreambuf_iterator<char> begin(cin), end;
    string inp(begin, end);
    
    auto encrypted = repeatingKeyXOR(stringToBytes(inp), key);
    cout<<hexEncode(encrypted)<<endl;
    breakRepeatingKeyXOR(encrypted);
    return 0;
}