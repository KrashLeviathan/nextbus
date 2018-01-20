#ifndef ACTIONS_H
# define ACTIONS_H

# include "io.h"
# include "config.h"

void action_agency_list(CommandLineAction *clAction, ConfigFile *configFile);

void action_agency_store(CommandLineAction *clAction, ConfigFile *configFile);

void action_route_list(CommandLineAction *clAction, ConfigFile *configFile);

void action_list_stops(CommandLineAction *clAction, ConfigFile *configFile);

void action_schedule_list(CommandLineAction *clAction, ConfigFile *configFile);

void action_predict_stop(CommandLineAction *clAction, ConfigFile *configFile);

void action_predict_route(CommandLineAction *clAction, ConfigFile *configFile);

void action_save_custom(CommandLineAction *clAction, ConfigFile *configFile);

void action_use_saved(CommandLineAction *clAction, ConfigFile *configFile, bool minutesOnly);

void action_help();

#endif
