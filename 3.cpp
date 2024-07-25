#include <iostream>
#include <utility>

#include "hex.hpp"
#include "singlekeyxor.hpp"

using namespace std;

int main()
{
    freopen("3.txt", "r", stdin);
    string inp; cin>>inp;
    string s = hexToText(inp);
    pair<int, string> result = breakSingleKeyXOR(s); 
    cout<<result.second<<endl;

    return 0;
}