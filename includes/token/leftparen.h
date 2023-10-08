#ifndef LEFTPAREN_H
#define LEFTPAREN_H

#include "constants.h"
#include "token.h"
#include <iomanip>
#include <iostream>

using namespace std;

class LeftParen : public Token {
public:
  LeftParen() { _Lparen = '('; }
  void Print(ostream &outs = cout) const { outs << "[" << _Lparen << "]"; }

  TOKEN_TYPES TypeOf() { return LPAREN; }
  string as_string() { return _Lparen; }
  int get_precedence() { return 91; }

private:
  string _Lparen;
};

#endif