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
    SecByteBlock k;
    prng.GenerateBlock(k, AES::DEFAULT_KEYLENGTH);
	// SecByteBlock k((CryptoPP::byte*)key.c_str(), AES::DEFAULT_KEYLENGTH);
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
        res = AES_CBC_Encrypt(msg, k, iv);
        cout<<"mode: CBC"<<'\n';
        cout<<hexEncode(res)<<endl;
        cout<<"==================="<<endl;
        cout<<bytec2String(AES_CBC_Decrypt(res, k, iv))<<endl;
    }
    else
    {
        res = AES_ECB_Encrypt(msg, k);
        cout<<"mode: ECB"<<'\n';
        cout<<hexEncode(res)<<endl;
        cout<<"==================="<<endl;
        cout<<bytec2String(AES_ECB_Decrypt(res, k))<<endl;
    }
    cout<<"guessed mode: "<<(AES_ECB_Detect(res)?"ECB":"CBC")<<endl;

    return 0;
}