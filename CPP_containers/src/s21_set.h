#ifndef S21_SRC_SET_H
#define S21_SRC_SET_H

#include <vector>

#include "AVLtree.h"

namespace s21 {

template <typename Key, typename Comparator = std::less<Key>>
class set : private AVLtree<Key, Key, Comparator> {
 public:
  class set_iterator;
  class const_set_iterator;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using pointer = value_type*;
  using const_reference = const value_type&;
  using const_pointer = const value_type*;
  using iterator = set_iterator;
  using const_iterator = const_set_iterator;
  using size_type = size_t;

  class set_iterator : public AVLtree<Key, Key, Comparator>::iterator {
   public:
    set_iterator() = default;
    set_iterator(const typename AVLtree<Key, Key, Comparator>::iterator& other);
    set_iterator(typename AVLtree<Key, Key, Comparator>::node* node);
    reference operator*();
  };

  class const_set_iterator
      : public AVLtree<Key, Key, Comparator>::const_iterator {
   public:
    const_set_iterator() = default;
    const_set_iterator(
        const typename AVLtree<Key, Key, Comparator>::const_iterator& other);
    const_set_iterator(typename AVLtree<Key, Key, Comparator>::node* node);
    const_reference operator*();
  };

  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s);
  ~set() = default;
  set& operator=(const set& s);
  set& operator=(set&& s);

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);

  iterator find(const Key& key);
  bool contains(const Key& key) const;

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};

template <typename Key, typename Comparator>
set<Key, Comparator>::set() : AVLtree<Key, Key, Comparator>() {}

template <typename Key, typename Comparator>
set<Key, Comparator>::set(std::initializer_list<value_type> const& items)
    : set() {
  for (auto item : items) {
    AVLtree<Key, Key, Comparator>::tree_unique_insert(item, item);
  }
}

template <typename Key, typename Comparator>
set<Key, Comparator>::set(const set& s) : AVLtree<Key, Key, Comparator>(s) {}

template <typename Key, typename Comparator>
set<Key, Comparator>::set(set&& s)
    : AVLtree<Key, Key, Comparator>(std::move(s)) {}

template <typename Key, typename Comparator>
set<Key, Comparator>& set<Key, Comparator>::operator=(const set& s) {
  AVLtree<Key, Key, Comparator>::operator=(s);
  return *this;
}

template <typename Key, typename Comparator>
set<Key, Comparator>& set<Key, Comparator>::operator=(set&& s) {
  AVLtree<Key, Key, Comparator>::operator=(std::move(s));
  return *this;
}

template <typename Key, typename Comparator>
typename set<Key, Comparator>::iterator set<Key, Comparator>::begin() {
  return set_iterator(AVLtree<Key, Key, Comparator>::root->parent_);
}

template <typename Key, typename Comparator>
typename set<Key, Comparator>::const_iterator set<Key, Comparator>::begin()
    const {
  return const_set_iterator(AVLtree<Key, Key, Comparator>::root->parent_);
}

template <typename Key, typename Comparator>
typename set<Key, Comparator>::iterator set<Key, Comparator>::end() {
  return set_iterator(
      static_cast<typename AVLtree<Key, Key, Comparator>::node*>(
          AVLtree<Key, Key, Comparator>::root));
}

template <typename Key, typename Comparator>
typename set<Key, Comparator>::const_iterator set<Key, Comparator>::end()
    const {
  return const_set_iterator(
      static_cast<typename AVLtree<Key, Key, Comparator>::node*>(
          AVLtree<Key, Key, Comparator>::root));
}

template <typename Key, typename Comparator>
bool set<Key, Comparator>::empty() const {
  return AVLtree<Key, Key, Comparator>::tree_empty();
}

template <typename Key, typename Comparator>
typename set<Key, Comparator>::size_type set<Key, Comparator>::size() const {
  return AVLtree<Key, Key, Comparator>::tree_size();
}

template <typename Key, typename Comparator>
typename set<Key, Comparator>::size_type set<Key, Comparator>::max_size()
    const {
  return AVLtree<Key, Key, Comparator>::tree_max_size();
}

template <typename Key, typename Comparator>
void set<Key, Comparator>::clear() {
  AVLtree<Key, Key, Comparator>::tree_clear();
}

template <typename Key, typename Comparator>
std::pair<typename set<Key, Comparator>::iterator, bool>
set<Key, Comparator>::insert(const value_type& value) {
  std::pair<set_iterator, bool> result =
      AVLtree<Key, Key, Comparator>::tree_unique_insert(value, value);
  return result;
}

template <typename Key, typename Comparator>
void set<Key, Comparator>::erase(iterator pos) {
  AVLtree<Key, Key, Comparator>::tree_erase(pos);
}

template <typename Key, typename Comparator>
void set<Key, Comparator>::swap(set& other) {
  AVLtree<Key, Key, Comparator>::tree_swap(other);
}

template <typename Key, typename Comparator>
void set<Key, Comparator>::merge(set& other) {
  AVLtree<Key, Key, Comparator>::tree_merge_unique(other);
}

template <typename Key, typename Comparator>
typename set<Key, Comparator>::iterator set<Key, Comparator>::find(
    const Key& key) {
  return AVLtree<Key, Key, Comparator>::tree_find(key);
}

template <typename Key, typename Comparator>
bool set<Key, Comparator>::contains(const Key& key) const {
  return AVLtree<Key, Key, Comparator>::tree_contains(key);
}

template <typename Key, typename Comparator>
inline set<Key, Comparator>::set_iterator::set_iterator(
    const typename AVLtree<Key, Key, Comparator>::iterator& other)
    : AVLtree<Key, Key, Comparator>::iterator::iterator(other) {}

template <typename Key, typename Comparator>
set<Key, Comparator>::set_iterator::set_iterator(
    typename AVLtree<Key, Key, Comparator>::node* node)
    : AVLtree<Key, Key, Comparator>::iterator::iterator(node) {}

template <typename Key, typename Comparator>
typename set<Key, Comparator>::reference
set<Key, Comparator>::set_iterator::operator*() {
  return AVLtree<Key, Key, Comparator>::iterator::current_node->data_.second;
}

template <typename Key, typename Comparator>
set<Key, Comparator>::const_set_iterator::const_set_iterator(
    const typename AVLtree<Key, Key, Comparator>::const_iterator& other)
    : AVLtree<Key, Key, Comparator>::const_iterator::const_iterator(other) {}

template <typename Key, typename Comparator>
set<Key, Comparator>::const_set_iterator::const_set_iterator(
    typename AVLtree<Key, Key, Comparator>::node* node)
    : AVLtree<Key, Key, Comparator>::const_iterator::const_iterator(node) {}

template <typename Key, typename Comparator>
typename set<Key, Comparator>::const_reference
set<Key, Comparator>::const_set_iterator::operator*() {
  return AVLtree<Key, Key, Comparator>::const_iterator::current_node->data_
      .second;
}

template <typename Key, typename Comparator>
template <class... Args>
std::vector<std::pair<typename set<Key, Comparator>::iterator, bool>>
set<Key, Comparator>::insert_many(Args&&... args) {
  std::vector<std::pair<typename set<Key, Comparator>::iterator, bool>> result;
  for (const auto& item : {args...}) {
    result.push_back(insert(item));
  }
  return result;
}

}  // namespace s21

#endif