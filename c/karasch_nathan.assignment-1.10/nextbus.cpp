#include <iostream>
#include "io.h"
#include "config.h"
#include "connection.h"
#include "route_parser.h"
#include "predictions_parser.h"

int main(int argc, char *argv[]) {
  std::string filepath;
  std::string xml_string;
  CommandLineAction *clAction;
  ConfigFile *configFile;
  int i, j;

  // TODO
  // <body copyright="All data copyright agencies listed below and NextBus Inc 2016.">
  //    <Error shouldRetry="false">
  //    Agency parameter "a=cyrdie" is not valid.
  //    </Error>
  // </body>

  // Load settings from the config file
  filepath = get_filepath("config.nextbus");
  configFile = new ConfigFile(filepath);

  // Parse command line arguments
  clAction = parse_arguments(argc, argv);
  // std::cout << clAction->to_string() << std::endl << std::endl;

  // Take appropriate action
  if (clAction->actions & ACTION_AGENCY_LIST) {
    // Agency list
    filepath = get_filepath("agencyList.xml");
    xml_string = get_file_contents(filepath);
    if (xml_string[0] != '<' ||
	(configFile->lastChangeExpired() &&
	 !(clAction->actions & ACTION_CACHED)) ||
	clAction->actions & ACTION_ONLINE) {
      // The file doesn't exist, so get it from NextBus online API
      xml_string = agencyList();
      set_file_contents(filepath, xml_string);
    }
    // TODO: parse agencyList


    
  } else if (clAction->actions & ACTION_AGENCY_STORE) {
    // Store agency
    configFile->agency = clAction->agency;
    configFile->update();
    std::cout << "Configuration Change:" << std::endl
	      << "   Agency set to '"
	      << configFile->agency << "'." << std::endl;
  } else if (clAction->actions & ACTION_ROUTE_LIST) {
    // Route list
    filepath = get_filepath("routeList.xml");
    xml_string = get_file_contents(filepath);
    if (xml_string[0] != '<' ||
	(configFile->lastChangeExpired() &&
	 !(clAction->actions & ACTION_CACHED)) ||
	clAction->actions & ACTION_ONLINE) {
      // The file doesn't exist, so get it from NextBus online API
      xml_string = routeList(configFile->agency.c_str());
      set_file_contents(filepath, xml_string);
    }
    // TODO: Parse


    
    // TODO: Route Config?
    // xml_string = routeConfig(configFile->agency.c_str(), NULL);
  } else if (clAction->actions & ACTION_ROUTE_STORE) {
    // Store route
    configFile->routes.push_back(&clAction->route);
    configFile->update();
    std::cout << "Configuration Change:" << std::endl
	      << "   Added route '"
	      << clAction->route << "'. This route's schedule or "
	      << std::endl
	      << "   messages will display with the command line arguments "
	      << std::endl
	      << "   [-s|--schedules] or [-m|--messages], respectively."
	      << std::endl;
  } else if (clAction->actions & ACTION_SCHEDULE_LIST) {
    // Schedules
    if (configFile->routes.size() == 0) {
      // TODO
      std::cout
	<< "   No route given! Use nextbus -R <route name> to store a route"
	<< std::endl
	<< "   or several routes first; or use nextbus -s <route name> to"
	<< std::endl
	<< "   give a schedule for a certain route without storing it."
	<< std::endl;
    } else {
      // TODO: Find a smart way to cache schedule data
      for (j = 0; j < configFile->routes.size(); j++) {
	xml_string = schedule(configFile->agency.c_str(), configFile->routes[j]->c_str());
	// TODO: parse


	
      }
    }
  } else if (clAction->actions & ACTION_MESSAGE_LIST) {
    // Messages
    if (configFile->routes.size() == 0) {
      // TODO
      std::cout
	<< "   No route given! Use nextbus -R <route name> to store a route"
	<< std::endl
	<< "   or several routes first; or use nextbus -m <route name> to"
	<< std::endl
	<< "   give messages for a certain route without storing it."
	<< std::endl;
    } else {
      // TODO: Find a smart way to cache message data
      for (j = 0; j < configFile->routes.size(); j++) {
	xml_string = nb_messages(configFile->agency.c_str(), configFile->routes);
	// TODO: parse


	
      }
    }
  } else if (clAction->actions & ACTION_PREDICT_STOP) {
    // Predictions for a stop
    xml_string = predictions(configFile->agency.c_str(),
			     clAction->stop.c_str());
    PredictionsParser parser (xml_string);
    parser.parse();
    std::cout << parser.results() << std::endl;
  } else if (clAction->actions & ACTION_PREDICT_ROUTE) {
    // Predictions for a route
    xml_string = predictions(configFile->agency.c_str(),
			     clAction->stop.c_str(),
			     clAction->route.c_str());
    PredictionsParser parser (xml_string);
    parser.parse();
    std::cout << parser.results() << std::endl;
  } else if (clAction->actions & ACTION_SAVE_CUSTOM) {
    // Save a custom setting
    configFile->savedRouteStops
      .push_back(new SavedRouteStop(clAction->save,
				    clAction->route,
				    clAction->stop));
    configFile->update();
  } else if (clAction->actions & ACTION_USE_SAVED) {
    // Use a custom setting
    for (j = 0; j < configFile->savedRouteStops.size(); j++) {
      for (i = 0; i < clAction->saveUses.size(); i++) {
	if (!configFile->savedRouteStops[j]->name.compare(
	       *clAction->saveUses[i])) {
	  xml_string = predictions(configFile->agency.c_str(),
			   configFile->savedRouteStops[j]->stop.c_str(),
			   configFile->savedRouteStops[j]->route.c_str());
	PredictionsParser parser (xml_string);
	parser.parse();
	std::cout << parser.results() << std::endl;
	}
      }
    }
  } else {
    usage();
  }

  // After parsing an xml string, the variables in the
  // RouteParser instance contain all the data pulled
  // from the xml string.
  // RouteParser parser (xml_string);
  // parser.parse();

  // Cleanup
  delete clAction;
  delete configFile;
  
  return 0;
}
