//
// Created by pengfei.he on 17/12/19.
/**
-fexec - charset = gbk
-finput - charset = utf-8
**/
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <iostream>
#include <iostream>
#include <tchar.h>
#include <fstream>
#include "AESUtils.h"
#include <StringUtils.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <wchar.h>  
using namespace std;

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"libssl.lib")
#pragma comment(lib,"libcrypto.lib")

string AESUtils::AESEncode(const string & key, const string & plaintext)
{
	return  AESEncode(key, (const unsigned char*) plaintext.c_str(), plaintext.size());
}

string AESUtils::AESEncode(const string & key, const unsigned char * plaintext, const unsigned len)
{
	unsigned blockNum = len / AES_BLOCK_SIZE + 1;

    AES_KEY aesKey;
    if (AES_set_encrypt_key((unsigned char *) key.c_str(), key.size() * 8, &aesKey) < 0)
    {
        throw runtime_error("AES_set_encrypt_key failed");
    }

    string ret;
    ret.resize(blockNum * AES_BLOCK_SIZE);
    unsigned char * pResult = (unsigned char *)const_cast<char *>(ret.c_str());

    //encrypt block
    for (unsigned i = 0; i < blockNum - 1; ++i)
    {
        AES_encrypt(plaintext + i * AES_BLOCK_SIZE, pResult + i * AES_BLOCK_SIZE, &aesKey);
    }

    //padding
    unsigned char padBuf[AES_BLOCK_SIZE];
    unsigned remain = len - (blockNum - 1) * AES_BLOCK_SIZE;

    if (remain > 0)
    {
        memcpy(padBuf, plaintext + (blockNum - 1) * AES_BLOCK_SIZE, remain);
        unsigned padVal = AES_BLOCK_SIZE - remain;

        for (unsigned i = 0; i < padVal; ++i)
        {
            padBuf[AES_BLOCK_SIZE - 1 - i] = (unsigned char)padVal;
        }
    }
    else
    {
        memset(padBuf, 0x10, AES_BLOCK_SIZE);
    }

    AES_encrypt(padBuf, pResult + (blockNum - 1) * AES_BLOCK_SIZE, &aesKey);

    return ret;
}

string AESUtils::AESDecode(const string & key, const string & ciphertext)
{
	return AESDecode(key, (const unsigned char*)ciphertext.c_str(), ciphertext.size());
}

string AESUtils::AESDecode(const string & key, const unsigned char * ciphertext, const unsigned len)
{
	unsigned blockNum = len / AES_BLOCK_SIZE;

	if (len != blockNum * AES_BLOCK_SIZE)
	{
		throw runtime_error("ciphertext len wrong");
	}

	if (blockNum == 0)
	{
		return "";
	}

	AES_KEY aesKey;
	if (AES_set_decrypt_key((unsigned char *)key.c_str(), key.size() * 8, &aesKey) < 0)
	{
		throw runtime_error("AES_set_encrypt_key failed");
	}

	string ret;
	ret.resize(blockNum * AES_BLOCK_SIZE);
	unsigned char * pResult = (unsigned char *)const_cast<char *>(ret.c_str());

	//decrypt block
	for (unsigned i = 0; i < blockNum; ++i)
	{
		AES_decrypt(ciphertext + i * AES_BLOCK_SIZE, pResult + i * AES_BLOCK_SIZE, &aesKey);
	}

	//del padding
	unsigned pad = ret[len - 1];

	ret.resize(len - pad);

	return ret;
}

int main(){
	
	 //SetConsoleOutputCP (65001); 
	//设置控制台中文乱码
	setlocale(LC_ALL,"chs");
	string sercurity = "秘钥";
	string postResponseStr = "16进制字符串";
	string str = StringUtils::HexToBin(postResponseStr);
	string result= AESUtils::AESDecode(sercurity, str);

	std::cout << "解密数据："+StringUtils::U2G(result.data()) << std::endl;
	system("pause");
	return 0;

}
