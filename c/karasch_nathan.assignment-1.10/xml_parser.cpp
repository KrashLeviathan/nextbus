#include <iostream>
#include <string>
#include <map>
#include "xml_parser.h"
#include "io.h"

std::map<char, std::string> *XmlParser::parse_attributes() {
  std::map<char, std::string> *attributeMap = new std::map<char, std::string>();
  char key;
  bool readingValueString = false;
  
  substring.erase();

  while (index < text->length()) {
    c = (*text)[index++];
    switch (c) {
    case ' ':
      if (!readingValueString) {
	// New attribute coming up
	substring.erase();
      } else {
	// The space is part of a string value
	substring += c;
      }
      break;
    case '=':
      key = key_from_string(&substring);
      break;
    case '"':
      if (readingValueString) {
	(*attributeMap)[key] = substring;
	readingValueString = false;
      } else {
	readingValueString = true;
	substring.erase();
      }
      break;
    case '>':
      // Closing bracket found
      substring.erase();
      return attributeMap;
    default:
      substring += c;
      break;
    }
  }
  std::cout << IO_RED "ERROR: PredictionsParser::parse_attributes()"
	    << IO_NORMAL << std::endl;
  return attributeMap;
}

void XmlParser::parse_element_open() {
  substring.erase();
  c = (*text)[index++];
  if (c == '/') {
    // Element closing
    substring.erase();
    while (index < text->length()) {
      c = (*text)[index++];
      // Is it an element we care about?
      if (c == ' ' || c == '>') {
	element_close_actions();
	substring.erase();
	break;
      } else {
	substring += c;
      }
    }
  } else {
    // Element opening
    substring.erase();
    substring += c;
    while (index < text->length()) {
      c = (*text)[index++];
      // Is it an element we care about?
      if (c == ' ' || c == '>') {
	element_open_actions();
	substring.erase();
	break;
      } else {
	substring += c;
      }
    }
  }
}

void XmlParser::parse() {
  while (index < text->length()) {
    c = (*text)[index++];
    if (c == '<') {
      // Found an opening bracket
      parse_element_open();
    }
  }
}
