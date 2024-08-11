#include <string>
#include <iostream>

#include "hex.hpp"
#include "xorcipher.hpp"
#include "byteutils.hpp"

using namespace std;

const string key = "ICE";

int main()
{
    freopen("5.txt", "r", stdin);
    
    istreambuf_iterator<char> begin(cin), end;
    string inp(begin, end);
    
    auto encrypted = repeatingKeyXOR(stringToBytes(inp), stringToBytes(key));
    cout<<hexEncode(encrypted)<<endl;
    // cout<<bytesToString(breakRepeatingKeyXOR(encrypted));
    return 0;
}