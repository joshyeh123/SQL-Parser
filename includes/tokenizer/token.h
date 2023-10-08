#ifndef STRING_TOKEN_H
#define STRING_TOKEN_H

#include <iostream>
#include <string>

#include "constants.h"

using namespace std;

class SToken {
public:
  // Constructors
  SToken() {
    _token = "";
    _type = TOKEN_UNKNOWN;
  }
  SToken(string str, STRING_TOKEN_TYPES type) {
    _token = str;
    _type = type;
  }
  // return the type of the token
  STRING_TOKEN_TYPES type() const { return _type; }
  // return the token string
  string token_str() const { return _token; }
  // return the type of the token as a string
  string token_type() const {
    switch (int(_type)) {
    case TOKEN_STRING:
      return "STR";
    case TOKEN_NUMBER:
      return "NUMBER";
    case TOKEN_OPERATOR:
      return "OPERATOR";
    case TOKEN_ASTERISK:
      return "ASTERISK";
    case TOKEN_SPACE:
      return "SPACE";
    case TOKEN_COMMA:
      return "COMMA";
    case TOKEN_QUOTE:
      return "QUOTE";
    case TOKEN_LEFT_PARENTH:
      return "LEFT_PARENTH";
    case TOKEN_RIGHT_PARENTH:
      return "RIGHT_PARENTH";
    default:
      return "UNKNOWN";
    }
  }
  // overload the << operator
  friend ostream &operator<<(ostream &outs, const SToken &t) {
    outs << "|" << t.token_str() << '|';
    return outs;
  }
  // =====================================
  // TODO: Add more methods here if needed
  // =====================================
private:
  // the token string
  string _token;
  // the type of the token
  STRING_TOKEN_TYPES _type;
};

#endif // STRING_TOKEN_H