#ifndef TOKENSTR_H
#define TOKENSTR_H

#include "constants.h"
#include "token.h"
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

class TokenStr : public Token {
public:
  TokenStr() {}
  TokenStr(string value) { str = value; }
  void Print(ostream &outs = cout) const { std::cout << "[" << str << "]"; }

  TOKEN_TYPES TypeOf() { return TOKENSTR; }
  string as_string() { return str; }
  int get_precedence() { return 0; }

private:
  string str;
};

#endif