#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "agency_parser.h"
#include "io.h"

char AgencyParser::key_from_string(std::string *str) {
  if (!str->compare("tag")) {
    return ATTR_AGENCY_TAG;
  } else if (!str->compare("title")) {
    return ATTR_AGENCY_TITLE;
  } else if (!str->compare("regionTitle")) {
    return ATTR_AGENCY_REGION_TITLE;
  } else {
    return 'Z';
  }
}

std::string AgencyParser::results() {
  std::stringstream ss;
  int i;
  
  if (agencies.empty()) {
    error("AgencyParser::results()");
  }

  ss << IO_GREEN "AGENCY TITLE                             (AGENCY TAG     )               REGION" IO_NORMAL
     << std::endl << std::endl;
  for (i = 0; i < agencies.size(); i++) {
    ss << std::left << std::setw(40) << agencies[i]->title
       << std::setw(0) << " (" IO_YELLOW
       << std::setw(15) << agencies[i]->tag
       << std::setw(0) << IO_NORMAL ") "
       << std::setw(20) << std::right << agencies[i]->regionTitle
       << std::endl;
  }
  ss << std::endl
     << IO_GREEN "NOTE: When you set the nextbus agency using "
     << "`nextbus -A <agency>` make sure to"
     << std::endl << "use the " IO_YELLOW
     << "AGENCY TAG" IO_GREEN "." IO_NORMAL;
  return ss.str();
}

void AgencyParser::parse_agency() {
  std::map<char, std::string> *attributeMap;

  tempAgency = new Agency();

  attributeMap = parse_attributes();
  tempAgency->tag = (*attributeMap)[ATTR_AGENCY_TAG];
  tempAgency->title = (*attributeMap)[ATTR_AGENCY_TITLE];
  tempAgency->regionTitle = (*attributeMap)[ATTR_AGENCY_REGION_TITLE];
  agencies.push_back(tempAgency);
}

void AgencyParser::element_open_actions() {
  if (!substring.compare("agency")) {
    parse_agency();
  }
}

void AgencyParser::element_close_actions() {
  // No actions necessary because <Agency/> is self-closing
}
