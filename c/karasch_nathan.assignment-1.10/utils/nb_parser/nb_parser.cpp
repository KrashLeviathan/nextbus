#include <iostream>
#include <string>
#include "io.h"
#include "route_parser.h"

void gdb_test(RouteParser parser) {
  int i;
  for (i = 0; i < parser.routes.size(); i++) {
    std::cout << parser.routes[i]->to_string() << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::string filepath;
  std::string textToParse;

  // Test RouteConfigParser creation
  filepath = get_filepath("routeConfig.xml");
  textToParse = get_file_contents(filepath);
  RouteParser parser (textToParse);
  parser.parse();

  gdb_test(parser);

  return 0;
}
