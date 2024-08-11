#include <iterator>
#include <string>
#include <iostream>

#include "base64.hpp"
#include "byteutils.hpp"
#include "xorcipher.hpp"

using namespace std;

int main()
{
    freopen("6.txt", "r", stdin);
    istreambuf_iterator<char> begin(cin), end;
    string input(begin, end);
    auto bytes = base64Decode(input);

    auto res = breakRepeatingKeyXOR(bytes);
    for (const auto& s : res)
        cout<<"Key: "<<bytesToString(s.second)<<endl<<"------------"<<endl
            <<bytesToString(s.first)<<endl<<"==============="<<endl;
    return 0;
}