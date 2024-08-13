#include <iostream>
#include <string>

#include "hex.hpp"
#include "byteutils.hpp"

using namespace std;

int main()
{
    freopen("2.txt", "r", stdin);
    string input1, input2; cin>>input1>>input2;
    string bin1 = hexDecode(input1);
    string bin2 = hexDecode(input2);
    string res = xorBytes(bin1, bin2);
    cout<<hexEncode(res)<<endl;
    return 0;
}