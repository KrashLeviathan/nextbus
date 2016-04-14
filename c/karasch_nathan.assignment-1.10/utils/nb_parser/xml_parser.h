#ifndef XML_PARSER
# define XML_PARSER

# include <string>

class XmlParser {
 protected:
  std::string text;
 public:
  XmlParser(std::string &s) { text = s; }
  virtual void *next(const char *type);
};

#endif
