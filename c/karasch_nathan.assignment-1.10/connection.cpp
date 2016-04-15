#include <string>
#include <vector>
#include <curl/curl.h>
#include "connection.h"
#include "curlplusplus.h"

std::string agencyList() {
  CURLplusplus client;
  return client.Get("http://webservices.nextbus.com/service/publicXMLFeed?command=agencyList");
}

std::string routeList() {
  CURLplusplus client;
  return client.Get("http://webservices.nextbus.com/service/publicXMLFeed?command=routeList&a=cyride");
}

std::string routeConfig(const char *routeTag) {
  CURLplusplus client;
  return client.Get("http://webservices.nextbus.com/service/publicXMLFeed?command=routeConfig&a=<agency_tag>&r=<route tag>");
}

std::string predictions(const char *stopTag) {
  CURLplusplus client;
  return client.Get("http://webservices.nextbus.com/service/publicXMLFeed?command=predictions&a=<agency_tag>&stopId=<stop id>");
}

std::string predictions(const char *stopTag, const char *routeTag) {
  CURLplusplus client;
  return client.Get("http://webservices.nextbus.com/service/publicXMLFeed?command=predictions&a=<agency_tag>&stopId=<stop id>&routeTag=<route tag>");
}

std::string predictionsForMultiStops(std::vector<std::string> stopTagVector) {
  CURLplusplus client;
  return client.Get("http://webservices.nextbus.com/service/publicXMLFeed?command=predictionsForMultiStops&a=<agency_tag>&stops=<stop 1>&stops=<stop 2>&stops=<stop3>");
}

std::string schedule(const char *routeTag) {
  CURLplusplus client;
  return client.Get("http://webservices.nextbus.com/service/publicXMLFeed?command=schedule&a=<agency_tag>&r=<route_tag>");
}

std::string messages(std::vector<std::string> routeTagVector) {
  CURLplusplus client;
  return client.Get("http://webservices.nextbus.com/service/publicXMLFeed?command=messages&a=<agency tag>&r=<route tag1>&r=<route tagN>");
}
