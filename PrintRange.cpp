#include <iostream>
#include <vector>
#include <set>

template<typename Iterator>
void PrintRange(Iterator iterator1, Iterator iterator2){
    for(auto it = iterator1; it != iterator2; ++it){
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}


int main() {
    std::cout << "Test1" << std::endl;
    std::set<int> test1 = {1, 1, 1, 2, 3, 4, 5, 5};
    PrintRange(test1.begin(), test1.end());
    std::cout << "Test2" << std::endl;
    std::vector<int> test2 = {}; // пустой контейнер
    PrintRange(test2.begin(), test2.end());
    std::cout << "End of tests" << std::endl;
}