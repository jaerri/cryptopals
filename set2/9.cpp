#include <iostream>
#include <string>

#include "byteutils.hpp"
#include "hex.hpp"
#include "aes.hpp"

using namespace std;

int main()
{
    bytec inp = string2Bytec("YELLOW SUBMARINE");

    cout<<hexEncode(padPKCS7(inp, 20))<<endl;
    return 0;
}