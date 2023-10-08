#ifndef PARSE_H
#define PARSE_H

#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>

#include "../linked_list/queue/MyQueue.h"
#include "../map/map.h"
#include "../map/mmap.h"
#include "../tokenizer/stokenize.h"
/*
We take in a string, put it through tokenizer into a queue. We build an
adjacency matrix for commands only, and from the queue, pop the items and sort
out keywords, place them into the desired MPairs. Pass the MPairs into MMap. If
our statement is a success, return map. If not, scrap the map and return empty
map.

Additional Functions:
STokenize (tokenize string put into queue. If string is space or comma, skip)
createMatrix (Create adjacency matrix for command lines)
*/
class Parser {
public:
  // Constructors
  Parser() { makeTable(); }
  Parser(const char *&cstr) {
    _str = cstr;
    makeTable();
  }
  Parser(const string &str) {
    _str = str;
    makeTable();
  }
  // save string to private member
  void set_string(const char *&cstr) { _str = cstr; }
  void set_string(const string &str) { _str = str; }
  void makeTable() {
    init_table(_table);
    for (int i = 0; i < 40; i++) {
      mark_fail(_table, i);
    }
    mark_success(_table, 4);
    mark_success(_table, 10);
    mark_success(_table, 17);
    mark_success(_table, 20);
    mark_cell(0, _table,INSERT, 1);
    mark_cell(0, _table, SELECT, 12);
    mark_cell(0, _table, CREATE, 6);
    mark_cell(1, _table, INTO, 2);
    mark_cell(2, _table, STRINGS, 3);
    mark_cell(3, _table, VALUES, 25);
    mark_cell(25, _table, STRINGS, 4);
    mark_cell(25, _table, NUMBER, 4);
    mark_cell(4, _table, STRINGS, 4);
    mark_cell(4, _table, NUMBER, 4);
    mark_cell(4, _table, COMMA_TYPE, 5);
    mark_cell(5, _table, STRINGS, 4);
    mark_cell(5, _table, NUMBER, 4);
    mark_cell(6, _table, TABLE, 7);
    mark_cell(7, _table, STRINGS, 8);
    mark_cell(8, _table, FIELDS, 9);
    mark_cell(9, _table, STRINGS, 10);
    mark_cell(10, _table, COMMA_TYPE, 11);
    mark_cell(11, _table, STRINGS, 10);
    mark_cell(12, _table, ASTERISK_TYPE, 13);
    mark_cell(12, _table, STRINGS, 14);
    mark_cell(12, _table, NUMBER, 14);
    mark_cell(14, _table, COMMA_TYPE, 15);
    mark_cell(15, _table, STRINGS, 14);
    mark_cell(15, _table, NUMBER, 14);
    mark_cell(14, _table, FROM, 16);
    mark_cell(13, _table, FROM, 16);
    mark_cell(16, _table, STRINGS, 17);
    mark_cell(17, _table, WHERE, 18);
    mark_cell(18, _table, NOT, 19);
    mark_cell(18, _table, LEFT_PARENTHESIS, 22);
    mark_cell(18, _table, STRINGS, 20);
    mark_cell(19, _table, STRINGS, 20);
    mark_cell(20, _table, OPERATOR, 21);
    mark_cell(21, _table, STRINGS, 20);
    mark_cell(21, _table, NUMBER, 20);
    mark_cell(20, _table, AND, 18);
    mark_cell(20, _table, OR, 18);
    mark_cell(22, _table, NOT, 23);
    mark_cell(22, _table, STRINGS, 24);
    mark_cell(23, _table, STRINGS, 24);
    mark_cell(24, _table, AND, 22);
    mark_cell(24, _table, OR, 22);
    mark_cell(24, _table, RIGHT_PARENTHESIS, 20);
    mark_cell(24, _table, OPERATOR, 26);
    mark_cell(26, _table, STRINGS, 24);
    mark_cell(26, _table, NUMBER, 24);
  }
  STRING_TOKEN_TYPES token_type(SToken token) const {
    std::string str = token.token_str();
    STRING_TOKEN_TYPES type = token.type();
    if (str == "insert") {
      return INSERT;
    }
    if (str == "create") {
      return CREATE;
    }
    if (str == "select") {
      return SELECT;
    }
    if (str == "into") {
      return INTO;
    }
    if (str == "*") {
      return ASTERISK_TYPE;
    }
    if (str == ",") {
      return COMMA_TYPE;
    }
    if (str == "fields") {
      return FIELDS;
    }
    if (str == "(") {
      return LEFT_PARENTHESIS;
    }
    if (str == ")") {
      return RIGHT_PARENTHESIS;
    }
    if (str == "and") {
      return AND;
    }
    if (str == "or") {
      return OR;
    }
    if (str == "where") {
      return WHERE;
    }
    if (str == "not") {
      return NOT;
    }
    if (str == "from") {
      return FROM;
    }
    if (str == "table") {
      return TABLE;
    }
    if (str == "values") {
      return VALUES;
    }
    if (type == TOKEN_NUMBER) {
      return NUMBER;
    }
    if (type == TOKEN_STRING) {
      return STRINGS;
    }
    if (type == TOKEN_SPACE) {
      return SPACE;
    }
    if (type == TOKEN_OPERATOR) {
      return OPERATOR;
    }
    return TOKEN_UNKNOWN;
  }
  void pushQueue() { // this tokenizes the string and passes into the queue.
    tokenizer.set_string(_str.c_str());
    SToken temp;
    tokenizer >> temp;
    while (tokenizer.more()) {
      if (temp.token_type() == "UNKNOWN") {
        queue.clear_list();
        break;
      }
      queue.push(temp);
      temp = SToken();
      tokenizer >> temp;
    }
  }
  int get_state(int start_state, STRING_TOKEN_TYPES type) {
    return _table[start_state][type];
  }
  // parse string to map
  // sort through the queue and pass the commands and key variables into pairs
  // with key values (command, fields, table_name, values condition, where) Pass
  // this pair into map if the command ends in success state.
  MMap<string, string> parse_tree() {
    pushQueue();
    // std::cout << queue;
    MMap<string, string> map;
    SToken temp;
    int prev_state;
    int state = 0;
    bool where = false;
    // queue.size() >1
    // !queue.empty()
    while (!queue.empty()) {
      temp = queue.front();
      queue.pop();
      if (temp.token_str() == " ") {
        continue;
      }
      // std::cout << temp.token_str() << endl;
      STRING_TOKEN_TYPES type = token_type(temp);
      prev_state = state;
      state = get_state(state, type);
      if (state == TOKEN_UNKNOWN) {
        break;
      }
      if (temp.token_str() == ",") {
        if (prev_state == COMMA_TYPE) {
          break;
        }
        continue;
      }
      if (state == 1 || state == 12 || state == 6) {

        map["command"] += temp.token_str();
      }
      if (state == 3 || state == 8 || state == 17) {
        map["table_name"] += temp.token_str();
      }
      if (state == 4) {
        map["values"] += temp.token_str();
      }
      if (state == 10 || state == 13 || state == 14) {
        map["fields"] += temp.token_str();
      }
      if (where == true &&
          (state == 19 || state == 18 || state == 20 || state == 22 ||
           state == 23 || state == 24 || state == 21 || state == 26)) {
        map["condition"] += temp.token_str();
      }
      if (where == false && state == 18) {
        std::string yes = "yes";
        map["where"] += yes;
        where = true;
      }
    }
    if (state == TOKEN_UNKNOWN || !is_success(_table, state)) {
      queue.clear_list();
      map.clear();
    }
    // std::cout << map;
    return map;
  }

  // =====================================
  // TODO: Add more methods here if needed
  // =====================================

private:
  // command string
  string _str;
  STokenizer tokenizer;
  int _table[MAX_ROWS][MAX_COLUMNS];
  Queue<SToken> queue;
  // =====================================
  // TODO: Add more methods here if needed
  // =====================================
};

#endif // PARSE_H
