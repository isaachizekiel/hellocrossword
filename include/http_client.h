#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <curl/curl.h>
#include <string>
#include <iostream>

struct memory {
  char *response;
  size_t size;
};


class HTTPCLient {
private:
  CURL *mCurl;
  CURLcode mResponse;
  
public:
  HTTPCLient() {
    mCurl = curl_easy_init();
    if (!mCurl) printf("error initializing curl\n");    
  }
  
  ~HTTPCLient() {
    if (mCurl) curl_easy_cleanup(mCurl);
  }

  static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *)userp;

    char *ptr = (char *)std::realloc(mem->response, mem->size + realsize +1);
    if (ptr == nullptr) return 0;

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;
    
    return realsize;
  }
  
  void get(const char *request, void *chunk) {
    curl_easy_setopt(mCurl, CURLOPT_URL, request);
    curl_easy_setopt(mCurl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, chunk);
    mResponse = curl_easy_perform(mCurl);
  }
  
};
