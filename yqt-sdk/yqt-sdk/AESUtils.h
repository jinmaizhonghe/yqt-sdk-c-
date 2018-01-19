//
// Created by yp-O2O-7020 on 17/12/19.
//

#ifndef YQT_SDK_AESUTILS_H
#define YQT_SDK_AESUTILS_H
#include<iostream>
#include <string>

using namespace std;

class AESUtils {
public:

    static string AESEncode(const string& key, const string& plaintext);

    static string AESEncode(const string& key, const unsigned char* plaintext, const unsigned len);

    static string AESDecode(const string& key, const string& ciphertext);

    static string AESDecode(const string& key, const unsigned char* ciphertext, const unsigned len);

};


#endif //YQT_SDK_AESUTILS_H
