#ifndef FILE_RECORD_H
#define FILE_RECORD_H

#include <cstring>  // strncpy
#include <fstream>  // fstream
#include <iomanip>  // setw, right
#include <iostream> // cout, endl
#include <vector>   // vector

using namespace std;

class FileRecord {
public:
  // When construct a FileRecord, it's either empty or it contains a word
  FileRecord() {
    recno = 0;
    // _records[0] => [ | '\0' | G | a | r | b | a | g | e | ]
  }

  FileRecord(string s) {
    char *temp = new char[MAX];
    std::strncpy(temp, s.c_str(), MAX);
    _records.push_back(temp);
    recno++;
  }

  FileRecord(char str[]) { _records.push_back(str); }

  FileRecord(vector<string> v) {
    for (int i = 0; i < v.size(); i++) {
      char *temp = new char[MAX];
      std::strncpy(temp, v[i].c_str(), MAX);

      _records.push_back(temp);
      recno++;
    }
  }

  // Returns the record number
  long write(fstream &outs) {
    // Take the Record r and write it into file f and return the record number
    // of this Record
    // r.write(f); calls this function

    // Write to the end of the file
    outs.seekg(0, outs.end);
    // Retrieves the current position of the file pointer
    long pos = outs.tellp();
    // Insert the size of record items into file
    for (int i = 0; i < _records.size(); i++) {
      outs.write(_records[i], MAX);
    }
    // Return the record number
    return pos / (MAX * _records.size());
  }
  // Returns the number of bytes read = MAX, or zero if read passed the end of
  // file
  long read(fstream &ins, long recno) {
    // Save sixth record in file to Record r and returns the number of bytes
    // read
    // r.read(f, 6); calls this function

    // Calculate the position of the record in the file
    long pos = recno * MAX * (_records.size());
    // Set the file pointer to the pos starting from the beginning of the file
    ins.seekg(pos, ios_base::beg);
    long count = 0;
    // Read the record from the file
    for (int i = 0; i < _records.size(); i++) {
      ins.read(_records[i], MAX);
      _records[i][MAX - 1] = '\0';
      count += ins.gcount();
    }

    // Set the end of cstring with null
    // For example: _records[] => [zero'\0' trash ... trash
    // Return the number of bytes read
    return count;
  }
  // Returns the record
  vector<char *> get_records() { return _records; }

  // Overload the << operator to print a FileRecord
  friend ostream &operator<<(ostream &outs, const FileRecord &r) {
    for (char *_record : r._records) {
      outs << setw(MAX / 4) << right << _record;
    }
    return outs;
  }

  // =====================================
  // TODO: Add more methods here if needed
  // =====================================

private:
  // The maximum size of the record
  static const int MAX = 100;
  // The record number
  int recno;
  // The record vector
  vector<char *> _records;
};

#endif