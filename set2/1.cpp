#include "byteutils.hpp"
#include "hex.hpp"
#include <iostream>
#include <string>

using namespace std;

string padPKCS7(string& text, int k)
{
    int noOfPads = k - (text.size() % k);
    text.append(noOfPads, static_cast<char>(noOfPads));
    return text;
}

int main()
{
    string inp = "YELLOW SUBMARINE";

    cout<<hexEncode(stringToBytes(padPKCS7(inp, 20)))<<endl;
    return 0;
}