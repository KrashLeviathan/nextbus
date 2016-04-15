#include <iostream>
#include <string>
#include "io.h"
#include "route_parser.h"

void gdb_test(RouteParser parser) {
  // std::cout << parser.routes[0]->to_string() << std::endl;
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

  std::cout << "Done" << std::endl;
  
  return 0;
}
