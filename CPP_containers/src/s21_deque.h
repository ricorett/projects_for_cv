#ifndef S21_SRC_DEQUE_H
#define S21_SRC_DEQUE_H

#include <memory>
#include <stdexcept>

#define CHUNK_SIZE 32
#define INITIAL_MAP_SIZE 6

namespace s21 {

template <typename Type>
class deque {
 public:
  using value_type = Type;
  using map_pointer = Type**;
  using elt_pointer = Type*;
  using const_elt_pointer = const Type*;
  using const_map_pointer = const Type**;
  using reference = Type&;
  using const_reference = const Type&;
  using size_type = std::size_t;

  class iterator {
   public:
    iterator();
    iterator(const iterator& other);
    iterator(map_pointer line, elt_pointer begin, elt_pointer cur,
             elt_pointer end);

    elt_pointer cur();
    elt_pointer end();
    elt_pointer begin();
    map_pointer line();

    reference operator++();
    value_type operator++(int);
    reference operator--();
    value_type operator--(int);
    iterator& operator=(const iterator& other);

    reference operator*() const;
    elt_pointer operator->() const;
    bool operator<(const iterator& other);
    bool operator>(const iterator& other);
    bool operator==(const iterator& other);
    bool operator!=(const iterator& other);
    bool operator<=(const iterator& other);
    bool operator>=(const iterator& other);

    void setCur(elt_pointer cur);
    void setEnd(elt_pointer end);
    void setBegin(elt_pointer begin);
    void setLine(map_pointer line);

   private:
    map_pointer line_;
    elt_pointer begin_;
    elt_pointer cur_;
    elt_pointer end_;
  };

  class const_iterator : public iterator {
   public:
    const_iterator();
    const_iterator(const iterator& other);
    const_iterator(map_pointer line, elt_pointer begin, elt_pointer cur,
                   elt_pointer end);

    const_elt_pointer cur() const;
    const_elt_pointer end() const;
    const_elt_pointer begin() const;
    const_map_pointer line() const;

   private:
    const_map_pointer line_;
    const_elt_pointer begin_;
    const_elt_pointer cur_;
    const_elt_pointer end_;
  };

  deque();
  deque(std::initializer_list<value_type> const& items);
  deque(const deque& deq);
  deque(deque&& deq);
  ~deque();
  deque& operator=(const deque& deq);
  deque& operator=(deque&& deq);

  const_reference front() const;
  const_reference back() const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference at(size_type pos);

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  void swap(deque& other);
  void push_back(const_reference item);
  void push_front(const_reference item);
  void pop_back();
  void pop_front();

 private:
  map_pointer data;
  size_type size_;
  size_type maxMapSize;
  iterator start;
  iterator finish;
  std::allocator<value_type> dequeAllocator;
  void InitMap();
  void AllocBottomLine();
  void AllocTopLine();
  void ResizeMap();
};

template <typename Type>
deque<Type>::deque()
    : data(nullptr), size_(0), maxMapSize(0), start(), finish(start) {}

template <typename Type>
deque<Type>::~deque() {
  for (auto i = begin(); i < end(); ++i) {
    i->~Type();
  }

  while (start.line() <= finish.line()) {
    if (start.line() == nullptr) {
      break;
    }
    dequeAllocator.deallocate(*start.line(), CHUNK_SIZE);
    start.setLine(start.line() + 1);
  }
  if (data != nullptr) {
    delete[] data;
  }
}

template <typename Type>
deque<Type>::deque(std::initializer_list<value_type> const& items) : deque() {
  for (auto item : items) {
    push_back(item);
  }
}

template <typename Type>
deque<Type>::deque(const deque& deq) : deque() {
  for (const_iterator i = deq.begin(); i < deq.end(); i++) {
    push_back(*i);
  }
}

template <typename Type>
deque<Type>::deque(deque&& deq) : deque() {
  this->operator=(std::move(deq));
}

template <typename Type>
deque<Type>& deque<Type>::operator=(const deque& deq) {
  while (!empty()) {
    pop_back();
  }
  for (auto i = deq.begin(); i < deq.end(); ++i) {
    push_back(*i);
  }
  return *this;
}

template <typename Type>
deque<Type>& deque<Type>::operator=(deque&& deq) {
  while (!empty()) {
    pop_back();
  }
  if (data) {
    if (start.line()) {
      dequeAllocator.deallocate(*start.line(), CHUNK_SIZE);
    }
    delete[] data;
  }
  data = deq.data;
  size_ = deq.size_;
  maxMapSize = deq.maxMapSize;
  start = deq.start;
  finish = deq.finish;

  deq.data = nullptr;
  deq.size_ = 0;
  deq.maxMapSize = 0;

  deq.start.setLine(nullptr);
  deq.start.setBegin(nullptr);
  deq.start.setEnd(nullptr);
  deq.start.setCur(nullptr);

  deq.finish.setLine(nullptr);
  deq.finish.setBegin(nullptr);
  deq.finish.setEnd(nullptr);
  deq.finish.setCur(nullptr);

  return *this;
}

template <typename Type>
void deque<Type>::push_back(const_reference item) {
  if (data == nullptr) {
    InitMap();
    new (finish.cur()) value_type(item);
  } else {
    new (finish.cur()) value_type(item);
    if (finish.cur() == finish.end()) {
      AllocBottomLine();
    }
  }
  ++finish;
  ++size_;
}

template <typename Type>
void deque<Type>::push_front(const_reference item) {
  if (data == nullptr) {
    InitMap();
  }
  if (start.cur() == start.begin()) {
    AllocTopLine();
  }
  --start;
  new (start.cur()) value_type(item);
  ++size_;
}

template <typename Type>
void deque<Type>::InitMap() {
  data = new elt_pointer[INITIAL_MAP_SIZE];
  size_type midOfMap = INITIAL_MAP_SIZE / 2;

  data[midOfMap] = dequeAllocator.allocate(CHUNK_SIZE);

  maxMapSize = INITIAL_MAP_SIZE;

  start.setLine(data + midOfMap);
  start.setBegin(data[midOfMap]);
  start.setCur(data[midOfMap]);
  start.setEnd(data[midOfMap] + CHUNK_SIZE - 1);

  finish = start;
}

template <typename Type>
void deque<Type>::AllocBottomLine() {
  if (finish.line() + 1 == data + maxMapSize) {
    ResizeMap();
  }
  *(finish.line() + 1) = dequeAllocator.allocate(CHUNK_SIZE);
}

template <typename Type>
void deque<Type>::AllocTopLine() {
  if (start.line() - 1 == data) {
    ResizeMap();
  }
  *(start.line() - 1) = dequeAllocator.allocate(CHUNK_SIZE);
}

template <typename Type>
void deque<Type>::ResizeMap() {
  size_type realMapSize = std::distance(start.line(), finish.line());

  map_pointer newData = new elt_pointer[realMapSize * 3];

  std::copy(start.line(), finish.line() + 1, newData + realMapSize);

  start.setLine(newData + realMapSize);
  finish.setLine(newData + (realMapSize * 2));

  delete[] data;
  data = newData;
  maxMapSize = realMapSize * 3;
}

template <typename Type>
typename deque<Type>::reference deque<Type>::operator[](size_type pos) {
  size_type distance = std::distance(start.begin(), start.cur());
  return *(*(start.line() + (pos + distance) / CHUNK_SIZE) +
           (pos + distance) % CHUNK_SIZE);
}

template <typename Type>
typename deque<Type>::const_reference deque<Type>::operator[](
    size_type pos) const {
  size_type distance = std::distance(start.begin(), start.cur());
  return *(*(start.line() + (pos + distance) / CHUNK_SIZE) +
           (pos + distance) % CHUNK_SIZE);
}

template <typename Type>
typename deque<Type>::reference deque<Type>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return operator[](pos);
}

template <typename Type>
inline bool deque<Type>::empty() const {
  return size_ == 0;
}

template <typename Type>
void deque<Type>::pop_back() {
  auto tmp = finish.line();
  --finish;
  (finish.cur())->~Type();
  --size_;
  if (tmp != finish.line()) {
    dequeAllocator.deallocate(*tmp, CHUNK_SIZE);
  }
}

template <typename Type>
void deque<Type>::pop_front() {
  auto tmp = start.line();
  (start.cur())->~Type();
  ++start;
  --size_;
  if (tmp != start.line()) {
    dequeAllocator.deallocate(*tmp, CHUNK_SIZE);
  }
}

template <typename Type>
typename deque<Type>::const_reference deque<Type>::front() const {
  return *begin();
}

template <typename Type>
typename deque<Type>::const_reference deque<Type>::back() const {
  const_iterator tmp(finish);
  --tmp;
  return *tmp;
}

template <typename Type>
inline typename deque<Type>::size_type deque<Type>::size() const {
  return size_;
}

template <typename Type>
void deque<Type>::swap(deque& other) {
  std::swap(data, other.data);
  std::swap(size_, other.size_);
  std::swap(maxMapSize, other.maxMapSize);
  std::swap(start, other.start);
  std::swap(finish, other.finish);
}

//-------deque-iterator-methods---------//

template <typename Type>
typename deque<Type>::iterator deque<Type>::begin() {
  return iterator{start.line(), start.begin(), start.cur(), start.end()};
}

template <typename Type>
typename deque<Type>::iterator deque<Type>::end() {
  return iterator{finish.line(), finish.begin(), finish.cur(), finish.end()};
}

template <typename Type>
typename deque<Type>::const_iterator deque<Type>::begin() const {
  return const_iterator(start);
}

template <typename Type>
typename deque<Type>::const_iterator deque<Type>::end() const {
  return const_iterator(finish);
}

//--------------iterator---------------//

template <typename Type>
deque<Type>::iterator::iterator()
    : line_(nullptr),
      begin_(nullptr),
      cur_(reinterpret_cast<elt_pointer>(this)),
      end_(nullptr) {}

template <typename Type>
deque<Type>::iterator::iterator(const iterator& other)
    : line_(other.line_),
      begin_(other.begin_),
      cur_(other.cur_),
      end_(other.end_) {}

template <typename Type>
deque<Type>::iterator::iterator(map_pointer line, elt_pointer begin,
                                elt_pointer cur, elt_pointer end)
    : line_(line), begin_(begin), cur_(cur), end_(end) {}

template <typename Type>
inline deque<Type>::const_iterator::const_iterator(const iterator& other)
    : deque<Type>::iterator::iterator(other) {}

template <typename Type>
deque<Type>::const_iterator::const_iterator(map_pointer line, elt_pointer begin,
                                            elt_pointer cur, elt_pointer end)
    : line_(line), begin_(begin), cur_(cur), end_(end) {}

template <typename Type>
inline typename deque<Type>::elt_pointer deque<Type>::iterator::cur() {
  return cur_;
}

template <typename Type>
inline typename deque<Type>::elt_pointer deque<Type>::iterator::begin() {
  return begin_;
}

template <typename Type>
inline typename deque<Type>::elt_pointer deque<Type>::iterator::end() {
  return end_;
}

template <typename Type>
inline typename deque<Type>::map_pointer deque<Type>::iterator::line() {
  return line_;
}

template <typename Type>
inline typename deque<Type>::const_elt_pointer
deque<Type>::const_iterator::cur() const {
  return cur_;
}

template <typename Type>
inline typename deque<Type>::const_elt_pointer
deque<Type>::const_iterator::begin() const {
  return begin_;
}

template <typename Type>
inline typename deque<Type>::const_elt_pointer
deque<Type>::const_iterator::end() const {
  return end_;
}

template <typename Type>
inline typename deque<Type>::const_map_pointer
deque<Type>::const_iterator::line() const {
  return line_;
}

template <typename Type>
inline void deque<Type>::iterator::setCur(elt_pointer cur) {
  cur_ = cur;
}

template <typename Type>
inline void deque<Type>::iterator::setEnd(elt_pointer end) {
  end_ = end;
}

template <typename Type>
inline void deque<Type>::iterator::setBegin(elt_pointer begin) {
  begin_ = begin;
}

template <typename Type>
inline void deque<Type>::iterator::setLine(map_pointer line) {
  line_ = line;
}

template <typename Type>
typename deque<Type>::reference deque<Type>::iterator::operator++() {
  if (cur_ == end_) {
    ++line_;
    begin_ = *line_;
    end_ = *line_ + CHUNK_SIZE - 1;
    cur_ = begin_;
  } else {
    ++cur_;
  }
  return *cur_;
}

template <typename Type>
typename deque<Type>::value_type deque<Type>::iterator::operator++(int) {
  iterator copy = *this;
  this->operator++();
  return *(copy.cur_);
}

template <typename Type>
typename deque<Type>::reference deque<Type>::iterator::operator--() {
  if (cur_ == begin_) {
    --line_;
    begin_ = *line_;
    end_ = *line_ + CHUNK_SIZE - 1;
    cur_ = end_;
  } else {
    --cur_;
  }
  return *cur_;
}

template <typename Type>
typename deque<Type>::value_type deque<Type>::iterator::operator--(int) {
  iterator copy = *this;
  this->operator--;
  return *(copy.cur_);
}

template <typename Type>
typename deque<Type>::iterator& deque<Type>::iterator::operator=(
    const iterator& other) {
  begin_ = other.begin_;
  line_ = other.line_;
  cur_ = other.cur_;
  end_ = other.end_;
  return *this;
}

template <typename Type>
inline typename deque<Type>::reference deque<Type>::iterator::operator*()
    const {
  return *cur_;
}

template <typename Type>
inline typename deque<Type>::elt_pointer deque<Type>::iterator::operator->()
    const {
  return cur_;
}

template <typename Type>
inline bool deque<Type>::iterator::operator<(const iterator& other) {
  bool result = false;
  if (line_ < other.line_) result = true;
  if (line_ == other.line_ && cur_ < other.cur_) result = true;
  return result;
}

template <typename Type>
inline bool deque<Type>::iterator::operator>(const iterator& other) {
  return other < *this;
}

template <typename Type>
inline bool deque<Type>::iterator::operator==(const iterator& other) {
  return cur_ == other.cur_;
}

template <typename Type>
inline bool deque<Type>::iterator::operator!=(const iterator& other) {
  return cur_ != other.cur_;
}

template <typename Type>
inline bool deque<Type>::iterator::operator<=(const iterator& other) {
  return *this == other || *this < other;
}

template <typename Type>
inline bool deque<Type>::iterator::operator>=(const iterator& other) {
  return *this > other || *this == other;
}

}  // namespace s21

#endif
