#ifndef S21_SRC_QUEUE_H
#define S21_SRC_QUEUE_H

#include <vector>

#include "s21_deque.h"

namespace s21 {

template <typename Type, typename Container = deque<Type>>
class queue {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  queue();
  queue(std::initializer_list<value_type> const& items);
  queue(const queue& q);
  queue(queue&& q);
  ~queue();
  queue& operator=(queue& q);
  queue& operator=(queue&& q);

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(queue& other);

  template <class... Args>
  void insert_many_back(Args&&... args);

 private:
  Container underlying_container;
};

template <typename Type, typename Container>
queue<Type, Container>::queue() : underlying_container() {}

template <typename Type, typename Container>
queue<Type, Container>::queue(std::initializer_list<value_type> const& items)
    : underlying_container(items) {}

template <typename Type, typename Container>
queue<Type, Container>::queue(const queue& q)
    : underlying_container(q.underlying_container) {}

template <typename Type, typename Container>
queue<Type, Container>::queue(queue&& q)
    : underlying_container(std::move(q.underlying_container)) {}

template <typename Type, typename Container>
queue<Type, Container>::~queue() {}

template <typename Type, typename Container>
queue<Type, Container>& queue<Type, Container>::operator=(queue& q) {
  underlying_container = q.underlying_container;
  return *this;
}

template <typename Type, typename Container>
queue<Type, Container>& queue<Type, Container>::operator=(queue&& q) {
  underlying_container = std::move(q.underlying_container);
  return *this;
}

template <typename Type, typename Container>
typename queue<Type, Container>::const_reference
queue<Type, Container>::front() {
  return underlying_container.front();
}

template <typename Type, typename Container>
typename queue<Type, Container>::const_reference
queue<Type, Container>::back() {
  return underlying_container.back();
}

template <typename Type, typename Container>
bool queue<Type, Container>::empty() {
  return underlying_container.empty();
}

template <typename Type, typename Container>
typename queue<Type, Container>::size_type queue<Type, Container>::size() {
  return underlying_container.size();
}

template <typename Type, typename Container>
void queue<Type, Container>::push(const_reference value) {
  underlying_container.push_back(value);
}

template <typename Type, typename Container>
void queue<Type, Container>::pop() {
  underlying_container.pop_front();
}

template <typename Type, typename Container>
void queue<Type, Container>::swap(queue& other) {
  underlying_container.swap(other.underlying_container);
}

template <typename Type, typename Container>
template <class... Args>
void queue<Type, Container>::insert_many_back(Args&&... args) {
  for (const auto& item : {args...}) {
    underlying_container.push_back(item);
  }
}

}  // namespace s21

#endif