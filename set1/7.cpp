#include <iostream>
#include <string>

#include <cryptopp/config_int.h>
#include <cryptopp/filters.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/hex.h>

#include "base64.hpp"
#include "byteutils.hpp"

using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::AES;
using CryptoPP::ECB_Mode;
using namespace std;

int main()
{
    freopen("7.txt", "rb", stdin);
    istreambuf_iterator<char> begin(cin), end;
    string cipher(begin, end);
    cipher = bytesToString(base64Decode(cipher));
	unsigned char key[AES::DEFAULT_KEYLENGTH] = {
        'Y','E','L','L','O','W',' ','S','U','B','M','A','R','I','N','E'
    };
    
    string plain;
    try {
		ECB_Mode<AES>::Decryption decryption(key, sizeof(key));

		StringSource(cipher, true, 
			new StreamTransformationFilter(decryption, new StringSink(plain))
		);
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}
    cout<<plain<<endl;
    
    return 0;
}