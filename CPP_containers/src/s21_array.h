#ifndef S21_SRC_ARRAY_H
#define S21_SRC_ARRAY_H

#include <limits>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a) noexcept;
  ~array();
  array<T, N> &operator=(array<T, N> &&a);
  array<T, N> &operator=(const array<T, N> &a);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iterator data();

  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void swap(array &other);
  void fill(const_reference value);

 private:
  size_type size_ = N;
  value_type arr_[N ? N : 1] = {};
};

template <typename T, size_t N>
inline array<T, N>::array() : size_(N) {}

template <typename T, size_t N>
inline array<T, N>::array(std::initializer_list<value_type> const &items)
    : array() {
  for (size_type i = 0; i < items.size(); ++i) {
    arr_[i] = *(items.begin() + i);
  }
}

template <typename T, size_t N>
inline array<T, N>::array(const array &a) {
  for (size_type i = 0; i < size_; ++i) {
    arr_[i] = a.arr_[i];
  }
}

template <typename T, size_t N>
inline array<T, N>::array(array &&a) noexcept : array(a) {}

template <typename T, size_t N>
inline array<T, N>::~array() {}

template <typename T, size_t N>
inline array<T, N> &array<T, N>::operator=(array<T, N> &&a) {
  if (this != &a) {
    for (size_type i = 0; i < size_; ++i) {
      arr_[i] = a.arr_[i];
    }
  }
  return *this;
}

template <typename T, std::size_t N>
inline array<T, N> &array<T, N>::operator=(const array<T, N> &a) {
  std::copy(a.arr_, a.arr_ + N, arr_);
  return *this;
}

template <typename T, size_t N>
inline typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= size_ || size_ == 0) {
    throw std::out_of_range("Index out of array range");
  }

  return arr_[pos];
}

template <typename T, size_t N>
inline typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of array range");
  }

  return *(arr_ + pos);
}

template <typename T, size_t N>
inline typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Index out of array range");
  }

  return arr_[pos];
}

template <typename T, size_t N>
inline typename array<T, N>::const_reference array<T, N>::front() const {
  return *arr_;
}

template <typename T, size_t N>
inline typename array<T, N>::const_reference array<T, N>::back() const {
  return arr_[size_ - 1];
}

template <typename T, size_t N>
inline typename array<T, N>::iterator array<T, N>::data() {
  return N ? arr_ : nullptr;
}

template <typename T, size_t N>
inline typename array<T, N>::iterator array<T, N>::begin() {
  return arr_;
}

template <typename T, size_t N>
inline typename array<T, N>::iterator array<T, N>::end() {
  return arr_ + size_;
}

template <typename T, size_t N>
inline bool array<T, N>::empty() const {
  return N == 0;
}

template <typename T, size_t N>
inline typename array<T, N>::size_type array<T, N>::size() const {
  return size_;
}

template <typename T, size_t N>
inline typename array<T, N>::size_type array<T, N>::max_size() const {
  return size();
}

template <typename T, size_t N>
inline void array<T, N>::swap(array &other) {
  value_type tmp;
  for (size_type i = 0; i < size_; ++i) {
    tmp = other.arr_[i];
    other.arr_[i] = arr_[i];
    arr_[i] = tmp;
  }
}

template <typename T, size_t N>
inline void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < size_; ++i) {
    arr_[i] = value;
  }
}
}  // namespace s21

#endif