#include <iostream>
#include <string>

#include "aes.hpp"
#include "base64.hpp"
#include "byteutils.hpp"

using namespace std;

int main()
{
    freopen("7.txt", "rb", stdin);
    istreambuf_iterator<char> begin(cin), end;
    string inp(begin, end);
    bytec cipher = base64Decode(inp);
    bytec key = string2Bytec("YELLOW SUBMARINE");
    cout<<bytec2String(AES_ECB_Decrypt(cipher, key))<<endl;
    
    return 0;
}