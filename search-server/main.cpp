// Решите загадку: Сколько чисел от 1 до 1000 содержат как минимум одну цифру 3?
// Напишите ответ здесь: 271

#include <iostream>
#include <string>

int main(){
    int count = 0;
    for(int i = 1; i < 1000; ++i){
        for(int j = 0; j < std::to_string(i).size(); ++j){
            if(std::to_string(i)[j] == '3'){
                ++count;
                break;
            }
        }
    }

    std::cout << "Answer: " << count << '\n';
}

// Закомитьте изменения и отправьте их в свой репозиторий.
