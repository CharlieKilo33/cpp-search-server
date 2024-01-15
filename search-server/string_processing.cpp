#include "string_processing.h"

std::vector<std::string> string_processing::SplitIntoWords(const std::string &text) {
    std::vector<std::string> words;
    std::string word;
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

std::ostream &operator<<(std::ostream &out, const Document &document) {
    out << "{ document_id = " << document.id << ", relevance = " << document.relevance << ", rating = "
        << document.rating << " }";
    return out;
}





