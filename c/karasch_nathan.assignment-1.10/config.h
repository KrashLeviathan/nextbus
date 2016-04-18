#ifndef CONFIG_H
# define CONFIG_H

# include <fstream>
# include <string>
# include <vector>
# include <ctime>

# define VERSION_NUMBER        "1"
# define DEFAULT_AGENCY        "cyride"

class SavedRouteStop {
 public:
  std::string name;
  std::string route;
  std::string stop;
};

class ConfigFile {
 public:
  time_t lastChange;
  time_t lastRouteDownload;
  std::string agency;
  std::vector<std::string *> routes;
  std::vector<SavedRouteStop *> savedRouteStops;

  ConfigFile(std::string &filepath);
  bool update();

 private:
  std::string filepath;
  std::string contents;
  bool parse();
  void print_details();
};

#endif
