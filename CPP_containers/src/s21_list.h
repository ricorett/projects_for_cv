#pragma once
#include <cstddef>
#include <limits>
#include <utility>

namespace s21 {

template <typename T>
class list {
 public:
  class Node;
  class ListIterator;
  class ConstListIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ConstListIterator;
  using size_type = size_t;

  class Node {
   public:
    Node(value_type data) : data(data), prev_(nullptr), next_(nullptr) {}

    value_type data;
    Node *prev_;
    Node *next_;
  };

  class ListIterator {
   private:
    Node *current;
    friend list;

   public:
    ListIterator(Node *node) : current(node) {}
    ListIterator(ConstListIterator const_iter);
    const_reference operator*() { return current->data; }
    value_type *operator->() { return &current->data; }

    ListIterator &operator++() {
      if (current) current = current->next_;
      return *this;
    }
    ListIterator operator++(int) {
      ListIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    ListIterator &operator--() {
      if (current) current = current->prev_;
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const ListIterator &other) const {
      return current == other.current;
    }
    bool operator!=(const ListIterator &other) const {
      return current != other.current;
    }
  };

  class ConstListIterator {
   private:
    const Node *current;
    friend list;

   public:
    ConstListIterator(const Node *node) : current(node) {}

    const_reference operator*() const { return current->data; }

    const value_type *operator->() const { return &current->data; }

    ConstListIterator &operator++() {
      if (current) current = current->next_;
      return *this;
    }

    ConstListIterator operator++(int) {
      ConstListIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    ConstListIterator &operator--() {
      if (current) current = current->prev_;
      return *this;
    }

    ConstListIterator operator--(int) {
      ConstListIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const ConstListIterator &other) const {
      return current == other.current;
    }

    bool operator!=(const ConstListIterator &other) const {
      return current != other.current;
    }
  };

  list() : head_(nullptr), tail_(nullptr), size_(0) {}
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &other);
  list(list &&other);

  ~list() { clear(); }
  list &operator=(list &&other);
  list &operator=(const list &other);

  const_reference front() const { return head_->data; }
  const_reference back() const { return tail_->data; }

  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(nullptr); }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  const_iterator cbegin() const { return const_iterator(head_); };
  const_iterator cend() const { return const_iterator(nullptr); };
  void remove(const_reference value);
  list<value_type> copy();

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <class... Args>
  void insert_many_back(Args &&...args);

  template <class... Args>
  void insert_many_front(Args &&...args);

 private:
  Node *head_;
  Node *tail_;
  size_type size_;
};

template <typename value_type>
list<value_type>::list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  for (size_type i = 0; i < n; ++i) {
    push_back(value_type{});
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (auto item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list &other) : list() {
  const_iterator data = other.cbegin();
  for (size_type i = 0; i < other.size(); ++i, ++data) {
    push_back(*data);
  }
}

template <typename T>
list<T>::list(list &&other) {
  head_ = std::exchange(other.head_, nullptr);
  tail_ = std::exchange(other.tail_, nullptr);
  size_ = std::exchange(other.size_, 0);
}

template <typename value_type>
list<value_type> &list<value_type>::operator=(const list &other) {
  if (this != &other) {
    clear();
    Node *current = other.head_;
    while (current) {
      push_back(current->data);
      current = current->next_;
    }
  }
  return *this;
};

template <typename value_type>
list<value_type> &list<value_type>::operator=(list &&other) {
  if (this != &other) {
    clear();
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename value_type>
size_t list<value_type>::max_size() const {
  return (std::numeric_limits<std::size_t>::max() / sizeof(value_type)) / 2;
}

template <typename value_type>
void list<value_type>::clear() {
  Node *current = head_;
  while (current) {
    Node *nextNode = current->next_;
    current->next_ = nullptr;
    delete current;
    current = nextNode;
  }
  head_ = tail_ = nullptr;
  size_ = 0;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  Node *newNode = new Node(value);
  Node *current = pos.current;
  if (current) {
    newNode->next_ = current;
    newNode->prev_ = current->prev_;
    if (current->prev_) {
      current->prev_->next_ = newNode;
    } else {
      head_ = newNode;
    }
    current->prev_ = newNode;
  } else {
    if (!head_) {
      head_ = tail_ = newNode;
    } else {
      tail_->next_ = newNode;
      newNode->prev_ = tail_;
      tail_ = newNode;
    }
  }
  ++size_;
  return iterator(newNode);
}

template <typename value_type>
void list<value_type>::push_back(const_reference value) {
  if (head_ == nullptr) {
    head_ = new Node(value);
    tail_ = head_;
    size_++;
  } else {
    Node *current = tail_;
    tail_->next_ = new Node(value);
    tail_ = tail_->next_;
    tail_->prev_ = current;
    size_++;
  }
};

template <typename value_type>
void list<value_type>::pop_back() {
  if (size_ != 0) {
    Node *current = tail_;
    tail_ = tail_->prev_;
    delete current;
    tail_->next_ = nullptr;
    if (current == head_) {
      head_ = nullptr;
    }
    current = nullptr;
    size_--;
  }
};

template <typename value_type>
void list<value_type>::push_front(const_reference value) {
  if (head_ == nullptr) {
    head_ = new Node(value);
    tail_ = head_;
    size_++;
  } else {
    Node *new_node = new Node(value);
    Node *current = head_;
    head_ = new_node;
    head_->next_ = current;
    size_++;
  }
};

template <typename value_type>
void list<value_type>::pop_front() {
  if (head_) {
    Node *tmp = head_;
    head_ = head_->next_;
    if (head_) {
      head_->prev_ = nullptr;
    } else {
      tail_ = nullptr;
    }
    delete tmp;
    --size_;
  }
};

template <typename value_type>
void list<value_type>::swap(list &other) {
  Node *tmp_head = this->head_;
  this->head_ = other.head_;
  other.head_ = tmp_head;

  Node *tmp_tail = this->tail_;
  this->tail_ = other.tail_;
  other.tail_ = tmp_tail;

  int tmp_size = this->size_;
  this->size_ = other.size_;
  other.size_ = tmp_size;
}

template <typename value_type>
void list<value_type>::merge(list &other) {
  if (other.empty()) {
    return;
  }

  if (this->empty()) {
    this->head_ = other.head_;
    this->tail_ = other.tail_;
    this->size_ = other.size_;

    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
    return;
  }

  Node *current = this->head_;
  Node *other_current = other.head_;

  Node *new_head = nullptr;
  Node *new_tail = nullptr;

  if (current->data <= other_current->data) {
    new_head = current;
    current = current->next_;
  } else {
    new_head = other_current;
    other_current = other_current->next_;
  }
  new_tail = new_head;

  while (current != nullptr && other_current != nullptr) {
    if (current->data <= other_current->data) {
      new_tail->next_ = current;
      current->prev_ = new_tail;
      current = current->next_;
    } else {
      new_tail->next_ = other_current;
      other_current->prev_ = new_tail;
      other_current = other_current->next_;
    }
    new_tail = new_tail->next_;
  }

  if (current != nullptr) {
    new_tail->next_ = current;
    current->prev_ = new_tail;
    this->tail_ = this->tail_;
  } else if (other_current != nullptr) {
    new_tail->next_ = other_current;
    other_current->prev_ = new_tail;
    this->tail_ = other.tail_;
  }

  this->head_ = new_head;
  this->tail_ = (current == nullptr) ? other.tail_ : this->tail_;
  this->size_ += other.size_;

  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  if (other.empty()) {
    return;
  }
  Node *pos_node = const_cast<Node *>(pos.current);
  Node *other_head = other.head_;
  Node *other_tail = other.tail_;

  if (pos_node == this->head_) {
    other_tail->next_ = this->head_;
    this->head_->prev_ = other_tail;
    this->head_ = other_head;
  }

  else if (pos_node == nullptr) {
    this->tail_->next_ = other_head;
    other_head->prev_ = this->tail_;
    this->tail_ = other_tail;
  }

  else {
    other_tail->next_ = pos_node;
    pos_node->prev_->next_ = other_head;
    other_head->prev_ = pos_node->prev_;
    pos_node->prev_ = other_tail;
  }

  this->size_ += other.size_;

  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename value_type>
void list<value_type>::reverse() {
  if (!head_ || !head_->next_) {
    return;
  }

  Node *current = head_;
  Node *tmp = nullptr;
  Node *tmp_head = head_;

  while (current != nullptr) {
    tmp = current->prev_;
    current->prev_ = current->next_;
    current->next_ = tmp;

    current = current->prev_;
  }

  if (tmp != nullptr) {
    head_ = tmp->prev_;
  }

  head_ = tail_;
  tail_ = tmp_head;
}

template <typename value_type>
void list<value_type>::unique() {
  if (!head_) return;

  Node *current = head_;

  while (current->next_) {
    if (current->data == current->next_->data) {
      Node *duplicate = current->next_;
      current->next_ = duplicate->next_;

      if (duplicate->next_) {
        duplicate->next_->prev_ = current;
      } else {
        tail_ = current;
      }

      delete duplicate;
      --size_;

    } else {
      current = current->next_;
    }
  }
}

template <typename value_type>
void list<value_type>::sort() {
  if (!head_ || !head_->next_) return;

  bool swapped;
  do {
    swapped = false;
    Node *current = head_;
    while (current->next_) {
      if (current->data > current->next_->data) {
        std::swap(current->data, current->next_->data);
        swapped = true;
      }
      current = current->next_;
    }
  } while (swapped);
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  Node *current = pos.current;

  if (!current) return;

  if (current->prev_) {
    current->prev_->next_ = current->next_;
  } else {
    head_ = current->next_;
  }

  if (current->next_) {
    current->next_->prev_ = current->prev_;
  } else {
    tail_ = current->prev_;
  }

  delete current;
  --size_;
}

template <typename value_type>
list<value_type> list<value_type>::copy() {
  list<value_type> new_list;

  Node *current = head_;
  while (current != nullptr) {
    new_list.push_back(current->data);
    current = current->next_;
  }

  return new_list;
}

template <typename value_type>
void list<value_type>::remove(const_reference value) {
  Node *current = head_;
  while (current) {
    if (current->data == value) {
      Node *toRemove = current;

      if (current->prev_) {
        current->prev_->next_ = current->next_;
      } else {
        head_ = current->next_;
      }

      if (current->next_) {
        current->next_->prev_ = current->prev_;
      } else {
        tail_ = current->prev_;
      }

      current = current->next_;
      delete toRemove;
      --size_;

    } else {
      current = current->next_;
    }
  }
};

template <typename T>
template <class... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  iterator insert_pos(nullptr);
  iterator iter(pos);
  bool flag = true;
  for (const auto &item : {args...}) {
    if (flag) {
      insert_pos = insert(iter, item);
      flag = false;
    } else {
      insert(iter, item);
    }
  }
  return insert_pos;
}

template <typename T>
template <class... Args>
void list<T>::insert_many_back(Args &&...args) {
  insert_many(const_iterator(tail_->next_), args...);
}

template <typename T>
template <class... Args>
void list<T>::insert_many_front(Args &&...args) {
  insert_many(const_iterator(head_), args...);
}

template <typename T>
list<T>::ListIterator::ListIterator(ConstListIterator const_iter)
    : current(const_cast<Node *>(const_iter.current)) {}

};  // namespace s21
