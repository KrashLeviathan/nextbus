#ifndef ROUTE_PARSER_H
# define ROUTE_PARSER_H

# include <string>
# include <vector>
# include <map>
# include "xml_parser.h"
# include "route.h"

# define ATTR_TAG        'a'
# define ATTR_TITLE      'b'
# define ATTR_COLOR      'c'
# define ATTR_OPP_COLOR  'd'

class RouteParser : public XmlParser {
 private:
  Route *tempRoute;
  Stop *tempStop;
  Direction *tempDirection;
  void parse_element_open();
  std::map<char, std::string> *parse_attributes();
  void parse_direction();
  void parse_stop();
  void parse_route();
 public:
  std::vector<Route *> routes;
  RouteParser(std::string &s) : XmlParser(s) {
    tempRoute = NULL;
    tempStop = NULL;
    tempDirection = NULL;
  }
  std::vector<Route *> get_all_routes();
  Route get_route(std::string tag);
  void parse();
};

#endif
