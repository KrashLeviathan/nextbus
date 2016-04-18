#include <iostream>
#include "io.h"
#include "config.h"
#include "connection.h"
#include "route_parser.h"


int main(int argc, char *argv[]) {
  std::string filepath;
  std::string xml_string;
  CommandLineAction *clAction;
  ConfigFile *configFile;

  // Parse command line arguments
  clAction = parse_arguments(argc, argv);

  // Load settings from the config file
  filepath = get_filepath("config.nextbus");
  configFile = new ConfigFile(filepath);
  
  // Curl File
  // xml_string = routeConfig(configFile->agency.c_str(), NULL);

  // Save to File
  // filepath = get_filepath("routeConfig.xml");
  // set_file_contents(filepath, xml_string);

  // Open a File
  filepath = get_filepath("routeConfig.xml");
  xml_string = get_file_contents(filepath);

  // After parsing an xml string, the variables in the
  // RouteParser instance contain all the data pulled
  // from the xml string.
  RouteParser parser (xml_string);
  parser.parse();

  // Cleanup
  delete clAction;
  delete configFile;
  
  return 0;
}
