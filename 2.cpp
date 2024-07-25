#include <iostream>
#include <string>
#include <vector>

#include "hex.hpp"
#include "byteutils.hpp"

using namespace std;

int main()
{
    freopen("2.txt", "r", stdin);
    string input1, input2; cin>>input1>>input2;
    vector<uint8_t> bin1 = hexDecode(input1);
    vector<uint8_t> bin2 = hexDecode(input2);
    vector<uint8_t> res = xorBytes(bin1, bin2);
    cout<<hexEncode(res)<<endl;
    return 0;
}