#pragma once

#include "array_ptr.h"
#include <cassert>
#include <initializer_list>

template <typename Type>
class SimpleVector {
 public:
  using Iterator = Type*;
  using ConstIterator = const Type*;

  SimpleVector() noexcept = default;

  // Создаёт вектор из size элементов, инициализированных значением по умолчанию
  explicit SimpleVector(size_t size) {
    capacity_ = size;
    size_ = size;
    for(size_t i = 0; i < size; ++i){
      ScopedPtr<Type> ptr_value(new Type(0));
      items_.GetItems().resize(size, ptr_value.GetRawPtr());
      ptr_value.Release();
    }
  }

  // Создаёт вектор из size элементов, инициализированных значением value
  SimpleVector(size_t size, const Type& value) {
    capacity_ = size;
    size_ = size;
    ScopedPtr<Type> ptr_value(new Type(value));
    for(size_t i = 0; i < size; ++i){
      items_.GetItems().push_back(ptr_value.GetRawPtr());
    }
    ptr_value.Release();
  }

  // Создаёт вектор из std::initializer_list
  SimpleVector(std::initializer_list<Type> init) {
    size_ = init.size();
    capacity_ = init.size();
    for(auto c : init){
      ScopedPtr<Type> ptr_value(new Type(c));
      items_.GetItems().push_back(ptr_value.GetRawPtr());
      ptr_value.Release();
    }
  }

  // Возвращает количество элементов в массиве
  size_t GetSize() const noexcept {
    return size_;
  }

  // Возвращает вместимость массива
  size_t GetCapacity() const noexcept {
    return capacity_;
  }

  // Сообщает, пустой ли массив
  bool IsEmpty() const noexcept {
    return size_ == 0;
  }

  // Возвращает ссылку на элемент с индексом index
  Type& operator[](size_t index) noexcept {
    return *items_.GetItems()[index];
  }

  // Возвращает константную ссылку на элемент с индексом index
  const Type& operator[](size_t index) const noexcept {
    return *items_.GetItems()[index];
  }

  // Возвращает константную ссылку на элемент с индексом index
  // Выбрасывает исключение std::out_of_range, если index >= size
  Type& At(size_t index) {
    if(index >= size_){
      throw std::out_of_range("index >= size");
    }
    return *items_.GetItems()[index];
  }

  // Возвращает константную ссылку на элемент с индексом index
  // Выбрасывает исключение std::out_of_range, если index >= size
  const Type& At(size_t index) const {
    if(index >= size_){
      throw std::out_of_range("index >= size");
    }
    return *items_.GetItems()[index];
  }

  // Обнуляет размер массива, не изменяя его вместимость
  void Clear() noexcept {
    size_ = 0;
    items_.DeleteItems();
  }

  // Изменяет размер массива.
  // При увеличении размера новые элементы получают значение по умолчанию для типа Type
  void Resize(size_t new_size) {
    if(new_size > capacity_){
      capacity_ = new_size * 2;
    }
    size_t temp = size_;
    while(size_ != new_size - 1){
      ScopedPtr<Type> ptr_value(new Type(0));
      items_.GetItems().push_back(ptr_value.GetRawPtr());
      ptr_value.Release();
    }
  }

  // Возвращает итератор на начало массива
  // Для пустого массива может быть равен (или не равен) nullptr
  Iterator begin() noexcept {
    return *items_.GetItems().begin();
  }

  // Возвращает итератор на элемент, следующий за последним
  // Для пустого массива может быть равен (или не равен) nullptr
  Iterator end() noexcept {
    return *items_.GetItems().end();
  }

  // Возвращает константный итератор на начало массива
  // Для пустого массива может быть равен (или не равен) nullptr
  ConstIterator begin() const noexcept {
    return *items_.GetItems().begin();
  }

  // Возвращает итератор на элемент, следующий за последним
  // Для пустого массива может быть равен (или не равен) nullptr
  ConstIterator end() const noexcept {
    return *items_.GetItems().end();
  }

  // Возвращает константный итератор на начало массива
  // Для пустого массива может быть равен (или не равен) nullptr
  ConstIterator cbegin() const noexcept {
    return *items_.GetItems().cbegin();
  }

  // Возвращает итератор на элемент, следующий за последним
  // Для пустого массива может быть равен (или не равен) nullptr
  ConstIterator cend() const noexcept {
    return *items_.GetItems().cend();
  }
 private:
  PtrVector<Type> items_;

  size_t size_ = 0;
  size_t capacity_ = 0;
};