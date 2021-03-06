#ifndef XML_PARSER_H
# define XML_PARSER_H

# include <string>

# define ATTR_ERROR_SHOULD_RETRY          '!'

class XmlParser {
protected:
  char c;
  std::string substring;
  std::string pText;
  std::string *text;
  std::string errorText;
  std::string errorShouldRetry;
  int index;

  std::map<char, std::string> *parse_attributes();

  void parse_error();

  void parse_element_open();

  virtual void element_open_actions() = 0;

  virtual void element_close_actions() = 0;

  virtual char key_from_string(std::string *str) = 0;

public:
  XmlParser(std::string &s) {
    text = &s;
    index = 0;
  }

  void parse();
};

#endif
