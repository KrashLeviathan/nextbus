#ifndef XML_PARSER
# define XML_PARSER

# include <string>

class XmlParser {
 protected:
  char c;
  std::string substring;
  std::string pText;
  std::string *text;
  int index;
 public:
  XmlParser(std::string &s) {
    text = &s;
    index = 0;
  }
};

#endif
