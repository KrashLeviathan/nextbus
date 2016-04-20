#include <string>
#include <sstream>
#include <vector>
#include <curl/curl.h>
#include "connection.h"
#include "curlplusplus.h"

std::string agencyList() {
  CURLplusplus client;
  return client.Get("http://webservices.nextbus.com/service/publicXMLFeed?command=agencyList");
}

std::string routeList(const char *agency) {
  CURLplusplus client;
  std::stringstream ss;
  ss << "http://webservices.nextbus.com/service/publicXMLFeed"
     << "?command=routeList&a=" << agency;
  return client.Get(ss.str());
}

std::string routeConfig(const char *agency, const char *optionalRouteTag) {
  CURLplusplus client;
  std::stringstream ss;
  ss << "http://webservices.nextbus.com/service/publicXMLFeed"
     << "?command=routeConfig&a=" << agency;
  if (optionalRouteTag != NULL) {
    ss << "&r=" << optionalRouteTag;
  }
  return client.Get(ss.str());
}

std::string predictions(const char *agency, const char *stopTag) {
  CURLplusplus client;
  std::stringstream ss;
  ss << "http://webservices.nextbus.com/service/publicXMLFeed"
     << "?command=predictions&a=" << agency << "&stopId=" << stopTag;
  return client.Get(ss.str());
}

std::string predictions(const char *agency, const char *stopTag,
			const char *routeTag) {
  CURLplusplus client;
  std::stringstream ss;
  ss << "http://webservices.nextbus.com/service/publicXMLFeed"
     << "?command=predictions&a=" << agency << "&stopId=" << stopTag
     << "&routeTag=" << routeTag;
  return client.Get(ss.str());
}

// TODO: Maybe this can get implemented someday, but not now
std::string predictionsForMultiStops(const char *agency,
			     std::vector<std::string> stopTagVector) {
  CURLplusplus client;
  std::stringstream ss;
  ss << "http://webservices.nextbus.com/service/publicXMLFeed"
     << "?command=predictionsForMultiStops&a=" << agency
     << "&stops=<stop 1>&stops=<stop 2>&stops=<stop3>";
  return client.Get(ss.str());
}

std::string schedule(const char *agency, const char *routeTag) {
  CURLplusplus client;
  std::stringstream ss;
  ss << "http://webservices.nextbus.com/service/publicXMLFeed"
     << "?command=schedule&a=" << agency << "&r=" << routeTag;
  return client.Get(ss.str());
}

// TODO: Maybe this can get implemented someday, but not now
std::string nb_messages(const char *agency, std::vector<std::string *> routeTagVector) {
  CURLplusplus client;
  std::stringstream ss;
  ss << "http://webservices.nextbus.com/service/publicXMLFeed"
     << "?command=messages&a=" << agency
     << "&r=<route tag1>&r=<route tagN>";
  return client.Get(ss.str());
}
