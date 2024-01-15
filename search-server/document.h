#pragma once
#include "iostream"
#ifndef PRACTICUM_SEARCH_SERVER_DOCUMENT_H_
#define PRACTICUM_SEARCH_SERVER_DOCUMENT_H_

struct Document {
  Document() = default;

  Document(int id, double relevance, int rating);

  int id = 0;
  double relevance = 0.0;
  int rating = 0;
};

enum class DocumentStatus {
  ACTUAL,
  IRRELEVANT [[maybe_unused]],
  BANNED [[maybe_unused]],
  REMOVED [[maybe_unused]],
};




#endif //PRACTICUM_SEARCH_SERVER_DOCUMENT_H_
