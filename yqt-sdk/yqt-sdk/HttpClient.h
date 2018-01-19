
//
// Created by pengfei.he on 17/12/19.
//

#ifndef YQT_SDK_HTTPCLIENT_H
#define YQT_SDK_HTTPCLIENT_H
#include <string>
#include <curl/curl.h>

using namespace std;

class HttpClient {
public:
    static CURLcode curl_get_req(const std::string &url, std::string &response);
    static CURLcode curl_post_req(const string &url, const string &postParams, string &response);

};


#endif //YQT_SDK_HTTPCLIENT_H
