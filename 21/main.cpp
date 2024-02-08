#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <unordered_map>
#include <deque>
#include <algorithm>

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target) {
        strings_.emplace_back(source);
        strings_.emplace_back(target);
        forward_translations_[strings_[strings_.size() - 2]] = strings_[strings_.size() - 1];
        backward_translations_[strings_[strings_.size() - 1]] = strings_[strings_.size() - 2];
    }

    string_view TranslateForward(string_view source) const {
        if(forward_translations_.count(source)){
            return forward_translations_.at(source);
        }
        return "";
    }

    string_view TranslateBackward(string_view target) const {
        if(backward_translations_.count(target)){
            return backward_translations_.at(target);
        }
        return "";
    }

private:
    unordered_map<string_view, string_view> forward_translations_;
    unordered_map<string_view, string_view> backward_translations_;
    deque<string> strings_;
};


void TestSimple() {
    Translator translator;
    string test = "loh";
    translator.Add(test, string("lol"s));
    test = "";
    auto test1 = translator.TranslateForward("loh");
    translator.Add(string("okno"s), string("window"s));
    translator.Add(string("stol"s), string("table"s));

    assert(translator.TranslateForward("okno"s) == "window"s);
    assert(translator.TranslateBackward("table"s) == "stol"s);
    assert(translator.TranslateForward("table"s) == ""s);
}

int main() {
    TestSimple();
}