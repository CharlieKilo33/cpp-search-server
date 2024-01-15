#pragma once
#include "search_server.h"
#include "document.h"
#include "string_processing.h"
#include "vector"
#include "string"
#include "deque"

#ifndef PRACTICUM_SEARCH_SERVER_REQUEST_QUEUE_H_
#define PRACTICUM_SEARCH_SERVER_REQUEST_QUEUE_H_

class RequestQueue {
 public:
  explicit RequestQueue(const SearchServer &search_server);

  template<typename DocumentPredicate>
  std::vector<Document> AddFindRequest(const std::string &raw_query, DocumentPredicate document_predicate);

  std::vector<Document> AddFindRequest(const std::string &raw_query, DocumentStatus status);

  std::vector<Document> AddFindRequest(const std::string &raw_query);

  [[nodiscard]] int GetNoResultRequests() const;

 private:
  const SearchServer &search_server_;
  int no_results = 0;
  struct QueryResult {
    std::string query;
    std::vector<Document> results;
  };
  std::deque<QueryResult> requests_;
  const static int min_in_day_ = 1440;
  void AddResult(QueryResult &result);
};

template<typename DocumentPredicate>
std::vector<Document> RequestQueue::AddFindRequest(const std::string &raw_query,
                                                    DocumentPredicate document_predicate) {
  QueryResult result;
  result.query = raw_query;
  result.results = search_server_.FindTopDocuments(raw_query, document_predicate);
  AddResult(result);
  return result.results;
}


#endif //PRACTICUM_SEARCH_SERVER_REQUEST_QUEUE_H_
