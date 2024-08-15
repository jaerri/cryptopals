#include <iostream>
#include <string>

#include "byteutils.hpp"
#include "hex.hpp"

using namespace std;

bytec padPKCS7(bytec& bytes, int k)
{
    int noOfPads = k - (bytes.size() % k);
    bytes.append(noOfPads, static_cast<char>(noOfPads));
    return bytes;
}

int main()
{
    bytec inp = string2Bytec("YELLOW SUBMARINE");

    cout<<hexEncode(padPKCS7(inp, 20))<<endl;
    return 0;
}