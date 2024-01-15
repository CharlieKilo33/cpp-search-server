#pragma once
#include "vector"
#include "string_processing.h"


#ifndef PRACTICUM_SEARCH_SERVER_PAGINATOR_H_
#define PRACTICUM_SEARCH_SERVER_PAGINATOR_H_

template<typename Iterator>
class IteratorRange {
 public:
  IteratorRange(Iterator it_begin, Iterator it_end_) : it_begin_(it_begin), it_end_(it_end_) {};

  [[nodiscard]] Iterator begin() const {
    return it_begin_;
  }

  [[nodiscard]] Iterator end() const {
    return it_end_;
  }

  [[maybe_unused]] [[nodiscard]] size_t size() const {
    return distance(it_begin_, it_end_);
  }

 private:
  Iterator it_begin_, it_end_;
};

template<typename Iterator>
class Paginator {
 public:
  Paginator(Iterator it_begin, Iterator it_end, size_t page_size) {
    for (auto i = it_begin, temp_iter = it_begin; i < it_end;) {
      auto length = distance(i, it_end);
      if (length >= page_size) {
        advance(temp_iter, page_size);
      } else {
        advance(temp_iter, length);
      }
      pages_in_vector_.push_back(IteratorRange(i, temp_iter));
      i = temp_iter;
    }
  };

  [[nodiscard]] auto begin() const {
    return pages_in_vector_.begin();
  };

  [[nodiscard]] auto end() const {
    return pages_in_vector_.end();
  };

  [[maybe_unused]] [[nodiscard]] size_t size() const {
    return pages_in_vector_.size();
  };


 private:
  std::vector<IteratorRange<Iterator>> pages_in_vector_;
};



#endif //PRACTICUM_SEARCH_SERVER_PAGINATOR_H_
