#include <string>
#include <list>

using namespace std;

class Editor {
 public:
  Editor() = default;
  // сдвинуть курсор влево
  void Left() {
    if (it_ == text_.begin()) {
      return;
    }
    it_--;
  }
  // сдвинуть курсор вправо
  void Right() {
    if (it_ == text_.end()) {
      return;
    }
    it_++;
  }
  // вставить символ token
  void Insert(char token) {
    text_.insert(it_, token);
  }
  // вырезать не более tokens символов, начиная с текущей позиции курсора
  void Cut(size_t tokens = 1) {
    inserted_text_.clear();

    if(static_cast<int>(tokens) > static_cast<int>(distance(it_, text_.end()))){
      tokens = distance(it_, text_.end());
    }

    auto copy_it = next(it_, static_cast<int>(tokens));
    inserted_text_.insert(inserted_text_.begin(), it_, copy_it);
    it_ = text_.erase(it_, copy_it);
  }
  // cкопировать не более tokens символов, начиная с текущей позиции курсора
  void Copy(size_t tokens = 1) {
    inserted_text_.clear();

    if(static_cast<int>(tokens) > static_cast<int>(distance(it_, text_.end()))){
      tokens = distance(it_, text_.end());
    }

    auto copy_it = next(it_, static_cast<int>(tokens));
    inserted_text_.insert(inserted_text_.begin(), it_, copy_it);
  }
  // вставить содержимое буфера в текущую позицию курсора
  void Paste() {
    if(inserted_text_.empty()){
      return;
    }
    text_.insert(it_, inserted_text_.begin(), inserted_text_.end());
  }
  // получить текущее содержимое текстового редактора
  string GetText() const {
    string text;
    for(char c : text_){
      text.push_back(c);
    }
    return text;
  }

 private:
  list<char> text_;
  list<char> inserted_text_;
  list<char>::iterator it_ = text_.begin();
};

int main() {
  Editor editor;
  const string text = "he123"s;
  for (char c : text) {
    editor.Insert(c);
  }
  editor.Left();
  editor.Left();
  editor.Cut(4);
  editor.Insert('a');
  editor.Left();
  editor.Left();
  editor.Left();
  editor.Copy(3);
  string res = editor.GetText();
}