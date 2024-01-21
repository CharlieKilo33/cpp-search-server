#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using filesystem::path;

path operator ""_p(const char *data, std::size_t sz) {
  return path(data, data + sz);
}

void PrintTree(ostream &dst, const path &p, const filesystem::file_status &status, int offset) {
  for (int i = 0; i < offset; i++) {
    dst << "  ";
  }

  dst << p.filename().string() << endl;

  if (status.type() == filesystem::file_type::directory) {
    vector<pair<path, filesystem::file_status>> entries;
    for (const auto &entry : filesystem::directory_iterator(p)) {
      entries.emplace_back(entry.path(), entry.status());
    }

    sort(entries.begin(),
         entries.end(),
         [](const pair<path, filesystem::file_status> &a, const pair<path, filesystem::file_status> &b) {
           return a.first.filename().string() > b.first.filename().string();
         });

    for (const auto &[entry, status] : entries) {
      PrintTree(dst, entry, status, offset + 1);
    }
  }
}

void PrintTree(ostream &dst, const path &p) {
  PrintTree(dst, p, filesystem::status(p), 0);
}

int main() {
  error_code err;
  filesystem::remove_all("test_dir", err);
  filesystem::create_directories("test_dir"_p / "a"_p, err);
  filesystem::create_directories("test_dir"_p / "b"_p, err);

  ofstream("test_dir"_p / "b"_p / "f1.txt"_p);
  ofstream("test_dir"_p / "b"_p / "f2.txt"_p);
  ofstream("test_dir"_p / "a"_p / "f3.txt"_p);

  ostringstream out;
  PrintTree(out, "test_dir"_p);
  assert(out.str() ==
      "test_dir\n"
      "  b\n"
      "    f2.txt\n"
      "    f1.txt\n"
      "  a\n"
      "    f3.txt\n"s
  );
}