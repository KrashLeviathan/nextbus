#include <iostream>
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
  std::cout << IO_RED "ERROR: XmlParser::parse_attributes()"
            << IO_NORMAL << std::endl;
  return attributeMap;
}

void XmlParser::parse_error() {
  std::map<char, std::string> *attributeMap;

  attributeMap = parse_attributes();
  errorShouldRetry = (*attributeMap)[ATTR_ERROR_SHOULD_RETRY];
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
        if (!substring.compare("Error")) {
          // Error complete
          errorText = pText;
          std::cout << IO_RED "ERROR: "
                    << errorText << IO_NORMAL
                    << "Should Retry?  " << errorShouldRetry << std::endl;
        }
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
        if (!substring.compare("Error")) {
          // Received Error from NextBus API
          parse_error();
        }
        element_open_actions();
        substring.erase();
        break;
      } else {
        substring += c;
        pText.erase();
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
    } else {
      pText += c;
    }
  }
}
