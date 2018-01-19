#pragma once

#include<iostream>
#include <string>
#include <stdint.h>
using namespace std;
#include <iomanip>

class StringUtils
{
public:

	//�ַ���ת16����
	static string str_to_hex(const string& str) ;
	//������ת16����
	static string BinToHex(const string &strBin);

	static string hex_to_str(char *ptr,unsigned char *buf,int len);
	//16����ת������
	static string  HexToBin (const string &strHex);
	//GB2312��UTF-8��ת��
	static string  G2U(const char* gb2312);
	//UTF-8��GB2312��ת��
	static string  U2G(const char* utf8);
	
};

