#pragma once

#include <cassert>
#include <iostream>
#include <string>

#include <cryptopp/config_int.h>
#include <cryptopp/filters.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>

#include "byteutils.hpp"
#include "xorcipher.hpp"

using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::AES;
using CryptoPP::ECB_Mode;
using namespace std;

inline bytec AES_Block_Decrypt(const bytec& cipher, const bytec& key)
{
    assert(key.size() == AES::DEFAULT_KEYLENGTH);
	CryptoPP::SecByteBlock k((CryptoPP::byte*)key.c_str(), AES::DEFAULT_KEYLENGTH);
    string plain;
    try {
		ECB_Mode<AES>::Decryption decryption(k, k.size());
		StringSource(bytec2String(cipher), true, 
			new StreamTransformationFilter(
				decryption,
				new StringSink(plain),
				StreamTransformationFilter::NO_PADDING
			)
		);
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}
    return string2Bytec(plain);
}

inline bytec AES_CBC_Decrypt(const bytec& cipher, const bytec& key, const bytec& IV)
{
	assert(key.size() == AES::DEFAULT_KEYLENGTH);
	assert(IV.size() == AES::BLOCKSIZE);

	bytec res;
	bytec prevBlock = IV;

	for (auto i=cipher.begin(); i!=cipher.end(); i+=AES::BLOCKSIZE)
	{
		bytec block(i, i+AES::BLOCKSIZE);
		res+=xorBytes(AES_Block_Decrypt(block, key), prevBlock);
		prevBlock = block;
	}

	return res;
}