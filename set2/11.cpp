#include <iostream>
#include <random>

#include "aes.hpp"
#include "byteutils.hpp"
#include "hex.hpp"

using namespace std;

int main()
{
    bytec msg = string2Bytec("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    bytec key;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> half(1,2);
    uniform_int_distribution<int> fivetoten(5, 10);

    AutoSeededRandomPool prng;
    for (int i=0; i<AES::DEFAULT_KEYLENGTH; i++)
        key += prng.GenerateByte();
    bytec append, prepend;
    for (int i=0; i<fivetoten(mt); i++)
        prepend += prng.GenerateByte();
    for (int i=0; i<fivetoten(mt); i++)
        append += prng.GenerateByte();
    msg = prepend + msg + append;

    cout<<"plain: "<<hexEncode(msg)<<'\n';
    cout<<"key: "<<hexEncode(key)<<'\n';
    bytec res;
    if (half(mt) == 1)
    {
        bytec iv;
        for (int i=0; i<AES::BLOCKSIZE; i++)
            iv += prng.GenerateByte();
        res = AES_CBC_Encrypt(msg, key, iv);
        cout<<"mode: CBC"<<'\n';
        cout<<hexEncode(res)<<endl;
        cout<<"==================="<<endl;
        cout<<bytec2String(AES_CBC_Decrypt(res, key, iv))<<endl;
    }
    else
    {
        res = AES_ECB_Encrypt(msg, key);
        cout<<"mode: ECB"<<'\n';
        cout<<hexEncode(res)<<endl;
        cout<<"==================="<<endl;
        cout<<bytec2String(AES_ECB_Decrypt(res, key))<<endl;
    }
    cout<<"guessed mode: "<<(AES_ECB_Detect(res)?"ECB":"CBC")<<endl;

    return 0;
}