#ifndef TOKEN_H
#define TOKEN_H
#include "constants.h"
#include <iomanip>
#include <iostream>

using namespace std;

class Token {
public:
  Token() {}
  friend ostream &operator<<(ostream &outs, const Token &token) {
    token.Print(outs);
    return outs;
  }
  virtual void Print(ostream &outs = cout) const {
    outs << "TOKEN Print: DON't ^%#$# call me again!" << endl;
  }
  virtual std::string as_string() { return "hi"; }
  virtual TOKEN_TYPES TypeOf() { return TOKEN; }
  virtual int get_precedence() { return -1; }
};

#endif