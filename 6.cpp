#include <iostream>

int IsPowOfTwo(int num){
    if(num == 1){
        return true;
    }
    if(num % 2 != 0 || num == 0){
        return false;
    }
    return IsPowOfTwo(num / 2);
}

int main(){
    int result = IsPowOfTwo(1);
    std::cout << result << '\n';
}