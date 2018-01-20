#ifndef ROUTE_LIST_PARSER_H
# define ROUTE_LIST_PARSER_H

# include <string>
# include <vector>
# include "xml_parser.h"

# define ATTR_ROUTE_TAG           'a'
# define ATTR_ROUTE_TITLE         'b'

class RouteListing {
public:
  std::string tag;
  std::string title;
};

class RouteListParser : public XmlParser {
private:
  RouteListing *tempRouteListing;

  void parse_route();

  void element_open_actions();

  void element_close_actions();

  char key_from_string(std::string *str);

public:
  std::vector<RouteListing *> routes;

  RouteListParser(std::string &s) : XmlParser(s) {
    tempRouteListing = NULL;
  }

  std::string results();
};

#endif
