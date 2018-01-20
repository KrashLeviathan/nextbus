#ifndef STOP_LIST_PARSER_H
# define STOP_LIST_PARSER_H

# include <string>
# include <vector>
# include "xml_parser.h"

# define ATTR_STOP_TAG           'c'
# define ATTR_STOP_TITLE         'd'

class StopListing {
public:
  std::string tag;
  std::string title;
};

class StopListParser : public XmlParser {
private:
  std::string routeTag;
  std::string routeTitle;
  StopListing *tempStopListing;

  void parse_route();

  void parse_stop();

  void element_open_actions();

  void element_close_actions();

  char key_from_string(std::string *str);

public:
  std::vector<StopListing *> stops;

  StopListParser(std::string &s) : XmlParser(s) {
    tempStopListing = NULL;
  }

  std::string results();
};

#endif
