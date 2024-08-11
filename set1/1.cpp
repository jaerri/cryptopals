#include <iostream>
#include <string>

#include "hex.hpp"
#include "base64.hpp"

using namespace std;

int main() 
{
    freopen("1.txt", "r", stdin);
    string data_string; cin>>data_string;

    cout<<base64Encode(hexDecode(data_string))<<endl;
    return 0;
}