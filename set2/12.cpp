#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <string>

#include "aes.hpp"
#include "base64.hpp"
#include "byteutils.hpp"
#include "hex.hpp"

using namespace std;

SecByteBlock getKey()
{
    ifstream keyin("12_key.txt");
    string key;
    keyin>>key;
    if (key.empty())
    {
        key = "";
        AutoSeededRandomPool prng;
        for (int i=0; i<AES::DEFAULT_KEYLENGTH; i++)
            key+=prng.GenerateByte();
        
        ofstream keyout("12_key.txt");
        keyout<<key;
        keyout.close();
    }
    return SecByteBlock((CryptoPP::byte*)key.c_str(), AES::DEFAULT_KEYLENGTH);    
}
bool ecb_oracle(const bytec& text, const SecByteBlock& key)
{
    bytec msg = text;

    // random_device rd;
    // mt19937 mt(rd());
    // uniform_int_distribution<int> fivetoten(5, 10);
    // AutoSeededRandomPool prng;

    // bytec append, prepend;
    // for (int i=0; i<fivetoten(mt); i++)
    //     prepend += prng.GenerateByte();
    // for (int i=0; i<fivetoten(mt); i++)
    //     append += prng.GenerateByte();
    // msg = prepend + msg + append;
    // cout<<"plain: "<<hexEncode(msg)<<'\n';
    // cout<<"key: "<<key.data()<<'\n';
    // cout<<"==========================="<<'\n';
    bytec res = AES_ECB_Encrypt(msg, key);
    //cout<<bytec2String(res)<<endl;
    // cout<<hexEncode(res)<<endl;
    bool ecb = AES_ECB_Detect(res);
    // cout<<"guessed mode: "<<(ecb?"ECB":"CBC")<<endl;
    return ecb;
}
int main()
{
    freopen("12.txt", "rb", stdin);
    istreambuf_iterator<char> begin(cin), end;
    string str(begin, end);
    bytec append = base64Decode(str);
    SecByteBlock k = getKey();
	// SecByteBlock k((CryptoPP::byte*)key.c_str(), AES::DEFAULT_KEYLENGTH);

    bytec res;
    bytec teststr;

    unsigned int blksize = AES::BLOCKSIZE;
    for (unsigned int i=1; i<=append.size(); i++)
    {
        unsigned int blkpos = i%blksize;
        // cout<<blkpos<<'\n';
        for (unsigned char c='\n'; c<=126; c++) // all printable chars?
        {        
            bytec probe;
            if (res.size()<blksize) 
            {
                for (unsigned i=0; i<blksize-(res.size()+1); i++) probe+='A';
                if (!res.empty()) probe+=res;
            }
            else probe+=res.substr(res.size()-(blksize-1), blksize-1);
            probe+=c;
            for (unsigned int i=0; i<blksize-blkpos; i++) probe+='A';
            probe+=append;
            // cout<<bytec2String(probe)<<'\n';
            
            if (AES_ECB_Detect(AES_ECB_Encrypt(probe, k))) 
            {
                res+=c;
                // cout<<c<<'\n'<<"===============================\n"; 
                break;
            }
            if (c=='\n') c=31;
        }
    }
    cout<<bytec2String(res)<<endl;
    // cout<<bytec2String(append)<<endl;
    cout<<((res==append)?"corret":"non")<<endl;
    return 0;
}