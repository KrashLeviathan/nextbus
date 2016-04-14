#include <iostream>
#include <string>
#include "io.h"
#include "route_config_parser.h"

int main(int argc, char *argv[]) {
  std::string filepath;
  std::string textToParse;

  // Test RouteConfigParser creation
  filepath = get_filepath("routeConfig.xml");
  textToParse = get_file_contents(filepath);
  RouteConfigParser parser (textToParse);
  std::string *voidPointer;
  voidPointer = static_cast<std::string *>(parser.next("Type of object"));
  std::cout << *voidPointer << std::endl;

  return 0;
}
