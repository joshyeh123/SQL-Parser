#ifndef RPN_H
#define RPN_H

#include <iostream>

#include "../linked_list/queue/MyQueue.h"
#include "../linked_list/queue/MyStack.h"
#include "../table/table.h"
#include "../token/leftparen.h"
#include "../token/logical.h"
#include "../token/relational.h"
#include "../token/rightparen.h"
#include "../token/tokenstr.h"
#include "../token/universal.h"
using namespace std;

class RPN {
public:
  // CTOR
  RPN() {}
  RPN(const Queue<Token *> &input_q) { queue = input_q; }

  // save input_q to member variable queue
  void set_input(const Queue<Token *> &input_q) { queue = input_q; }

  // return result from member variable queue
  vector<long> operator()(string table = "") { return rpn(table); }
  // called by operator ()
  vector<long> rpn(string table = "") { return vector<long>(); }

  // evaluate relational
  bool eval_one(string op, string a, string b) {
    // std::string::const_iterator it = a.begin();
    // int ain;
    // int bin;
    // while (it != a.end() && std::isdigit(*it))
    //   ++it;
    // if (!a.empty() && it == a.end()) {
    //   ain = stoi(a);
    // }
    // it = b.begin();
    // while (it != b.end() && std::isdigit(*it))
    //   ++it;
    // if (!b.empty() && it == b.end()) {
    //   bin = stoi(b);
    // }
    // if (ain && bin) {
    //   if (op == "=") {
    //     return ain == bin;
    //   } else if (op == "!=") {
    //     return ain != bin;
    //   } else if (op == "<") {
    //     return ain < bin;
    //   } else if (op == "<=") {
    //     return ain <= bin;
    //   } else if (op == ">") {
    //     return ain > bin;
    //   } else if (op == ">=") {
    //     return ain >= bin;
    //   } else {
    //     return false;
    //   }
    // }
    bool aint = false, bint = false;
    for (int i = 0; i < 10; i++) {
      if (a[0] == DIGITS[i]) {
        aint = true;
      }
      if (b[0] == DIGITS[i]) {
        bint = true;
      }
    }
    if (bint && aint) {
      int ain, bin;
      ain = stoi(a);
      bin = stoi(b);
      if (op == "=") {
        return ain == bin;
      } else if (op == "!=") {
        return ain != bin;
      } else if (op == "<") {
        return ain < bin;
      } else if (op == "<=") {
        return ain <= bin;
      } else if (op == ">") {
        return ain > bin;
      } else if (op == ">=") {
        return ain >= bin;
      } else {
        return false;
      }
    }
    if (op == "=") {
      return a == b;
    } else if (op == "!=") {
      return a != b;
    } else if (op == "<") {
      return a < b;
    } else if (op == "<=") {
      return a <= b;
    } else if (op == ">") {
      return a > b;
    } else if (op == ">=") {
      return a >= b;
    } else {
      return false;
    }
  }

  // evaluate and and or
  vector<long> evaluate_logic(const string &op, vector<long> a,
                              vector<long> b) {
    vector<long> vec;
    vector<long> vec2;
    if (op == "and") {
      for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
          if (a[i] == b[j]) {
            vec.push_back(a[i]);
          }
        }
      }
    } else if (op == "or") {
      for (int i = 0; i < a.size(); i++) {
        bool found;
        for (int j = 0; j < b.size(); j++) {
          if (b[j] == a[i]) {
            found = true;
            break;
          }
        }
        if (!found) {
          vec.push_back(a[i]);
        }
        found = false;
      }
      for (int i = 0; i < b.size(); i++) {
        vec.push_back(b[i]);
      }

    } else if (op == "not") {
    }
    return vec;
  }

private:
  Queue<Token *> queue;
};

#endif // RPN_H