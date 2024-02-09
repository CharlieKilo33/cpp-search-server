#pragma once

#include <array>
#include <stdexcept>

template <typename T, size_t N>
class StackVector {
 public:
  explicit StackVector(size_t a_size = 0) {
    if (a_size > capacity_){
      throw std::invalid_argument("size > max_size");
    }
    size_ = a_size;
  }

  T& operator[](size_t index) {
    return stack_vector_[index];
  }
  const T& operator[](size_t index) const {
    return stack_vector_[index];
  }

  auto begin(){
    return stack_vector_.begin();
  }
  auto end() {
    return stack_vector_.begin() + size_;
  }
  auto begin() const {
    return stack_vector_.cbegin();
  }
  auto end() const {
    return stack_vector_.cbegin() + size_;
  }

  size_t Size() const {
    return size_;
  }

  size_t Capacity() const {
    return capacity_;
  }

  void PushBack(const T& value) {
    if(size_ == capacity_){
      throw std::overflow_error("size == max_size");
    }
    stack_vector_[size_] = value;
    ++size_;
  }

  T PopBack() {
    if(size_ == 0){
      throw std::underflow_error("stack is empty");
    }
    --size_;
    return stack_vector_[size_];
  }
 private:
  size_t size_ = 0;
  size_t capacity_ = N;
  std::array<T, N> stack_vector_;
};
