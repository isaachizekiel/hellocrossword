#include "http_client.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <curl/curl.h>

int main() {
  HTTPCLient hc;
  struct memory chunk = {0};
  hc.get("http://www.bt251.com", &chunk);
  printf("%s\n", chunk.response);

  hc.get("http://www.example.com", &chunk);
  printf("%s\n", chunk.response);
  return 0;
}
