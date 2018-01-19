// yqt-sdk.cpp : 定义控制台应用程序的入口点。
//
/**
-fexec - charset = gbk
-finput - charset = utf-8
**/
#include "stdafx.h"
#include "stdafx.h"
#include "stdafx.h"
#include <string>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <AESUtils.h>
#include <HttpClient.h>
#include <fstream>
#include <string>
#include <cassert>
#include <iostream>
#include <locale>
#include <windows.h>
#include <StringUtils.h>


using namespace std;
using std::cout;
using std::endl;
using std::cin;

int _tmains(int argc, _TCHAR* argv[])
{

	//设置控制台中文乱码
	setlocale(LC_ALL,"chs");
	//商户编号
	string appKey = "10511********069";
	//商户秘钥
	string sercurity = "******";
	//请求地址
	string postUrlStr = "https://api.jia007.com/api-center/rest/v1.0/yqt/consume";
	//请求数据
	rapidjson::Document request_json;
	request_json.SetObject();
	rapidjson::Document::AllocatorType& allocator = request_json.GetAllocator();

	request_json.AddMember("requestNo", "test0000100we912w", allocator);
	request_json.AddMember("merchantNo", "1051100110000070", allocator);
	request_json.AddMember("orderAmount", "0.01", allocator);
	request_json.AddMember("payTool", "WECHAT_SCAN", allocator);
	request_json.AddMember("orderDate", "2018-01-18 16:11:04", allocator);
	request_json.AddMember("productName", "测试产品", allocator);
	request_json.AddMember("serverCallbackUrl", "http://www.qq.com", allocator);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	request_json.Accept(writer);

	string requestStr = buffer.GetString();
	cout<<"请求参数:"+requestStr+"\n"<<endl;
	
	
	string reqstr = AESUtils::AESEncode(sercurity, requestStr);
	string hexSTR = StringUtils::BinToHex(reqstr);

	cout<<"验证加解密方法，反解密参数:"+jiemiSTR+"\n"<<endl;
	string postparams ="&appKey="+appKey+ "&data="+hexSTR;

	cout<<"请求参数URL：:"+postparams+"\n"<<endl;

	string postResponseStr;

	auto res = HttpClient::curl_post_req(postUrlStr, postparams, postResponseStr);
	cout<<"请求返回数据："+postResponseStr+"\n"<<endl;
	
	string results;
	if (res != CURLE_OK)
		cerr << "curl_easy_perform() failed: " + string(curl_easy_strerror(res)) << endl;
	else
		if (postResponseStr.find("code")!= string::npos)
			//由于未请求到业务系统，直接返回未加密字符串
			cout << postResponseStr << endl;
		else
			cout << postResponseStr << endl;
	

	//global release
	curl_global_cleanup();	

	system("pause");
	return 0;


}

