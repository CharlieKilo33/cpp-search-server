#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename T>
class ScopedPtr {
 public:
  ScopedPtr() = default;

  explicit ScopedPtr(T* raw_ptr) noexcept
      : ptr_(raw_ptr) {
  }

  // Запрещаем копирование указателя
  ScopedPtr(const ScopedPtr&) = delete;

  ~ScopedPtr() {
    delete ptr_;
  }

  T* GetRawPtr() const noexcept {
    return ptr_;
  }

  T* Release() noexcept {
    T* p = ptr_;
    ptr_ = nullptr;
    return p;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }

  T* operator->() const {
    using namespace std::literals;
    if (!ptr_) {
      throw std::logic_error("Scoped ptr is null"s);
    }
    return ptr_;
  }

  T& operator*() const {
    using namespace std::literals;
    if (!ptr_) {
      throw std::logic_error("Scoped ptr is null"s);
    }
    return *ptr_;
  }

 private:
  T* ptr_ = nullptr;
};

// Используйте эту заготовку PtrVector или замените её на свою реализацию
template <typename T>
class PtrVector {
 public:
  PtrVector() = default;

  // Создаёт вектор указателей на копии объектов из other
  PtrVector(const PtrVector& other) {
    // Резервируем место в vector-е для хранения нужного количества элементов
    // Благодаря этому при push_back не будет выбрасываться исключение
    items_.reserve(other.items_.size());

    try {
      for (auto p : other.items_) {
        // Копируем объект, если указатель на него ненулевой
        auto p_copy = p ? new T(*p) : nullptr;  // new может выбросить исключение

        // Не выбросит исключение, т. к. в vector память уже зарезервирована
        items_.push_back(p_copy);
      }
    } catch (...) {
      // удаляем элементы в векторе и перевыбрасываем пойманное исключение
      DeleteItems();
      throw;
    }
  }

  // Деструктор удаляет объекты в куче, на которые ссылаются указатели,
  // в векторе items_
  ~PtrVector() {
    DeleteItems();
  }

  // Возвращает ссылку на вектор указателей
  vector<T*>& GetItems() noexcept {
    return items_;
  }

  // Возвращает константную ссылку на вектор указателей
  vector<T*> const& GetItems() const noexcept {
    return items_;
  }

  PtrVector& operator=(const PtrVector& rhs){
    if(this != &rhs){
      auto rhs_copy(rhs);
      std::swap(items_, rhs_copy.items_);
    }
    return *this;
  }

  void DeleteItems() noexcept {
    for (auto p : items_) {
      delete p;
    }
  }

 private:
  vector<T*> items_;
};