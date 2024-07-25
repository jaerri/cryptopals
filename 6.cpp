#include <iterator>
#include <string>
#include <iostream>

#include "base64.hpp"
#include "byteutils.hpp"
#include "repeatingkeyxor.hpp"

using namespace std;

int main()
{
    freopen("6.txt", "r", stdin);
    istreambuf_iterator<char> begin(cin), end;
    string input(begin, end);
    auto bytes = base64Decode(input);

    breakRepeatingKeyXOR(bytes);
    return 0;
}