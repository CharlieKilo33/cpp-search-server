#pragma once
#include "document.h"
#include "paginator.h"
#include <iostream>
#include "set"
#include "string"
#include "vector"


#ifndef PRACTICUM_SEARCH_SERVER_STRING_PROCESSING_H_
#define PRACTICUM_SEARCH_SERVER_STRING_PROCESSING_H_



class string_processing{
 public:
  static std::vector<std::string> SplitIntoWords(const std::string &text);

  template<typename StringContainer>
  static std::set<std::string> MakeUniqueNonEmptyStrings(const StringContainer &strings);
};


template<typename StringContainer>
std::set<std::string> string_processing::MakeUniqueNonEmptyStrings(const StringContainer &strings) {
  std::set<std::string> non_empty_strings;
  for (const std::string &str : strings) {
    if (!str.empty()) {
      non_empty_strings.insert(str);
    }
  }
  return non_empty_strings;
}

std::ostream &operator<<(std::ostream &out, const Document &document);

template<typename Iterator>
std::ostream &operator<<(std::ostream &out, const IteratorRange<Iterator> &pages) {
  for (auto i = pages.begin(); i != pages.end(); ++i) {
    out << *i;
  }
  return out;
}

template <typename Container>
auto Paginate(const Container &c, std::size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}

#endif //PRACTICUM_SEARCH_SERVER_STRING_PROCESSING_H_
