#include "request_queue.h"

RequestQueue::RequestQueue(const SearchServer &search_server) : search_server_(search_server) {}

std::vector<Document> RequestQueue::AddFindRequest(const std::string &raw_query, DocumentStatus status) {
    QueryResult result;
    result.query = raw_query;
    result.results = search_server_.FindTopDocuments(raw_query, status);
    AddResult(result);
    return result.results;
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string &raw_query) {
    QueryResult result;
    result.query = raw_query;
    result.results = search_server_.FindTopDocuments(raw_query);
    AddResult(result);
    return result.results;
}

int RequestQueue::GetNoResultRequests() const {
    return no_results;
}

void RequestQueue::AddResult(RequestQueue::QueryResult &result) {
    requests_.push_back(result);
    if (result.results.empty()) {
        ++no_results;
    }
    if (requests_.size() > min_in_day_) {
        if (requests_.front().results.empty()) {
            --no_results;
        }
        requests_.pop_front();
    }
}
