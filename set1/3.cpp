#include <iostream>
#include <utility>
#include <string>

#include "hex.hpp"
#include "xorcipher.hpp"

using namespace std;

int main()
{
    freopen("3.txt", "r", stdin);
    string inp; cin>>inp;
    cout<<breakSingleKeyXOR(hexDecode(inp)).second.first<<endl;

    return 0;
}