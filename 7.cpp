#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <random>

using namespace std;

template<typename Iterator>
void PrintRange(Iterator iterator1, Iterator iterator2){
    for(auto it = iterator1; it != iterator2; ++it){
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}

template <typename RandomIt>
void Merge(RandomIt range_begin, RandomIt range_mid, RandomIt range_end){
    std::vector<typename RandomIt::value_type> left_range(range_begin, range_mid);
    std::vector<typename RandomIt::value_type> right_range(range_mid, range_end);

    RandomIt left_it = left_range.begin();
    RandomIt right_it = right_range.begin();

    while(left_it != left_range.end() && right_it != right_range.end()){
        if(*left_it < *right_it){
            *range_begin = *left_it;
            ++left_it;
        } else {
            *range_begin = *right_it;
            ++right_it;
        }
        ++range_begin;
    }

    range_begin = std::copy(left_it, left_range.end(), range_begin);
    range_begin = std::copy(right_it, right_range.end(), range_begin);
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
    auto distance = std::distance(range_begin, range_end);

    if(distance < 2){
        return;
    }

    RandomIt range_middle = range_begin + distance / 2;

    MergeSort(range_begin, range_middle);
    MergeSort(range_middle, range_end);

    Merge(range_begin, range_middle, range_end);


}

int main() {
    vector<int> test_vector(10);
    // iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
    // Заполняет диапазон последовательно возрастающими значениями
    iota(test_vector.begin(), test_vector.end(), 1);

    // shuffle   -> https://ru.cppreference.com/w/cpp/algorithm/random_shuffle
    // Перемешивает элементы в случайном порядке
    random_device rd;
    mt19937 g(rd());
    shuffle(test_vector.begin(), test_vector.end(), g);

    // Выводим вектор до сортировки
    PrintRange(test_vector.begin(), test_vector.end());
    // Сортируем вектор с помощью сортировки слиянием
    MergeSort(test_vector.begin(), test_vector.end());
    // Выводим результат
    PrintRange(test_vector.begin(), test_vector.end());
    return 0;
}