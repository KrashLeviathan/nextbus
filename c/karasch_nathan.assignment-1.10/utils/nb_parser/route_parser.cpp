#include <iostream>
#include <map>
#include <vector>
#include "route_parser.h"
#include "route.h"

static void PRINT(const char *str) {
  std::cout << str << std::endl;
}

void RouteParser::breakpoint() {
  // TODO: Remove me when finished.
  std::cout << substring << std::endl;
}

static char key_from_string(std::string *str) {
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

std::map<char, std::string> *RouteParser::parse_attributes() {
  std::map<char, std::string> *attributeMap = new map<char, std::string>();
  char key;
  bool readingValueString = false;
  
  substring.erase();

  while (index < text->length()) {
    c = (*text)[index++];
    switch (c) {
    case ' ':
      if (!readingValueString) {
	// New attribute coming up
	substring.erase();
      } else {
	// The space is part of a string value
	substring += c;
      }
      break;
    case '=':
      key = key_from_string(&substring);
      break;
    case '"':
      if (readingValueString) {
	(*attributeMap)[key] = substring;
	readingValueString = false;
      } else {
	readingValueString = true;
	substring.erase();
      }
      break;
    case '>':
      // Closing bracket found
      substring.erase();
      return attributeMap;
    default:
      substring += c;
      break;
    }
  }
  std::cout << "ERROR: RouteParser::parse_attributes()" << std::endl;
  return attributeMap;
}

void RouteParser::parse_element_open() {
  substring.erase();
  c = (*text)[index++];
  if (c == '/') {
    // Element closing
    substring.erase();
    while (index < text->length()) {
      c = (*text)[index++];
      // Is it an element we care about?
      if (c == ' ' || c == '>') {
	if (!substring.compare("route")) {
	  // Route complete
	  breakpoint();
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
	substring.erase();
	break;
      } else {
	substring += c;
      }
    }
  } else {
    // Element opening
    substring.erase();
    substring += c;
    while (index < text->length()) {
      c = (*text)[index++];
      // Is it an element we care about?
      if (c == ' ' || c == '>') {
	if (!substring.compare("route")) {
	  parse_route();
	} else if (!substring.compare("stop")) {
	  parse_stop();
	} else if (!substring.compare("direction")) {
	  parse_direction();
	}
	substring.erase();
	break;
      } else {
	substring += c;
      }
    }
  }
}

void RouteParser::parse() {
  while (index < text->length()) {
    c = (*text)[index++];
    if (c == '<') {
      // Found an opening bracket
      parse_element_open();
    }
  }
}
