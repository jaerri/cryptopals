#pragma once

#include <cassert>
#include <iostream>
#include <string>

#include <cryptopp/config_int.h>
#include <cryptopp/filters.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/hex.h>

using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::AES;
using CryptoPP::ECB_Mode;
using namespace std;

inline string AES_ECB_Decrypt(const string& cipher, const string& key)
{
    assert(key.size() == AES::DEFAULT_KEYLENGTH);
    string plain;
    try {
		ECB_Mode<AES>::Decryption decryption(
            reinterpret_cast<unsigned char*>(const_cast<char*>(key.c_str())),
            key.size()
        );

		StringSource(cipher, true, 
			new StreamTransformationFilter(decryption, new StringSink(plain))
		);
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}
    return plain;
}