#include <cryptopp/config_int.h>
#include <iostream>
#include <string>

#include "aes.hpp"
#include "base64.hpp"
#include "byteutils.hpp"
#include "hex.hpp"

using namespace std;

int main()
{
    freopen("10.txt", "r", stdin);
    istreambuf_iterator<char> begin(cin), end;
    string inp(begin, end);
    bytec cipher = base64Decode(inp);
    // bytec k = string2Bytec("YELLOW SUBMARINE");
    SecByteBlock k(reinterpret_cast<CryptoPP::byte*>(const_cast<char*>("YELLOW SUBMARINE")), AES::DEFAULT_KEYLENGTH);
    bytec IV = hexDecode("00000000000000000000000000000000");
    
    cout<<bytec2String(AES_CBC_Decrypt(cipher, k, IV))<<endl;
    return 0;
}