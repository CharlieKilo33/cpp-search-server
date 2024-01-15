#pragma once
#include "iostream"
#include "vector"
#include "string"
#include "set"

#ifndef PRACTICUM_SEARCH_SERVER_READ_INPUT_FUNCTIONS_H_
#define PRACTICUM_SEARCH_SERVER_READ_INPUT_FUNCTIONS_H_


class read_input_functions {
 public:
  static std::string ReadLine();
  static int ReadLineWithNumber();
};

#endif //PRACTICUM_SEARCH_SERVER_READ_INPUT_FUNCTIONS_H_
