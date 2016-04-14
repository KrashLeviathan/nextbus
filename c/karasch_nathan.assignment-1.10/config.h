#include <fstream>
#include <string>

void add_config_stop(std::ofstream &configFile,
		     const char *name,
		     const char *route,
		     const char *stop);

bool init_config(std::string &filepath);
