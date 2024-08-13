#include <iostream>
#include <string>

#include "hex.hpp"

using namespace std;

string padPKCS7(string& bytes, int k)
{
    int noOfPads = k - (bytes.size() % k);
    bytes.append(noOfPads, static_cast<char>(noOfPads));
    return bytes;
}

int main()
{
    string inp = "YELLOW SUBMARINE";

    cout<<hexEncode(padPKCS7(inp, 20))<<endl;
    return 0;
}