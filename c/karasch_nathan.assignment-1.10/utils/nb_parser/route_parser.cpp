#include <iostream>
#include <map>
#include <vector>
#include "route_parser.h"
#include "route.h"

char RouteParser::key_from_string(std::string *str) {
  if (!str->compare("tag")) {
    return ATTR_TAG;
  } else if (!str->compare("title")) {
    return ATTR_TITLE;
  } else if (!str->compare("color")) {
    return ATTR_COLOR;
  } else if (!str->compare("oppositeColor")) {
    return ATTR_OPP_COLOR;
  } else {
    return 'Z';
  }
}

void RouteParser::parse_direction() {
  std::map<char, std::string> *attributeMap;

  tempDirection = new Direction();

  attributeMap = parse_attributes();
  tempDirection->tag = (*attributeMap)[ATTR_TAG];
  tempDirection->title = (*attributeMap)[ATTR_TITLE];
}

void RouteParser::parse_stop() {
  std::map<char, std::string> *attributeMap;
  Stop *s;

  tempStop = new Stop();

  attributeMap = parse_attributes();

  if (tempDirection == NULL) {
    tempStop->tag = (*attributeMap)[ATTR_TAG];
    tempStop->title = (*attributeMap)[ATTR_TITLE];
    tempRoute->stops.push_back(*tempStop);
  } else {
    if ((s = tempRoute->find_stop((*attributeMap)[ATTR_TAG])) != NULL) {
      tempDirection->stops.push_back(s);
    }
  }
}

void RouteParser::parse_route() {
  std::map<char, std::string> *attributeMap;

  tempRoute = new Route();

  attributeMap = parse_attributes();
  tempRoute->tag = (*attributeMap)[ATTR_TAG];
  tempRoute->title = (*attributeMap)[ATTR_TITLE];
  tempRoute->color = (*attributeMap)[ATTR_COLOR];
  tempRoute->oppositeColor = (*attributeMap)[ATTR_OPP_COLOR];
}

void RouteParser::element_open_actions() {
  if (!substring.compare("route")) {
    parse_route();
  } else if (!substring.compare("stop")) {
    parse_stop();
  } else if (!substring.compare("direction")) {
    parse_direction();
  }
}

void RouteParser::element_close_actions() {
  if (!substring.compare("route")) {
    // Route complete
    routes.push_back(tempRoute);
  } else if (!substring.compare("stop")) {
    // Stop complete
    std::cout << "ERROR: RouteParser::parse_element_open()"
	      << std::endl;
  } else if (!substring.compare("direction")) {
    // Direction complete
    tempRoute->directions.push_back(*tempDirection);
    tempDirection = NULL;
  }
}
