#include <iostream>
#include "io.h"
#include "config.h"
#include "connection.h"


int main(int argc, char *argv[]) {
  std::string filepath;
  std::string xml_string;
  CommandLineAction *clAction;

  clAction = parse_arguments(argc, argv);

  // Test config file creation
  // filepath = get_filepath("config.nextbus");
  // init_config(filepath);

  // Test file curling
  // agency = DEFAULT_AGENCY;
  // xml_string = routeList();

  // std::cout << xml_string << std::endl;

  delete clAction;
  
  return 0;
}
