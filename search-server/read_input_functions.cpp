#include "read_input_functions.h"


std::string read_input_functions::ReadLine() {
  std::string s;
  getline(std::cin, s);
  return s;
}

int read_input_functions::ReadLineWithNumber() {
  int result;
  std::cin >> result;
  read_input_functions::ReadLine();
  return result;
}