#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

const int MAX_RESULT_DOCUMENT_COUNT = 5;

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result = 0;
    cin >> result;
    ReadLine();
    return result;
}

vector<string> SplitIntoWords(const string &text) {
    vector<string> words;
    string word;
    for (const char c: text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

struct Document {
    int id = 0;
    double relevance = 0;
};

class SearchServer {
public:
    void SetStopWords(const string &text) {
        for (const string &word: SplitIntoWords(text)) {
            stop_words_.insert(word);
        }
    }

    void AddDocument(int document_id, const string &document) {
        const vector<string> words = SplitIntoWordsNoStop(document);
        document_count_++;
        double w_size = words.size();
        for (const string &word: words) {
            word_to_document_freqs_[word].insert(
                    {document_id, count(words.begin(), words.end(), word) * 1. / w_size});

        }
    }

    vector<Document> FindTopDocuments(const string &raw_query) const {
        const QueryWords query_words = ParseQuery(raw_query);
        auto matched_documents = FindAllDocuments(query_words);

        sort(matched_documents.begin(), matched_documents.end(),
             [](const Document &lhs, const Document &rhs) {
                 return lhs.relevance > rhs.relevance;
             });
        if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        }
        return matched_documents;
    }

private:
    struct QueryWords {
        set<string> plus_words;
        set<string> minus_words;
    };

    map<string, map<int, double>> word_to_document_freqs_;
    set<string> stop_words_;
    int document_count_ = 0;

    bool IsStopWord(const string &word) const {
        return stop_words_.count(word) > 0;
    }

    vector<string> SplitIntoWordsNoStop(const string &text) const {
        vector<string> words;
        for (const string &word: SplitIntoWords(text)) {
            if (!IsStopWord(word)) {
                words.push_back(word);
            }
        }
        return words;
    }

    QueryWords ParseQuery(const string &text) const {
        QueryWords query_words;
        for (string &word: SplitIntoWordsNoStop(text)) {
            if (word[0] == '-') {
                word.erase(0, 1);
                query_words.minus_words.insert(word);
            } else {
                query_words.plus_words.insert(word);
            }
        }
        return query_words;
    }

    vector<Document> FindAllDocuments(const QueryWords &query_words) const {
        vector<Document> matched_documents;
        map<int, double> id_rel;

        for (const auto &word: query_words.plus_words) {
            if (word_to_document_freqs_.count(word)) {
                auto our_map = word_to_document_freqs_.at(word);
                for (const auto &[doc_id, tf]: our_map) {
                    id_rel[doc_id] += tf * log(static_cast<double>(document_count_) / our_map.size());
                }
            }
        }

        for (const auto &word: query_words.minus_words) {
            if (word_to_document_freqs_.count(word)) {
                for (const auto &[word_name, id]: word_to_document_freqs_) {
                    for (int i = 0; i < id.size(); ++i) {
                        id_rel.erase(i);
                    }
                }
            }
        }

        for (const auto &[id, rel]: id_rel) {
            matched_documents.push_back({id, rel});
        }

        return matched_documents;
    }
};

SearchServer CreateSearchServer() {
    SearchServer search_server;
    search_server.SetStopWords(ReadLine());

    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        search_server.AddDocument(document_id, ReadLine());
    }

    return search_server;
}

int main() {
    const SearchServer search_server = CreateSearchServer();

    const string query = ReadLine();
    for (const auto &[document_id, relevance]: search_server.FindTopDocuments(query)) {
        cout << "{ document_id = "s << document_id << ", "
             << "relevance = "s << relevance << " }"s << endl;
    }
}