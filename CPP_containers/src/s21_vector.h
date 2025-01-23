#pragma once
#include <initializer_list>
#include <limits>
#include <memory>
#include <stdexcept>

namespace s21 {

template <typename T>
class vector {
 public:
  class VectorIterator;
  class ConstVectorIterator;

  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  using iterator = VectorIterator;
  using const_iterator = ConstVectorIterator;
  using size_type = size_t;

  class VectorIterator {
   public:
    VectorIterator() : current(nullptr) {}
    VectorIterator(pointer ptr) : current(ptr) {}

    reference operator*();
    VectorIterator operator++(int);
    VectorIterator operator--(int);
    VectorIterator& operator++();
    VectorIterator& operator--();
    VectorIterator operator+(int offset);
    VectorIterator operator-(int offset);
    VectorIterator& operator+=(int offset);
    VectorIterator& operator-=(int offset);

    int operator-(const VectorIterator& other) const;

    bool operator==(const VectorIterator& other) const;
    bool operator!=(const VectorIterator& other) const;
    bool operator<(const VectorIterator& other) const;
    bool operator<=(const VectorIterator& other) const;
    bool operator>(const VectorIterator& other) const;
    bool operator>=(const VectorIterator& other) const;

   private:
    pointer current;
  };

  class ConstVectorIterator : public VectorIterator {
   public:
    ConstVectorIterator() : current(nullptr) {}
    ConstVectorIterator(const_pointer ptr) : current(ptr) {}

    const_reference operator*() const;
    ConstVectorIterator operator++(int);
    ConstVectorIterator operator--(int);
    ConstVectorIterator& operator++();
    ConstVectorIterator& operator--();
    ConstVectorIterator operator+(int offset);
    ConstVectorIterator operator-(int offset);
    ConstVectorIterator& operator+=(int offset);
    ConstVectorIterator& operator-=(int offset);

    int operator-(const ConstVectorIterator& other) const;

    bool operator==(const ConstVectorIterator& other) const;
    bool operator!=(const ConstVectorIterator& other) const;
    bool operator<(const ConstVectorIterator& other) const;
    bool operator<=(const ConstVectorIterator& other) const;
    bool operator>(const ConstVectorIterator& other) const;
    bool operator>=(const ConstVectorIterator& other) const;

   private:
    const_pointer current;
  };

  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& other);
  vector(vector&& other);
  ~vector();
  vector& operator=(vector&& other);

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  pointer data();
  const_pointer data() const;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type n);
  size_type capacity() const;
  void shrink_to_fit();
  void clear();

  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <class... Args>
  void insert_many_back(Args&&... args);

 private:
  pointer data_;
  size_type size_;
  size_type capacity_;
  std::allocator<value_type> vector_allocator_;
};

template <typename value_type>
vector<value_type>::vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename value_type>
vector<value_type>::vector(size_type n) : vector() {
  data_ = vector_allocator_.allocate(n);
  capacity_ = n;
}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const& items)
    : vector(items.size() * 2) {
  for (auto item : items) {
    push_back(item);
  }
  size_ = items.size();
}

template <typename value_type>
vector<value_type>::vector(const vector& other) : vector(other.capacity_) {
  for (size_type i = 0; i < other.size(); ++i) {
    new (data_ + i) value_type(*(other.data() + i));
  }
  size_ = other.size_;
  capacity_ = other.capacity_;
}

template <typename value_type>
vector<value_type>::vector(vector&& other) {
  data_ = std::move(other.data_);
  other.data_ = nullptr;
  size_ = std::move(other.size_);
  other.size_ = 0;
  capacity_ = std::move(other.capacity_);
  other.capacity_ = 0;
}

template <typename value_type>
vector<value_type>::~vector() {
  for (size_type i = 0; i < size_; ++i) {
    data_[i].~value_type();
  }
  vector_allocator_.deallocate(data_, capacity_);
}

template <typename value_type>
vector<value_type>& vector<value_type>::operator=(vector&& other) {
  clear();
  vector_allocator_.deallocate(data_, capacity_);
  data_ = std::move(other.data_);
  other.data_ = nullptr;
  size_ = std::move(other.size_);
  other.size_ = 0;
  capacity_ = std::move(other.capacity_);
  other.capacity_ = 0;
  return *this;
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::at(
    size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type pos) {
  return data_[pos];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::operator[](
    size_type pos) const {
  return data_[pos];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::front() {
  return *data_;
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() const {
  return *data_;
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::back() {
  return *(data_ + size_ - 1);
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back() const {
  return *(data_ + size_ - 1);
}

template <typename value_type>
typename vector<value_type>::pointer vector<value_type>::data() {
  return data_;
}

template <typename value_type>
typename vector<value_type>::const_pointer vector<value_type>::data() const {
  return data_;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  return VectorIterator(data_);
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  return VectorIterator(data_ + size_);
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::begin() const {
  return ConstVectorIterator(data_);
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::end() const {
  return ConstVectorIterator(data_ + size_);
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::cbegin() const {
  return ConstVectorIterator(data_);
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::cend() const {
  return ConstVectorIterator(data_ + size_);
}

template <typename value_type>
bool vector<value_type>::empty() const {
  return size_ == 0;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() const {
  return size_;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() const {
  return (std::numeric_limits<std::size_t>::max() / sizeof(value_type)) / 2;
}

template <typename value_type>
void vector<value_type>::reserve(size_type n) {
  if (n > capacity_) {
    pointer temp_buffer = vector_allocator_.allocate(n);
    for (size_type i = 0; i < size_; ++i) {
      new (temp_buffer + i) value_type(data_[i]);
      data_[i].~value_type();
    }
    vector_allocator_.deallocate(data_, capacity_);
    data_ = temp_buffer;
    capacity_ = n;
  }
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() const {
  return capacity_;
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  pointer temp_buffer = vector_allocator_.allocate(size_);
  for (size_type i = 0; i < size_; ++i) {
    new (temp_buffer + i) value_type(data_[i]);
    data_[i].~value_type();
  }
  vector_allocator_.deallocate(data_, capacity_);
  data_ = temp_buffer;
  capacity_ = size_;
}

template <typename value_type>
void vector<value_type>::clear() {
  for (size_type i = 0; i < size_; ++i) {
    data_[i].~value_type();
  }
  size_ = 0;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  if (size_ == capacity_) {
    int index = pos - begin();
    reserve(capacity_ ? capacity_ * 2 : 1);
    pos = begin() + index;
  }
  for (auto i = end(); i > pos; --i) {
    new (data_ + (i - begin())) value_type(data_[i - begin() - 1]);
    data_[i - begin() - 1].~value_type();
  }
  new (data_ + (pos - begin())) value_type(value);
  ++size_;
  return pos;
}

template <typename value_type>
void vector<value_type>::erase(iterator pos) {
  if (size_ > 0) {
    data_[pos - begin()].~value_type();
    for (iterator i = pos; i != end() - 1; ++i) {
      *i = std::move(*(i + 1));
    }
    --size_;
  }
}

template <typename value_type>
void vector<value_type>::push_back(const_reference value) {
  if (size_ == capacity_) {
    reserve(capacity_ ? capacity_ * 2 : 1);
  }
  new (data_ + size_) value_type(value);
  ++size_;
}

template <typename value_type>
void vector<value_type>::pop_back() {
  if (size_ > 0) {
    data_[size_ - 1].~value_type();
    --size_;
  }
}

template <typename value_type>
void vector<value_type>::swap(vector& other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename value_type>
template <class... Args>
typename vector<value_type>::iterator vector<value_type>::insert_many(
    const_iterator pos, Args&&... args) {
  iterator insert_pos;
  int insert_index = pos - cbegin();
  bool flag = true;
  for (const auto& item : {args...}) {
    if (flag) {
      insert_pos = insert(begin() + insert_index, item);
      flag = false;
    } else {
      insert(begin() + insert_index, item);
    }
    ++insert_index;
  }
  return insert_pos;
}

template <typename value_type>
template <class... Args>
void vector<value_type>::insert_many_back(Args&&... args) {
  insert_many(cend(), args...);
}

//------iterators-logic------//

template <typename value_type>
typename vector<value_type>::reference
vector<value_type>::iterator::operator*() {
  return *current;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::iterator::operator++(
    int) {
  iterator tmp(*this);
  ++current;
  return tmp;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::iterator::operator--(
    int) {
  iterator tmp(*this);
  --current;
  return tmp;
}

template <typename value_type>
typename vector<value_type>::iterator&
vector<value_type>::iterator::operator++() {
  ++current;
  return *this;
}

template <typename value_type>
typename vector<value_type>::iterator&
vector<value_type>::iterator::operator--() {
  --current;
  return *this;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::iterator::operator+(
    int offset) {
  return iterator(current + offset);
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::iterator::operator-(
    int offset) {
  return iterator(current - offset);
}

template <typename value_type>
typename vector<value_type>::iterator& vector<value_type>::iterator::operator+=(
    int offset) {
  current += offset;
  return *this;
}

template <typename value_type>
typename vector<value_type>::iterator& vector<value_type>::iterator::operator-=(
    int offset) {
  current -= offset;
  return *this;
}

template <typename value_type>
int vector<value_type>::iterator::operator-(const iterator& other) const {
  return current - other.current;
}

template <typename value_type>
bool vector<value_type>::iterator::operator==(const iterator& other) const {
  return current == other.current;
}

template <typename value_type>
bool vector<value_type>::iterator::operator!=(const iterator& other) const {
  return current != other.current;
}

template <typename value_type>
bool vector<value_type>::iterator::operator<(const iterator& other) const {
  return current < other.current;
}

template <typename value_type>
bool vector<value_type>::iterator::operator<=(const iterator& other) const {
  return current < other.current || current == other.current;
}

template <typename value_type>
bool vector<value_type>::iterator::operator>(const iterator& other) const {
  return current > other.current;
}

template <typename value_type>
bool vector<value_type>::iterator::operator>=(const iterator& other) const {
  return current > other.current || current == other.current;
}

//----const-iter----//

template <typename value_type>
typename vector<value_type>::const_reference
vector<value_type>::const_iterator::operator*() const {
  return *current;
}

template <typename value_type>
typename vector<value_type>::const_iterator
vector<value_type>::const_iterator::operator++(int) {
  const_iterator tmp(*this);
  ++current;
  return tmp;
}

template <typename value_type>
typename vector<value_type>::const_iterator
vector<value_type>::const_iterator::operator--(int) {
  const_iterator tmp(*this);
  --current;
  return tmp;
}

template <typename value_type>
typename vector<value_type>::const_iterator&
vector<value_type>::const_iterator::operator++() {
  ++current;
  return *this;
}

template <typename value_type>
typename vector<value_type>::const_iterator&
vector<value_type>::const_iterator::operator--() {
  --current;
  return *this;
}

template <typename value_type>
typename vector<value_type>::const_iterator
vector<value_type>::const_iterator::operator+(int offset) {
  return const_iterator(current + offset);
}

template <typename value_type>
typename vector<value_type>::const_iterator
vector<value_type>::const_iterator::operator-(int offset) {
  return const_iterator(current - offset);
}

template <typename value_type>
typename vector<value_type>::const_iterator&
vector<value_type>::const_iterator::operator+=(int offset) {
  current += offset;
  return *this;
}

template <typename value_type>
typename vector<value_type>::const_iterator&
vector<value_type>::const_iterator::operator-=(int offset) {
  current -= offset;
  return *this;
}

template <typename value_type>
int vector<value_type>::const_iterator::operator-(
    const const_iterator& other) const {
  return current - other.current;
}

template <typename value_type>
bool vector<value_type>::const_iterator::operator==(
    const const_iterator& other) const {
  return current == other.current;
}

template <typename value_type>
bool vector<value_type>::const_iterator::operator!=(
    const const_iterator& other) const {
  return current != other.current;
}

template <typename value_type>
bool vector<value_type>::const_iterator::operator<(
    const const_iterator& other) const {
  return current < other.current;
}

template <typename value_type>
bool vector<value_type>::const_iterator::operator<=(
    const const_iterator& other) const {
  return current < other.current || current == other.current;
}

template <typename value_type>
bool vector<value_type>::const_iterator::operator>(
    const const_iterator& other) const {
  return current > other.current;
}

template <typename value_type>
bool vector<value_type>::const_iterator::operator>=(
    const const_iterator& other) const {
  return current > other.current || current == other.current;
}

}  // namespace s21