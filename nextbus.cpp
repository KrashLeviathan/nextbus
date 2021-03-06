#include <iostream>
#include "io.h"
#include "config.h"
#include "actions.h"

int main(int argc, char *argv[]) {
  std::string filepath;
  std::string xml_string;
  CommandLineAction *clAction;
  ConfigFile *configFile;

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

  // Take appropriate action
  if (clAction->actions & ACTION_AGENCY_LIST) {
    // Agency list
    action_agency_list(clAction, configFile);
  }
  if (clAction->actions & ACTION_AGENCY_STORE) {
    // Store agency
    action_agency_store(clAction, configFile);
  }
  if (clAction->actions & ACTION_ROUTE_LIST) {
    // Route list
    action_route_list(clAction, configFile);
  }
  if (clAction->actions & ACTION_LIST_STOPS) {
    // List stops
    action_list_stops(clAction, configFile);
  }
  if (clAction->actions & ACTION_SCHEDULE_LIST) {
    // Schedules
    action_schedule_list(clAction, configFile);
  }
  if (clAction->actions & ACTION_HELP) {
    // Help
    action_help();
  }
  if (clAction->actions & ACTION_PREDICT_STOP) {
    // Predictions for a stop
    action_predict_stop(clAction, configFile);
  }
  if (clAction->actions & ACTION_PREDICT_ROUTE) {
    // Predictions for a route
    action_predict_route(clAction, configFile);
  }
  if (clAction->actions & ACTION_SAVE_CUSTOM) {
    // Save a custom setting
    action_save_custom(clAction, configFile);
  }
  if (clAction->actions & ACTION_USE_SAVED) {
    // Use a custom setting
    action_use_saved(clAction, configFile, false);
  }
  if (clAction->actions & ACTION_MINUTES) {
    // Print ONLY the minutes for a custom setting
    action_use_saved(clAction, configFile, true);
  }
  if (clAction->actions == 0) {
    usage();
  }

  // Cleanup
  delete clAction;
  delete configFile;

  return 0;
}
