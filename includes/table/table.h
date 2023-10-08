#ifndef TABLE_H
#define TABLE_H

#include <cassert>  // assert
#include <cstring>  // strcmp
#include <fstream>  // fstream
#include <iomanip>  // setw
#include <iostream> // cout, endl
#include <string>   // string
#include <vector>   // vector

#include "../binary_files/file_record.h"
#include "../binary_files/utilities.h"

#include "../linked_list/queue/MyQueue.h"

#include "../map/map.h"
#include "../map/mmap.h"

#include "../rpn/rpn.h"
#include "../shunting_yard/shunting_yard.h"

#include "../token/leftparen.h"
#include "../token/logical.h"
#include "../token/relational.h"
#include "../token/rightparen.h"
#include "../token/tokenstr.h"
#include "../token/universal.h"

// //======================================
// // TODO: include more lib here as needed
// //======================================

class Table {
public:
  // TYPEDEFS
  typedef vector<string> vector_str;
  typedef vector<long> vector_long;
  typedef Map<string, long> map_sl;
  typedef Map<string, string> map_ss;
  typedef MMap<string, long> mmap_sl;
  typedef MMap<string, string> mmap_ss;
  // CONSTRUCTORS
  Table(const string &title = string(),
        const vector<string> &fields = vector<string>()) {
    _title = title;

    if (!fields.empty()) {
      create_table(title, fields);
    } else {
      _n_records = 0;
      fstream t;
      fstream f;
      // create table binary file
      open_fileRW(f, (title + "_names.txt").c_str());
      vector<string> temp = vector<string>(100, "");
      FileRecord record = FileRecord(temp);
      record.read(f, 0);
      vector<char *> records = record.get_records();
      f.close();
      int n_fields = 0;
      for (int i = 0; i < records.size(); i++) {
        if (strlen(records[i]) == 0) {
          break;
        }
        _fields.push_back(records[i]);
        _indices.push_back(mmap_sl());
        n_fields++;
      }
      temp = vector<string>(n_fields, "");
      record = FileRecord(temp);
      // Initialize the number of records

      // Read the first record
      open_fileRW(t, (title + ".tbl").c_str());
      long bytes = record.read(t, _n_records);
      while (bytes > 0) {
        // Print the record
        vector<char *> record_fields = record.get_records();
        // cout << "Record " << _n_records << ": " << record << endl;
        vector<string> rec;
        for (int i = 0; i < _indices.size(); i++) {
          string temp = record_fields[i];
          rec.push_back(temp);
          _indices[i][record_fields[i]] += _n_records;
        }
        _table.push_back(rec);
        // Increment the record number
        _n_records++;
        // Read the record
        bytes = record.read(t, _n_records);
      }
      t.close();
    }
  }
  // SQL: CREATE TABLE
  string create_table(const string &title, const vector<string> &fields) {
    fstream f;
    // create table binary file
    open_fileW(f, (_title + "_names.txt").c_str());
    FileRecord record = FileRecord(fields);
    record.write(f);
    f.close();
    for (int i = 0; i < fields.size(); i++) {
      _fields.push_back(fields[i]);
      _indices.push_back(mmap_sl());
    }
    open_fileW(f, (title + ".tbl").c_str());
    f.close();
    _n_records = 0;
    return string();
  }
  // SQL: INSERT INTO
  string insert_into(const vector<char *> &record) {
    fstream f;
    open_fileRW(f, (_title + ".tbl").c_str());
    vector<string> rec_str;
    for (int i = 0; i < _indices.size(); i++) {
      string temp = record[i];
      rec_str.push_back(temp);
      _indices[i][record[i]] += _n_records;
    }
    _table.push_back(rec_str);
    FileRecord rec = FileRecord(rec_str);
    _n_records++;
    rec.write(f);
    f.close();
    return string();
  }
  string insert_into(const vector<string> &row) {
    fstream f;
    open_fileRW(f, (_title + ".tbl").c_str());
    _table.push_back(row);
    // std::cout << _indices.size() << endl;
    for (int i = 0; i < _indices.size(); i++) {
      // cout << row[i] << " " << _n_records << endl;

      _indices[i][row[i]] += (_n_records);
    }
    FileRecord rec = FileRecord(row);
    _n_records++;
    rec.write(f);
    f.close();
    return string();
  }
  // SQL: SELECT
  Table select(const vector<string> &fields, const string &lhs,
               const string &op, const string &rhs) {
    vector<string> field = fields;
    if (fields[0] == "*") {
      field = _fields;
    }
    _selected = vector<long>();
    Table newTable = Table("hi", field);
    vector<int> actual_fields;
    for (int i = 0; i < field.size(); i++) {
      for (int j = 0; j < _fields.size(); j++) {
        if (fields[i] == _fields[j]) {
          actual_fields.push_back(j);
          break;
        }
      }
    }
    // std::cout << actual_fields << endl;
    string temp = lhs;
    mmap_sl::Iterator iter;
    RPN rpn;
    fstream f;
    FileRecord record;
    Queue<Token *> q;
    vector<string> vec(_fields.size(), "");
    // this evaluates the command
    for (int i = 0; i < _fields.size(); i++) {
      // cout << fields[2] << endl;
      if (lhs == _fields[i]) {
        // cout << lhs << " " << fields[i] << endl;
        // cout << i << endl;
        iter = _indices[i].begin();
        // std::cout << (*iter).key << endl;
        while (iter != _indices[i].end()) {
          temp = (*iter).key;
          if (rpn.eval_one(op, temp, rhs)) {
            // cout << ((*iter).value_list) << endl;
            for (int j = 0; j < (*iter).value_list.size(); j++) {
              open_fileRW(f, (_title + ".tbl").c_str());
              _selected.push_back((*iter).value_list[j]);
              record = FileRecord(vec);
              record.read(f, (*iter).value_list[j]);
              f.close();
              // std::cout << record.get_records() << endl;
              vector<char *> records = record.get_records();
              vector<string> insert_record;
              for (int k = 0; k < actual_fields.size(); k++) {
                // std::cout << k << endl;
                //  std::cout << actual_fields[k];
                insert_record.push_back(records[actual_fields[k]]);
              }
              newTable.insert_into(insert_record);
            }
          }
          q.clear_list();
          iter++;
        }
        break;
      }
    }
    bubbleSort(_selected);
    return newTable;
  }

  Table select(const vector<string> &fields,
               const vector<string> &expression = vector<string>()) {
    Queue<Token *> queue;
    for (int i = 0; i < expression.size(); i++) {
      if (expression[i] == "=" || expression[i] == "!=" ||
          expression[i] == "<" || expression[i] == "<=" ||
          expression[i] == ">" || expression[i] == ">=") {
        queue.push(new Relational(expression[i]));
      } else if (expression[i] == "(") {
        queue.push(new LeftParen());
      } else if (expression[i] == ")") {
        queue.push(new RightParen());
      } else if (expression[i] == "and" || expression[i] == "or" ||
                 expression[i] == "not") {
        queue.push(new Logical(expression[i]));
      } else {
        queue.push(new TokenStr(expression[i]));
      }
    }
    Table newTable;
    if (!queue.empty()) {
      ShuntingYard yard(queue);
      Queue<Token *> q = yard.postfix();
      newTable = select(fields, q);
    } else {
      newTable = select(fields, Queue<Token *>());
    }

    return newTable;
  }

  Table select(const vector<string> &fields, const Queue<Token *> &expression) {
    vector<string> field = fields;
    for (int i = 0; i < fields.size(); i++) {
      for (int j = 0; j < _fields.size(); j++) {
        if (_fields[j] == fields[i]) {
          field.push_back(fields[i]);
          break;
        }
      }
    }
    // cout << expression << endl;
    _selected = vector<long>();
    if (fields[0] == "*") {
      field = _fields;
    }
    Table newTable = Table("hi", field);
    vector<int> actual_fields;
    mmap_sl::Iterator iter;
    fstream f;
    FileRecord record;
    vector<string> vec(_fields.size(), "");
    for (int i = 0; i < field.size(); i++) {
      for (int j = 0; j < _fields.size(); j++) {
        if (field[i] == _fields[j]) {
          actual_fields.push_back(j);
          break;
        }
      }
    }
    if (expression.empty()) {
      iter = _indices[0].begin();
      while (iter != _indices[0].end()) {
        for (int j = 0; j < (*iter).value_list.size(); j++) {
          _selected.push_back((*iter).value_list[j]);
        }
        iter++;
      }
      for (int i = 0; i < _selected.size(); i++) {
        open_fileRW(f, (_title + ".tbl").c_str());
        record = FileRecord(vec);
        record.read(f, _selected[i]);
        f.close();
        // std::cout << record.get_records() << endl;
        vector<char *> records = record.get_records();
        vector<string> insert_record;
        for (int k = 0; k < actual_fields.size(); k++) {
          // std::cout << k << endl;
          //  std::cout << actual_fields[k];
          insert_record.push_back(records[actual_fields[k]]);
        }
        // std::cout << insert_record << endl;
        newTable.insert_into(insert_record);
      }
      // cout << _selected << endl;
      bubbleSort(_selected);
      return newTable;
    }
    Queue<Token *> q = expression;
    Stack<vector<long>> stack;
    Stack<Token *> token_stack;
    RPN rpn;
    // this evaluates the command
    while (!q.empty()) {
      Token *temp = q.front();
      q.pop();
      if (temp->TypeOf() == TOKENSTR) {
        token_stack.push(temp);
      }
      if (temp->TypeOf() == LOGIC) {
        vector<long> a = stack.top();
        stack.pop();
        vector<long> b = stack.top();
        stack.pop();
        // std::cout << a << endl
        //           << b << endl
        //           << temp->as_string()
        //           << rpn.evaluate_logic(temp->as_string(), a, b) << endl;
        stack.push(rpn.evaluate_logic(temp->as_string(), a, b));
      }
      if (temp->TypeOf() == RELATIONAL) {
        Token *a = token_stack.top();
        token_stack.pop();
        Token *b = token_stack.top();
        token_stack.pop();
        for (int i = 0; i < _fields.size(); i++) {
          // cout << fields[2] << endl;
          if (b->as_string() == _fields[i]) {
            // cout << lhs << " " << fields[i] << endl;
            // cout << i << endl;
            iter = _indices[i].begin();
            // std::cout << (*iter).key << endl;
            while (iter != _indices[i].end()) {
              string str = (*iter).key;
              if (rpn.eval_one(temp->as_string(), str, a->as_string())) {
                // cout << ((*iter).value_list) << endl;
                for (int j = 0; j < (*iter).value_list.size(); j++) {
                  _selected.push_back((*iter).value_list[j]);
                  vector<long> yuh = _selected;
                }
              }
              iter++;
            }
          }
        }
        stack.push(_selected);
        _selected = vector<long>();
      }
    }
    _selected = stack.top();
    for (int i = 0; i < _selected.size(); i++) {
      open_fileRW(f, (_title + ".tbl").c_str());
      record = FileRecord(vec);
      record.read(f, _selected[i]);
      f.close();
      // std::cout << record.get_records() << endl;
      vector<char *> records = record.get_records();
      vector<string> insert_record;
      for (int k = 0; k < actual_fields.size(); k++) {
        // std::cout << k << endl;
        //  std::cout << actual_fields[k];
        insert_record.push_back(records[actual_fields[k]]);
      }
      newTable.insert_into(insert_record);
    }
    bubbleSort(_selected);
    //  cout << _selected;
    return newTable;
  }
  // Get all selected record numbers
  vector<long> select_recnos() const {
    // sort(_selected[0], _selected[_selected.size() - 1]);
    return _selected;
  }
  // Print table
  friend ostream &operator<<(ostream &outs, const Table &t) {
    outs << "Table name: " << t._title << ", records: " << t._n_records
         << std::endl;

    outs << std::right << std::setw(25) << "record";

    for (int i = 0; i < t._fields.size(); ++i) {
      outs << std::right << std::setw(25) << t._fields[i];
    }

    outs << std::endl;

    for (int i = 0; i < t._n_records; ++i) {
      outs << std::right << std::setw(25) << i;
      for (int j = 0; j < t._table[i].size(); ++j) {

        outs << std::right << std::setw(25) << (t._table[i][j]);
      }

      outs << std::endl;
    }

    return outs;
  }
  // Get the title of the table
  string title() const { return _title; }
  // Get the fields of the table
  vector<string> get_fields() { return _fields; }
  // Get the number of records in the table
  long record_count() const { return _n_records; }
  //======================================
  // TODO: add more methods here as needed
  //======================================
private:
  // title of the table
  string _title;
  // ACTUAL TABLE CUH?!
  vector<vector<string>> _table;
  // fields of the table
  vector<string> _fields;
  // number of records in the table
  long _n_records;
  // selected records' numbers
  vector<long> _selected;
  vector<mmap_sl> _indices;
  //===========================================
  // TODO: add more data members here as needed
  //===========================================
  void bubbleSort(vector<long> &arr) {
    if (arr.size() == 0) {
      return;
    }
    for (int i = 0; i < arr.size() - 1; i++) {
      for (int j = 0; j < arr.size() - i - 1; j++) {
        if (arr[j] > arr[j + 1]) {
          int temp = arr[j];
          arr[j] = arr[j + 1];
          arr[j + 1] = temp;
        }
      }
    }
  }
};

#endif // TABLE_H