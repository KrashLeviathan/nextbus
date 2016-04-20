# include <iostream>
# include <string>
# include <sstream>
# include <stdlib.h>
# include "actions.h"
# include "io.h"
# include "config.h"
# include "connection.h"
# include "predictions_parser.h"
# include "help_info.h"

void action_agency_list(CommandLineAction *clAction, ConfigFile *configFile) {
  std::string filepath;
  std::string xml_string;
  
  filepath = get_filepath("agencyList.xml");
  xml_string = get_file_contents(filepath);
  if (xml_string[0] != '<' ||
      (configFile->lastUsageExpired() &&
       !(clAction->actions & ACTION_CACHED)) ||
      clAction->actions & ACTION_ONLINE) {
    // The file doesn't exist, so get it from NextBus online API
    xml_string = agencyList();
    set_file_contents(filepath, xml_string);
  }
  // TODO: parse agencyList

}

void action_agency_store(CommandLineAction *clAction, ConfigFile *configFile) {
  configFile->agency = clAction->agency;
  configFile->update();
  std::cout << IO_GREEN "Configuration Change:" IO_NORMAL << std::endl
	    << "   Agency set to '"
	    << configFile->agency << "'." << std::endl;
}

void action_route_list(CommandLineAction *clAction, ConfigFile *configFile) {
  std::string filepath;
  std::string xml_string;
  
  filepath = get_filepath("routeList.xml");
  xml_string = get_file_contents(filepath);
  if (xml_string[0] != '<' ||
      (configFile->lastUsageExpired() &&
       !(clAction->actions & ACTION_CACHED)) ||
      clAction->actions & ACTION_ONLINE) {
    // The file doesn't exist, so get it from NextBus online API
    xml_string = routeList(configFile->agency.c_str());
    set_file_contents(filepath, xml_string);
  }
  // TODO: Parse


  
  // TODO: Route Config?
  // xml_string = routeConfig(configFile->agency.c_str(), NULL);
}

void action_schedule_list(CommandLineAction *clAction, ConfigFile *configFile) {
  std::string xml_string;
  
  xml_string = schedule(configFile->agency.c_str(), clAction->route.c_str());

  // TODO: Find a smart way to cache schedule data
  // TODO: parse
}

void action_predict_stop(CommandLineAction *clAction, ConfigFile *configFile) {
  std::string xml_string;
  
  xml_string = predictions(configFile->agency.c_str(),
			   clAction->stop.c_str());
  PredictionsParser parser (xml_string);
  parser.parse();
  std::cout << parser.results() << std::endl;
}

void action_predict_route(CommandLineAction *clAction, ConfigFile *configFile) {
  std::string xml_string;
  
  xml_string = predictions(configFile->agency.c_str(),
			   clAction->stop.c_str(),
			   clAction->route.c_str());
  PredictionsParser parser (xml_string);
  parser.parse();
  std::cout << parser.results() << std::endl;
}

void action_save_custom(CommandLineAction *clAction, ConfigFile *configFile) {
  configFile->savedRouteStops
    .push_back(new SavedRouteStop(clAction->save,
				  clAction->route,
				  clAction->stop));
  configFile->update();
}

void action_use_saved(CommandLineAction *clAction, ConfigFile *configFile) {
  bool saveUseFound;
  int i, j;
  std::string xml_string;
  
  for (i = 0; i < clAction->saveUses.size(); i++) {
    saveUseFound = false;
    for (j = 0; j < configFile->savedRouteStops.size()
	   && !saveUseFound; j++) {
      if (!configFile->savedRouteStops[j]->name.compare(
					*clAction->saveUses[i])) {
	saveUseFound = true;
	xml_string = predictions(configFile->agency.c_str(),
			 configFile->savedRouteStops[j]->stop.c_str(),
			 configFile->savedRouteStops[j]->route.c_str());
	PredictionsParser parser (xml_string);
	parser.parse();
	std::cout << IO_GREEN << *clAction->saveUses[i]
		  << IO_NORMAL << std::endl
		  << parser.results() << std::endl;
      }
    }
    if (!saveUseFound) {
      std::cout << IO_RED "No saved route/stop was found for '"
		<< *clAction->saveUses[i] << "'." IO_NORMAL << std::endl
		<< std::endl;
    }
  }
}

void action_help() {
  std::stringstream ss;
  std::string filepath;
  std::string readme_string;

  // Save the help info to README.txt in the default directory
  filepath = get_filepath("README.txt");
  set_file_contents(filepath, help_info);

  // Call less to try to display it
  ss << "less " << filepath;
  if (system(ss.str().c_str())) {
    // Call to less failed, so dump it to the terminal.
    std::cout << help_info << std::endl;
  }
}
