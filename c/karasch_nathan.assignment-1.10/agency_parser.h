#ifndef AGENCY_PARSER_H
# define AGENCY_PARSER_H

# include <string>
# include <vector>
# include "xml_parser.h"

# define ATTR_AGENCY_TAG           'a'
# define ATTR_AGENCY_TITLE         'b'
# define ATTR_AGENCY_REGION_TITLE  'c'

class Agency {
 public:
  std::string tag;
  std::string title;
  std::string regionTitle;
};

class AgencyParser : public XmlParser {
 private:
  Agency *tempAgency;
  void parse_agency();
  void element_open_actions();
  void element_close_actions();
  char key_from_string(std::string *str);
 public:
  std::vector<Agency *> agencies;
  AgencyParser(std::string &s) : XmlParser(s) {
    tempAgency = NULL;
  }
  std::string results();
};

#endif
