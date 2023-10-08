#ifndef RELATIONAL_H
#define RELATIONAL_H

#include "constants.h"
#include "token.h"
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

class Relational : public Token {
public:
  Relational() {}
  Relational(string value) { _Oper = value; }
  void Print(ostream &outs = cout) const { std::cout << "[" << _Oper << "]"; }

  TOKEN_TYPES TypeOf() { return RELATIONAL; }
  string as_string() { return _Oper; }
  int get_precedence() {
    if (_Oper == ">" || _Oper == "<" || _Oper == ">=" || _Oper == "<=") {
      return 50;
    } else if (_Oper == "=" || _Oper == "<>" || _Oper == "!=") {
      return 51;
    } else {
      return 49;
    }
  }

private:
  string _Oper;
};

#endif