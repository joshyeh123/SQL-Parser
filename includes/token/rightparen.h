#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H

#include "constants.h"
#include "token.h"
#include <iomanip>
#include <iostream>

using namespace std;

class RightParen : public Token {
public:
  RightParen() { _Rparen = ')'; }
  void Print(ostream &outs = cout) const { outs << "[" << _Rparen << "]"; }

  TOKEN_TYPES TypeOf() { return RPAREN; }
  string as_string() { return _Rparen; }
  int get_precedence() { return 90; }

private:
  string _Rparen;
};

#endif