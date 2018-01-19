#include "StdAfx.h"
#include "StringUtils.h"
#include <string>
#include<sstream>
#include<iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdint.h>
#include <windows.h>
using namespace std;


string StringUtils::str_to_hex(const string& str) 
{
	string result="0x";  
    string tmp;  
    stringstream ss;  
    for(int i=0;i<str.size();i++)  
    {  
        ss<<hex<<int(str[i])<<endl;  
        ss>>tmp;  
        result+=tmp;  
    }  
    return result;  
}

//浜岃繘鍒惰浆鍗佸叚杩涘埗
string StringUtils::BinToHex(const string &strBin)
 {
	 bool bIsUpper = true;
     string strHex;
     strHex.resize(strBin.size() * 2);
     for (size_t i = 0; i < strBin.size(); i++)
     {
         uint8_t cTemp = strBin[i];
         for (size_t j = 0; j < 2; j++)
         {
             uint8_t cCur = (cTemp & 0x0f);
             if (cCur < 10)
             {
                 cCur += '0';
             }
             else
             {
                 cCur += ((bIsUpper ? 'A' : 'a') - 10);
             }
             strHex[2 * i + 1 - j] = cCur;
             cTemp >>= 4;
         }
     }
 
     return strHex;
 }

string StringUtils::hex_to_str(char *ptr,unsigned char *buf,int len)  
{  
    for(int i = 0; i < len; i++)  
    {  
        sprintf(ptr, "%02x",buf[i]);  
        ptr += 2;  
    }  
	return ptr;
}  

string StringUtils:: HexToBin(const string &strHex)
 {
     if (strHex.size() % 2 != 0)
     {
         return "";
     }
 
     string strBin;
     strBin.resize(strHex.size() / 2);
     for (size_t i = 0; i < strBin.size(); i++)
     {
         uint8_t cTemp = 0;
         for (size_t j = 0; j < 2; j++)
         {
             char cCur = strHex[2 * i + j];
             if (cCur >= '0' && cCur <= '9')
             {
                 cTemp = (cTemp << 4) + (cCur - '0');
             }
             else if (cCur >= 'a' && cCur <= 'f')
             {
                 cTemp = (cTemp << 4) + (cCur - 'a' + 10);
             }
             else if (cCur >= 'A' && cCur <= 'F')
             {
                 cTemp = (cTemp << 4) + (cCur - 'A' + 10);
             }
             else
             {
                 return "";
             }
         }
         strBin[i] = cTemp;
     }
 
     return strBin;
 }

//GB2312到UTF-8的转换
string StringUtils::G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}
//UTF-8到GB2312的转换
string StringUtils:: U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}