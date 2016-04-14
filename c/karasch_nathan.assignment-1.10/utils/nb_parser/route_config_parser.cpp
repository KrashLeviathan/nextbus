#include <iostream>
#include "route_config_parser.h"

void *RouteConfigParser::next(const char *type) {
  std::cout << type << std::endl;
  return static_cast<void *>(&text);
}
