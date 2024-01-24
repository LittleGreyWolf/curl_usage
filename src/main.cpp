#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <iostream>

typedef struct {
    std::string body;
	size_t bodySize;
} stResponse;

typedef struct {
    std::string header;
	size_t headerSize;
} stResponseHeader;

size_t responseBodyCallback(void *ptr, size_t size, size_t nmemb, void *stream) {
    stResponse* pResponse = (stResponse*)stream;
	pResponse->body.append((char*)ptr, size * nmemb);
	pResponse->bodySize = size * nmemb;
	return size * nmemb;
}

size_t responseHeaderCallback(void *ptr, size_t size, size_t nmemb, void *stream){
	stResponseHeader* pResponseHeader = (stResponseHeader*)stream;
	pResponseHeader->header.append((char*)ptr, size * nmemb);
	pResponseHeader->headerSize = size * nmemb;
	return size * nmemb;
}

int main(){
	std::string readBuffer;
	stResponse response;
	stResponseHeader responseHeader;

	// 初始化所有可能的调用
	curl_global_init(CURL_GLOBAL_ALL);

	
	CURL *curl = curl_easy_init();

	// 设置url
	curl_easy_setopt(curl, CURLOPT_URL, "http://182.92.205.179:10088");

	// 设置post请求，不设置或设置为0则为get请求
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	// 设置post请求体
	char postData[1024] = "{\"req\":\"hello\"}";
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);
	// 设置post请求体大小
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(postData));

	// 设置http请求头
	curl_slist* headerList = NULL;
	headerList = curl_slist_append(headerList, "Content-Type: application/json");
	headerList = curl_slist_append(headerList, "flag: libcurl");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);

	// 设置不校验证书，https请求时使用
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

	// 设置回调函数获取响应体数据
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, responseBodyCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&response);

	// 设置回调函数获取响应头数据
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, responseHeaderCallback);
	curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void*)&responseHeader);

	// 超时时间
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);

	// 执行请求
	CURLcode res = curl_easy_perform(curl);

	// 检查错误
	if(res == CURLE_OK){
		// 获取状态码
		int responseCode = 0;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
		std::cout << "code : "<<responseCode << std::endl;

		std::cout << "responseHeader size : "<<responseHeader.headerSize << std::endl;
		std::cout << "responseHeader header : "<<responseHeader.header.c_str() << std::endl;

		std::cout << "response size : "<<response.bodySize << std::endl;
		std::cout << "response body : "<<response.body.c_str() << std::endl;
	}else{
		std::cout<<curl_easy_strerror(res)<<std::endl;
	}

	curl_slist_free_all(headerList);

	// 清理
	curl_easy_cleanup(curl);


	return 0;
}
