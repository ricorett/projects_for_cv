#ifndef S21_SRC_STACK_H
#define S21_SRC_STACK_H

#include <vector>

#include "s21_deque.h"

namespace s21 {

template <typename Type, typename Container = deque<Type>>
class stack {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  stack();
  stack(std::initializer_list<value_type> const& items);
  stack(const stack& s);
  stack(stack&& s);
  ~stack();
  stack& operator=(stack& s);
  stack& operator=(stack&& s);

  const_reference top();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(stack& other);

  template <class... Args>
  void insert_many_front(Args&&... args);

 private:
  Container underlying_container;
};

template <typename Type, typename Container>
stack<Type, Container>::stack() : underlying_container() {}

template <typename Type, typename Container>
stack<Type, Container>::stack(std::initializer_list<value_type> const& items)
    : stack() {
  for (auto item : items) {
    underlying_container.push_front(item);
  }
}

template <typename Type, typename Container>
stack<Type, Container>::stack(const stack& s)
    : underlying_container(s.underlying_container) {}

template <typename Type, typename Container>
stack<Type, Container>::stack(stack&& s)
    : underlying_container(std::move(s.underlying_container)) {}

template <typename Type, typename Container>
stack<Type, Container>::~stack() {}

template <typename Type, typename Container>
stack<Type, Container>& stack<Type, Container>::operator=(stack& s) {
  underlying_container = s.underlying_container;
  return *this;
}

template <typename Type, typename Container>
stack<Type, Container>& stack<Type, Container>::operator=(stack&& s) {
  underlying_container = std::move(s.underlying_container);
  return *this;
}

template <typename Type, typename Container>
typename stack<Type, Container>::const_reference stack<Type, Container>::top() {
  return underlying_container.front();
}

template <typename Type, typename Container>
bool stack<Type, Container>::empty() {
  return underlying_container.empty();
}

template <typename Type, typename Container>
typename stack<Type, Container>::size_type stack<Type, Container>::size() {
  return underlying_container.size();
}

template <typename Type, typename Container>
void stack<Type, Container>::push(const_reference value) {
  underlying_container.push_front(value);
}

template <typename Type, typename Container>
void stack<Type, Container>::pop() {
  underlying_container.pop_front();
}

template <typename Type, typename Container>
void stack<Type, Container>::swap(stack& other) {
  underlying_container.swap(other.underlying_container);
}

template <typename Type, typename Container>
template <class... Args>
void stack<Type, Container>::insert_many_front(Args&&... args) {
  for (const auto& item : {args...}) {
    underlying_container.push_front(item);
  }
}

}  // namespace s21

#endif