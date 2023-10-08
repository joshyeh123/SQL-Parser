#ifndef UNIVERSAL_H
#define UNIVERSAL_H

#include "constants.h"
#include "token.h"
#include <iomanip>
#include <iostream>

using namespace std;

class Universal : public Token {
public:
  Universal() { str = '*'; }
  void Print(ostream &outs = cout) const { outs << "[" << str << "]"; }

  TOKEN_TYPES TypeOf() { return UNIVERSAL; }
  string as_string() { return str; }
  int get_precedence() { return 1; }

private:
  string str;
};

#endif