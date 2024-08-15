#include <iterator>
#include <iostream>
#include <string>

#include "base64.hpp"
#include "xorcipher.hpp"
#include "byteutils.hpp"

using namespace std;

int main()
{
    freopen("6.txt", "r", stdin);
    istreambuf_iterator<char> begin(cin), end;
    string input(begin, end);
    auto string = base64Decode(input);
    
    auto res = breakRepeatingKeyXOR(string);
    for (const auto& s : res)
        cout<<"Key: "<<bytec2String(s.second)<<endl<<"------------"<<endl
            <<s.first<<endl<<"==============="<<endl;
    return 0;
}