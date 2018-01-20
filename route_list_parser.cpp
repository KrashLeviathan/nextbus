#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "route_list_parser.h"
#include "io.h"

char RouteListParser::key_from_string(std::string *str) {
  if (!str->compare("tag")) {
    return ATTR_ROUTE_TAG;
  } else if (!str->compare("title")) {
    return ATTR_ROUTE_TITLE;
  } else if (!str->compare("shouldRetry")) {
    // Must have this one
    return ATTR_ERROR_SHOULD_RETRY;
  } else {
    return 'Z';
  }
}

std::string RouteListParser::results() {
  std::stringstream ss;
  int i;

  if (routes.empty()) {
    error("RouteListParser::results()");
  }

  ss << IO_GREEN "ROUTE TITLE                    "
     << "(ROUTE TAG)" IO_NORMAL
     << std::endl << std::endl;
  for (i = 0; i < routes.size(); i++) {
    ss << std::left << std::setw(30) << routes[i]->title
       << std::setw(0) << " (" IO_YELLOW << routes[i]->tag
       << IO_NORMAL ")" << std::endl;
  }
  ss << std::endl
     << IO_GREEN "NOTE: When you get predictions or "
     << "set route/stop variables,"
     << std::endl << "make sure to use the " IO_YELLOW
     << "ROUTE TAG" IO_GREEN "." IO_NORMAL;
  return ss.str();
}

void RouteListParser::parse_route() {
  std::map<char, std::string> *attributeMap;

  tempRouteListing = new RouteListing();

  attributeMap = parse_attributes();
  tempRouteListing->tag = (*attributeMap)[ATTR_ROUTE_TAG];
  tempRouteListing->title = (*attributeMap)[ATTR_ROUTE_TITLE];
  routes.push_back(tempRouteListing);
}

void RouteListParser::element_open_actions() {
  if (!substring.compare("route")) {
    parse_route();
  }
}

void RouteListParser::element_close_actions() {
  // No actions necessary because <route/> is self-closing
}
