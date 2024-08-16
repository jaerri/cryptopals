#pragma once

#include <cassert>
#include <cryptopp/misc.h>
#include <iostream>
#include <string>
#include <set>

#include <cryptopp/secblock.h>
#include <cryptopp/config_int.h>
#include <cryptopp/filters.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include "cryptopp/osrng.h"

#include "byteutils.hpp"
#include "hex.hpp"
#include "xorcipher.hpp"

using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::AutoSeededRandomPool;
using CryptoPP::SecByteBlock;
using CryptoPP::AES;
using CryptoPP::ECB_Mode;
using namespace std;

inline bytec AES_ECB_Encrypt(const bytec& plain, const bytec& key, bool blockMode=false)
{
    assert(key.size() == AES::DEFAULT_KEYLENGTH);
	CryptoPP::SecByteBlock k((CryptoPP::byte*)key.c_str(), AES::DEFAULT_KEYLENGTH);
    string ciphertext;
    try {
		using namespace CryptoPP;
		ECB_Mode<AES>::Encryption encryption(k, k.size());
		StringSource(bytec2String(plain), true, 
			new StreamTransformationFilter(
				encryption,
				new StringSink(ciphertext),
				blockMode ? 
					BlockPaddingSchemeDef::NO_PADDING :
					BlockPaddingSchemeDef::DEFAULT_PADDING
			)
		);
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}
    return string2Bytec(ciphertext);
}
inline bytec AES_ECB_Decrypt(const bytec& cipher, const bytec& key, bool blockMode=false)
{
    assert(key.size() == AES::DEFAULT_KEYLENGTH);
	CryptoPP::SecByteBlock k((CryptoPP::byte*)key.c_str(), AES::DEFAULT_KEYLENGTH);
    string plain;
    try {
		using namespace CryptoPP;
		ECB_Mode<AES>::Decryption decryption(k, k.size());
		StringSource(bytec2String(cipher), true, 
			new StreamTransformationFilter(
				decryption,
				new StringSink(plain),
				blockMode ? 
					BlockPaddingSchemeDef::NO_PADDING :
					BlockPaddingSchemeDef::DEFAULT_PADDING
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

inline bytec padPKCS7(bytec& bytes, int k)
{
    int noOfPads = k - (bytes.size() % k);
    bytes.append(noOfPads, static_cast<char>(noOfPads));
    return bytes;
}

inline bytec AES_CBC_Encrypt(const bytec& plain, const bytec& key, const bytec& IV)
{
	assert(key.size() == AES::DEFAULT_KEYLENGTH);
	assert(IV.size() == AES::BLOCKSIZE);

	bytec res;
	bytec prevBlock = IV;
	bytec padded = plain;
	padded = padPKCS7(padded, AES::BLOCKSIZE);	
	for (unsigned long i=0; i<padded.size(); i+=AES::BLOCKSIZE)
	{
		bytec block = padded.substr(i, AES::BLOCKSIZE);
		bytec cipherblock = AES_ECB_Encrypt(xorBytes(block, prevBlock), key, true);
		res+=cipherblock;
		prevBlock = cipherblock;
	}

	return res;
}
inline bytec AES_CBC_Decrypt(const bytec& cipher, const bytec& key, const bytec& IV)
{
	assert(key.size() == AES::DEFAULT_KEYLENGTH);
	assert(IV.size() == AES::BLOCKSIZE);

	bytec res;
	bytec prevBlock = IV;

	for (unsigned long i=0; i<cipher.size(); i+=AES::BLOCKSIZE)
	{
		bytec block = cipher.substr(i, AES::BLOCKSIZE);
		res+=xorBytes(AES_ECB_Decrypt(block, key, true), prevBlock);
		prevBlock = block;
	}

	return res;
}
inline bool AES_ECB_Detect(const bytec& bytes)
{
	set<bytec> blocks;
	for (unsigned long i=0; i<bytes.size(); i+=AES::BLOCKSIZE)
	{
		bytec block = bytes.substr(i, AES::BLOCKSIZE);
		if (blocks.find(block) == blocks.end()) blocks.insert(block);
		else
		{
			cout<<hexEncode(block)<<endl;
			return true;
		}
	}
	return false;
}