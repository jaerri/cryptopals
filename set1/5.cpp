#include <iostream>
#include <string>

#include "byteutils.hpp"
#include "hex.hpp"
#include "xorcipher.hpp"

using namespace std;

const string key = "ICE";

int main()
{
    freopen("5.txt", "r", stdin);
    
    istreambuf_iterator<char> begin(cin), end;
    string inp(begin, end);
    
    bytec encrypted = repeatingKeyXOR(string2Bytec(inp), string2Bytec(key));
    cout<<hexEncode(encrypted)<<endl;
    // cout<<bytesView(breakRepeatingKeyXOR(encrypted));
    return 0;
}