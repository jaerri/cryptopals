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
    vector<unsigned char> bin1 = hexDecode(input1);
    vector<unsigned char> bin2 = hexDecode(input2);
    vector<unsigned char> res = xorBytes(bin1, bin2);
    cout<<hexEncode(res)<<endl;
    return 0;
}