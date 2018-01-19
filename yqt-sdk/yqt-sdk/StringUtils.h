#pragma once

#include<iostream>
#include <string>
#include <stdint.h>
using namespace std;
#include <iomanip>

class StringUtils
{
public:

	//字符串转16进制
	static string str_to_hex(const string& str) ;
	//二进制转16进制
	static string BinToHex(const string &strBin);

	static string hex_to_str(char *ptr,unsigned char *buf,int len);
	//16进制转二进制
	static string  HexToBin (const string &strHex);
	//GB2312到UTF-8的转换
	static string  G2U(const char* gb2312);
	//UTF-8到GB2312的转换
	static string  U2G(const char* utf8);
	
};

