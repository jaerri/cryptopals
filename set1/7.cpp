#include <iostream>
#include <string>

#include "aes.hpp"
#include "base64.hpp"

using namespace std;

int main()
{
    freopen("7.txt", "rb", stdin);
    istreambuf_iterator<char> begin(cin), end;
    string cipher(begin, end);
    cipher = base64Decode(cipher);
    string key = "YELLOW SUBMARINE";
    cout<<AES_ECB_Decrypt(cipher, key)<<endl;
    
    return 0;
}