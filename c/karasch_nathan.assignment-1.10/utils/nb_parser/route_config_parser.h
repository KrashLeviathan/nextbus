#ifndef ROUTE_CONFIG_PARSER
# define ROUTE_CONFIG_PARSER

# include <string>
# include "xml_parser.h"

class RouteConfigParser : public XmlParser {
 public:
  RouteConfigParser(std::string &s) : XmlParser(s) {}
  void *next(const char *type);
};

#endif
