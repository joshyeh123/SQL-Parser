#ifndef STATE_MACHINE_FUNCTIONS_H
#define STATE_MACHINE_FUNCTIONS_H

#include <cassert>
#include <cstring>
#include <iomanip>
#include <iostream>

#include "constants.h"

// Fill all cells of the array with -1
void init_table(int _table[][MAX_COLUMNS]) {
  for (int i = 0; i < MAX_COLUMNS; i++) {
    for (int j = 0; j < MAX_ROWS; j++) {
      _table[j][i] = -1;
    }
  }
}

// Mark this state (row) with a 1 (success)
void mark_success(int _table[][MAX_COLUMNS], int state) {
  _table[state][0] = 1;
}

// Mark this state (row) with a 0 (fail)
void mark_fail(int _table[][MAX_COLUMNS], int state) { _table[state][0] = 0; }

// true if state is a success state
bool is_success(int _table[][MAX_COLUMNS], int state) {
  if (state != -1 && _table[state][0] == 1) {
    return true;
  }
  return false;
}

// Mark a range of cells in the array.
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to,
                int state) {
  for (int i = from; i <= to; i++) {
    _table[row][i] = state;
  }
}

// Mark columns represented by the string columns[] for this row
void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[],
                int state) {
  for (int i = 0; i < strlen(columns); i++) {
    _table[row][int(columns[i])] = state;
  }
}

// Mark this row and column
void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state) {
  table[row][column] = state;
}

// This can realistically be used on a small table
void print_table(int _table[][MAX_COLUMNS]) {
  for (int i = 0; i < MAX_ROWS; i++) {
    for (int j = 0; j < MAX_COLUMNS; j++) {
      std::cout << _table[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

// show string s and mark this position on the string:
// hello world   pos: 7
//        ^
void show_string(char s[], int _pos) {

  std::cout << s << "  pos: " << _pos << std::endl;
  std::cout << std::string(' ', _pos) << "^";
}

// =====================================
// TODO: Add more methods here if needed
// =====================================

#endif // STATE_MACHINE_FUNCTIONS_H