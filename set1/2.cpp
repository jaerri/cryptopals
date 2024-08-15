#include <iostream>
#include <string>

#include "hex.hpp"
#include "xorcipher.hpp"
#include "byteutils.hpp"

using namespace std;

int main()
{
    freopen("2.txt", "r", stdin);
    string input1, input2; cin>>input1>>input2;
    bytec bin1 = hexDecode(input1);
    bytec bin2 = hexDecode(input2);
    bytec res = xorBytes(bin1, bin2);
    cout<<hexEncode(res)<<endl;
    return 0;
}