#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using filesystem::path;

path operator ""_p(const char *data, std::size_t sz) {
  return path(data, data + sz);
}

bool Preprocess(const path &in_file, const path &out_file, const vector<path> &include_directories);

bool FileProcess(const path& out_file, const vector<path>& include_directories, const path& file_name) {
  for (const auto& dir : include_directories) {
    path file_path = dir / file_name;
    if (filesystem::exists(file_path)) {
      Preprocess(file_path, out_file, include_directories);
      return true;
    }
  }
  return false;
}

bool Preprocess(const path& in_file, const path& out_file, const vector<path>& include_directories) {
  regex f_dir(R"/(\s*#\s*include\s*"([^"]*)"\s*)/");
  regex l_dir(R"/(\s*#\s*include\s*<([^>]*)>\s*)/");

  ifstream in(in_file);
  if(!in.is_open()){
    return false;
  }

  ofstream out(out_file, ios::app);

  string line;
  int line_num = 0;

  while (getline(in, line)) {
    ++line_num;

    smatch match_f, match_l;

    if (regex_match(line, match_f, f_dir)) {
      path file_name = string(match_f[1]);
      path file_path = in_file.parent_path() / file_name;
      ifstream f_in(file_path);
      if (f_in.is_open()) {
        Preprocess(file_path, out_file, include_directories);
        f_in.close();
      } else {
        if (!FileProcess(out_file, include_directories, file_name)) {
          cout << "unknown include file " << file_name.string() << " at file " << in_file.string()
               << " at line " << line_num << endl;
          return false;
        }
      }
    } else if (regex_match(line, match_l, l_dir)) {
      path file_name = string(match_l[1]);
      if (!FileProcess(out_file, include_directories, file_name)) {
        cout << "unknown include file " << file_name.string() << " at file " << in_file.string()
             << " at line " << line_num << endl;
        return false;
      }
    } else {
      out << line << endl;
    }
  }
  return true;
}

string GetFileContents(string file) {
  ifstream stream(file);

  // конструируем string по двум итераторам
  return {(istreambuf_iterator<char>(stream)), istreambuf_iterator<char>()};
}

void Test() {
  error_code err;
  filesystem::remove_all("sources"_p, err);
  filesystem::create_directories("sources"_p / "include2"_p / "lib"_p, err);
  filesystem::create_directories("sources"_p / "include1"_p, err);
  filesystem::create_directories("sources"_p / "dir1"_p / "subdir"_p, err);

  {
    ofstream file("sources/a.cpp");
    file << "// this comment before include\n"
            "#include \"dir1/b.h\"\n"
            "// text between b.h and c.h\n"
            "#include \"dir1/d.h\"\n"
            "\n"
            "int SayHello() {\n"
            "    cout << \"hello, world!\" << endl;\n"
            "#   include<dummy.txt>\n"
            "}\n"s;
  }
  {
    ofstream file("sources/dir1/b.h");
    file << "// text from b.h before include\n"
            "#include \"subdir/c.h\"\n"
            "// text from b.h after include"s;
  }
  {
    ofstream file("sources/dir1/subdir/c.h");
    file << "// text from c.h before include\n"
            "#include <std1.h>\n"
            "// text from c.h after include\n"s;
  }
  {
    ofstream file("sources/dir1/d.h");
    file << "// text from d.h before include\n"
            "#include \"lib/std2.h\"\n"
            "// text from d.h after include\n"s;
  }
  {
    ofstream file("sources/include1/std1.h");
    file << "// std1\n"s;
  }
  {
    ofstream file("sources/include2/lib/std2.h");
    file << "// std2\n"s;
  }

  assert((!Preprocess("sources"_p / "a.cpp"_p, "sources"_p / "a.in"_p,
                      {"sources"_p / "include1"_p, "sources"_p / "include2"_p})));

  ostringstream test_out;
  test_out << "// this comment before include\n"
              "// text from b.h before include\n"
              "// text from c.h before include\n"
              "// std1\n"
              "// text from c.h after include\n"
              "// text from b.h after include\n"
              "// text between b.h and c.h\n"
              "// text from d.h before include\n"
              "// std2\n"
              "// text from d.h after include\n"
              "\n"
              "int SayHello() {\n"
              "    cout << \"hello, world!\" << endl;\n"s;

  assert(GetFileContents("sources/a.in"s) == test_out.str());
}

int main() {
  Test();
}