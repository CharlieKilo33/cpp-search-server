#include <iostream>
#include <string>

using namespace std;

template<typename F>
string BruteForce(F check) {
    string str;
    for (char a = 'A'; a <= 'Z'; a++) {
        str.push_back(a);
        for (char b = 'A'; b <= 'Z'; b++) {
            str.push_back(b);
            for (char c = 'A'; c <= 'Z'; c++) {
                str.push_back(c);
                for (char d = 'A'; d <= 'Z'; d++) {
                    str.push_back(d);
                    for(char e = 'A'; e <= 'Z'; e++){
                        str.push_back(e);
                        if(check(str)){
                            return str;
                        }
                        str.pop_back();
                    }
                    str.pop_back();
                }
                str.pop_back();
            }
            str.pop_back();
        }
        str.pop_back();
    }
    return str;
}

int main() {
    string pass = "ARTUR"s;
    auto check = [pass](const string &s) {
        return s == pass;
    };
    cout << BruteForce(check) << endl;
}