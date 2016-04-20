#include <string>
#include <sstream>
#include <curl/curl.h>

/**
 * Credit for this class goes to Mark Lakata.
 *   http://stackoverflow.com/users/364818/mark-lakata
 * Found this solution at
 *   http://stackoverflow.com/questions/1011339
 *   /how-do-you-make-a-http-request-with-c
 */
class CURLplusplus {
 private:
  CURL* curl;
  std::stringstream ss;
  long http_code;
 public:
  CURLplusplus() : curl(curl_easy_init()) , http_code(0) {}
  ~CURLplusplus() {
    if (curl) curl_easy_cleanup(curl);
  }
  std::string Get(const std::string& url);
  long GetHttpCode() {
    return http_code;
  }
 private:
  static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
    return static_cast<CURLplusplus*>(userp)->Write(buffer,size,nmemb);
  }
  size_t Write(void *buffer, size_t size, size_t nmemb);
};
