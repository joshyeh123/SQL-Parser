#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <cassert>
#include <iostream>

#include "../linked_list/queue/MyQueue.h"
#include "../linked_list/queue/MyStack.h"
#include "../token/leftparen.h"
#include "../token/logical.h"
#include "../token/relational.h"
#include "../token/rightparen.h"
#include "../token/tokenstr.h"
#include "../token/universal.h"

using namespace std;

class ShuntingYard {
public:
  // CTOR
  ShuntingYard() {}
  ShuntingYard(const Queue<Token *> &input_q) { queue = input_q; }

  // save input_q to member variable queue
  void infix(const Queue<Token *> &input_q) { queue = input_q; }

  // generate postfix queue from infix queue
  Queue<Token *> postfix() { return shunting_yard(); }
  Queue<Token *> postfix(const Queue<Token *> &input_q) {
    queue = input_q;
    return shunting_yard();
  }
  // called by postfix()
  Queue<Token *> shunting_yard() {
    Token *temp = queue.front();
    Queue<Token *> postfix;
    Stack<Token *> operators;
    while (!queue.empty()) {
      temp = queue.front();
      queue.pop();
      if (temp->TypeOf() == TOKENSTR) {
        postfix.push(temp);
      } else if (temp->TypeOf() == LOGIC || temp->TypeOf() == RELATIONAL) {
        while ((!operators.empty() && (operators.top()->TypeOf() != LPAREN &&
                                       operators.top()->TypeOf() != RPAREN)) &&
               (temp->get_precedence() <= operators.top()->get_precedence())) {
          postfix.push(operators.top());
          operators.pop();
        }
        operators.push(temp);
      } else if (temp->TypeOf() == LPAREN) {
        operators.push(temp);
      } else if (temp->TypeOf() == RPAREN) {
        while (!operators.empty() && operators.top()->as_string() != "(") {
          postfix.push(operators.top());
          operators.pop();
        }
        if (!operators.empty()) {
          operators.pop();
        }
      }
    }
    while (!operators.empty()) {
      postfix.push(operators.top());
      operators.pop();
    }

    return postfix;
  }

private:
  Queue<Token *> queue;
};

#endif // SHUNTING_YARD_H