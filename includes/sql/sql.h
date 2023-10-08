#ifndef SQL_H
#define SQL_H

#include <cassert>  // assert
#include <fstream>  // ifstream
#include <iostream> // cout, endl

#include "../../includes/map/mmap.h"
#include "../../includes/parser/parser.h"
#include "../../includes/table/table.h"

using namespace std;

class SQL {
public:
  // Constructor
  SQL() {}
  // Process commands from a file
  SQL(char *&file) { this->file = file; }
  // Process a command and return the result table
  Table command(const string &cstr) {
    _parser.set_string(cstr);
    _command = _parser.parse_tree();
    // std::cout << _command << endl;
    if (_command.empty()) {
      return Table();
    }
    if ((_command.get("command"))[0] == "create") {
      _table = Table(_command.get("table_name")[0], _command.get("fields"));
    }
    if ((_command.get("command"))[0] == "insert") {
      _table = Table(_command.get("table_name")[0]);
      _table.insert_into(_command.get("values"));
    }
    if ((_command.get("command"))[0] == "select") {
      _table = Table(_command.get("table_name")[0]);

      if (_command.get("where").size() == 0) {
        selected = _table.select(_command.get("fields"));
        cout << selected << endl;

      } else {

        selected =
            _table.select(_command.get("fields"), _command.get("condition"));
        cout << selected << endl;
      }
    }
    return _table;
  }
  // Get all selected record numbers
  vector<long> select_recnos() {
    // std::cout << _table << endl;
    // std::cout << _command << endl;
    //  std::cout << _table.select_recnos() << endl;
    // cout << selected << endl;
    return _table.select_recnos();
  }
  // Print command
  void print_lookup() { _command.print_lookup(); }

  // takes a file and reads out the commands and executes them
  void batch(string str) {
    fstream f;
    f.open(str);
    string line;
    while (getline(f, line)) {
      cout << line << "\n";
      command(line);
      if (!_command.empty()) {
        if (line[0] == 's') {
          // cout << selected << endl;
          //     cout << _table << endl;
        }
        cout << select_recnos() << endl;
      }
    }
    f.close();
  }
  //======================================
  // TODO: add more methods here as needed
  //======================================
private:
  Table _table;
  Parser _parser;
  MMap<string, string> _command;
  string file;
  Table selected;
  //======================================
  // TODO: add more methods here as needed
  //======================================
};

#endif // SQL_H