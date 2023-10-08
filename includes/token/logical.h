#ifndef LOGICAL_H
#define LOGICAL_H

#include "constants.h"
#include "token.h"
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

class Logical : public Token {
public:
  Logical() {}
  Logical(string value) { logic = value; }
  void Print(ostream &outs = cout) const { std::cout << "[" << logic << "]"; }

  TOKEN_TYPES TypeOf() { return LOGIC; }
  string as_string() { return logic; }
  int get_precedence() {
    if (logic == "and") {
      return 40;
    } else if (logic == "or") {
      return 39;
    } else {
      return 41;
    }
  }

private:
  string logic;
};

#endif