#ifndef STOKENIZE_H
#define STOKENIZE_H

#include <cassert>
#include <cstring>
#include <iostream>

#include "../../includes/map/btree_array_functions.h"
#include "constants.h"
#include "state_machine_functions.h"
#include "token.h"

class STokenizer {
public:
  // Constructors
  STokenizer() {
    _pos = 0;
    make_table(_table);
  }
  STokenizer(const char str[]) {
    std::strcpy(_buffer, str);
    _pos = 0;
    make_table(_table);
  }
  bool done() { // true: there are no more tokens
    if (_pos > strlen(_buffer)) {
      return true;
    }
    return false;
  }
  bool more() { return !done(); }
  // true: there are more tokens
  // extract one token (very similar to the way cin >> works)
  friend STokenizer &operator>>(STokenizer &s, SToken &t) {
    s.get_token(0, t);
    return s;
  }
  // set a new string as the input string
  void set_string(const char str[]) {
    std::strcpy(_buffer, str);
    _pos = 0;
  }
  // =====================================
  // TODO: Add more methods here if needed
  // =====================================
private:
  // create table for all the tokens we will recognize (e.g. doubles, words,
  // etc.)
  void make_table(int _table[][MAX_COLUMNS]) {
    init_table(_table);
    mark_fail(_table, 2);
    mark_success(_table, 1);
    mark_fail(_table, 2);
    mark_fail(_table, 0);
    for (int i = 3; i < 13; i++) {
      mark_success(_table, i);
    }
    mark_fail(_table, 8);
    mark_cells(0, _table, ALFA, 4);
    mark_cells(0, _table, DIGITS, 1);
    mark_cells(0, _table, OPERATORS, 10);
    mark_cells(0, _table, SPACES, 5);
    mark_cell(0, _table, LEFT_PARENTH, 11);
    mark_cell(0, _table, RIGHT_PARENTH, 12);
    mark_cell(0, _table, COMMA, 6);
    mark_cell(0, _table, ASTERISK, 7);
    mark_cell(0, _table, QUOTE, 8);
    mark_cell(0, _table, '.', 2);
    mark_cells(1, _table, DIGITS, 1);
    mark_cell(1, _table, '.', 2);
    mark_cells(2, _table, DIGITS, 3);
    mark_cells(3, _table, DIGITS, 3);
    mark_cells(4, _table, ALFA, 4);
    mark_cells(4, _table, DIGITS, 4);
    mark_cells(5, _table, SPACES, 5);
    mark_cells(8, _table, 1, 255, 8);
    mark_cell(8, _table, QUOTE, 9);
    mark_cells(10, _table, OPERATORS, 10);
  }
  // extract the longest string that match one of the acceptable token types
  bool get_token(int start_state, SToken &token) {
    // std::cout << _buffer << std::endl;
    // std::cout << _pos;
    int next_state = start_state;
    int last_success = TOKEN_UNKNOWN;
    int init_pos = _pos;
    int last_success_pos = _pos;
    string temp = "";
    while (_buffer[_pos] > 0 && more()) {
      next_state = _table[next_state][int(_buffer[_pos])];
      if (next_state == TOKEN_UNKNOWN) {
        break;
      } else if (!is_success(_table, next_state)) {
        _pos++;
      } else {

        last_success_pos = _pos;
        last_success = next_state;
        _pos++;
      }
    }
    _pos = last_success_pos;
    if (_buffer[_pos] == '.') {
      last_success = 7;
    }
    _pos++;
    if (last_success != 9) {
      // temp = std::strncpy(temp, _buffer + init_pos, _pos - init_pos);
      for (int i = init_pos; i <= last_success_pos; i++) {
        temp += _buffer[i];
      }
    } else {
      // temp = std::strncpy(temp, _buffer + init_pos + 1, _pos - init_pos - 2);
      for (int i = init_pos + 1; i <= last_success_pos - 1; i++) {
        temp += _buffer[i];
      }
    }
    std::string str;
    if (last_success != TOKEN_UNKNOWN) {
      str = temp;
      // } else {
      //   str = "";
    }
    if (last_success == 5) {
      str = " ";
    }
    SToken tempToken(str, token_type(last_success));
    token = tempToken;
    return true;
  }
  // return the type of the token
  STRING_TOKEN_TYPES token_type(int state) const {
    switch (state) {
    case 1:
      return TOKEN_NUMBER;
    case 3:
      return TOKEN_NUMBER;
    case 4:
      return TOKEN_STRING;
    case 5:
      return TOKEN_SPACE;
    case 6:
      return TOKEN_COMMA;
    case 7:
      return TOKEN_ASTERISK;
    case 9:
      return TOKEN_STRING;
    case 10:
      return TOKEN_OPERATOR;
    case 11:
      return TOKEN_LEFT_PARENTH;
    case 12:
      return TOKEN_RIGHT_PARENTH;
    default:
      return TOKEN_UNKNOWN;
    }
  }
  char _buffer[MAX_BUFFER]; // input string
  int _pos;                 // current position in the string
  int _table[MAX_ROWS][MAX_COLUMNS];
};

#endif // STOKENIZE_H