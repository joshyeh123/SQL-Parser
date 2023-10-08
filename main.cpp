#include "includes/sql/sql.h"
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  SQL sql;
  string line;
  Table t;
  std::cout << "Type 'stop' to end code" << std::endl;
  getline(std::cin, line);
  while (line != "stop") {
    t = sql.command(line);
    cout << t << endl;
    cout << sql.select_recnos() << endl;
    getline(std::cin, line);
    std::cout << "Type 'stop' to end code" << std::endl;
  }
  return 0;
}
