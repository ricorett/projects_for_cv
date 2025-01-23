#ifndef S21_SRC_MAP_H
#define S21_SRC_MAP_H

#include <vector>

#include "AVLtree.h"
#include "exception"

namespace s21 {

template <typename Key, typename Value, typename Comparator = std::less<Key>>
class map : private AVLtree<Key, Value, Comparator> {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename AVLtree<Key, Value, Comparator>::iterator;
  using const_iterator =
      typename AVLtree<Key, Value, Comparator>::const_iterator;
  using size_type = size_t;

  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m);
  ~map() = default;
  map& operator=(const map& m);
  map& operator=(map&& m);

  Value& at(const Key& key);
  Value& operator[](const Key& key);

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const Key& key, const Value& obj);
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const Value& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);

  bool contains(const Key& key) const;

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};

template <typename Key, typename Value, typename Comparator>
map<Key, Value, Comparator>::map() : AVLtree<Key, Value, Comparator>() {}

template <typename Key, typename Value, typename Comparator>
map<Key, Value, Comparator>::map(std::initializer_list<value_type> const& items)
    : map() {
  for (auto item : items) {
    AVLtree<Key, Value, Comparator>::tree_unique_insert(item);
  }
}

template <typename Key, typename Value, typename Comparator>
map<Key, Value, Comparator>::map(const map& m)
    : AVLtree<Key, Value, Comparator>(m) {}

template <typename Key, typename Value, typename Comparator>
map<Key, Value, Comparator>::map(map&& m)
    : AVLtree<Key, Value, Comparator>(std::move(m)) {}

template <typename Key, typename Value, typename Comparator>
map<Key, Value, Comparator>& map<Key, Value, Comparator>::operator=(
    const map& m) {
  AVLtree<Key, Value, Comparator>::operator=(m);
  return *this;
}

template <typename Key, typename Value, typename Comparator>
map<Key, Value, Comparator>& map<Key, Value, Comparator>::operator=(map&& m) {
  AVLtree<Key, Value, Comparator>::operator=(std::move(m));
  return *this;
}

template <typename Key, typename Value, typename Comparator>
Value& map<Key, Value, Comparator>::at(const Key& key) {
  return AVLtree<Key, Value, Comparator>::at(key);
}

template <typename Key, typename Value, typename Comparator>
Value& map<Key, Value, Comparator>::operator[](const Key& key) {
  return AVLtree<Key, Value, Comparator>::operator[](key);
}

template <typename Key, typename Value, typename Comparator>
typename map<Key, Value, Comparator>::iterator
map<Key, Value, Comparator>::begin() {
  return AVLtree<Key, Value, Comparator>::tree_begin();
}

template <typename Key, typename Value, typename Comparator>
typename map<Key, Value, Comparator>::const_iterator
map<Key, Value, Comparator>::begin() const {
  return AVLtree<Key, Value, Comparator>::const_tree_begin();
}

template <typename Key, typename Value, typename Comparator>
typename map<Key, Value, Comparator>::iterator
map<Key, Value, Comparator>::end() {
  return AVLtree<Key, Value, Comparator>::tree_end();
}

template <typename Key, typename Value, typename Comparator>
typename map<Key, Value, Comparator>::const_iterator
map<Key, Value, Comparator>::end() const {
  return AVLtree<Key, Value, Comparator>::const_tree_end();
}

template <typename Key, typename Value, typename Comparator>
bool map<Key, Value, Comparator>::empty() const {
  return AVLtree<Key, Value, Comparator>::tree_empty();
}

template <typename Key, typename Value, typename Comparator>
typename map<Key, Value, Comparator>::size_type
map<Key, Value, Comparator>::size() const {
  return AVLtree<Key, Value, Comparator>::tree_size();
}

template <typename Key, typename Value, typename Comparator>
typename map<Key, Value, Comparator>::size_type
map<Key, Value, Comparator>::max_size() const {
  return AVLtree<Key, Value, Comparator>::tree_max_size();
}

template <typename Key, typename Value, typename Comparator>
void map<Key, Value, Comparator>::clear() {
  AVLtree<Key, Value, Comparator>::tree_clear();
}

template <typename Key, typename Value, typename Comparator>
std::pair<typename map<Key, Value, Comparator>::iterator, bool>
map<Key, Value, Comparator>::insert(const Key& key, const Value& obj) {
  return AVLtree<Key, Value, Comparator>::tree_unique_insert(key, obj);
}

template <typename Key, typename Value, typename Comparator>
std::pair<typename map<Key, Value, Comparator>::iterator, bool>
map<Key, Value, Comparator>::insert(const value_type& value) {
  return AVLtree<Key, Value, Comparator>::tree_unique_insert(value);
}

template <typename Key, typename Value, typename Comparator>
std::pair<typename map<Key, Value, Comparator>::iterator, bool>
map<Key, Value, Comparator>::insert_or_assign(const Key& key,
                                              const Value& obj) {
  return AVLtree<Key, Value, Comparator>::tree_insert_or_assign(key, obj);
}

template <typename Key, typename Value, typename Comparator>
void map<Key, Value, Comparator>::erase(iterator pos) {
  AVLtree<Key, Value, Comparator>::tree_erase(pos);
}

template <typename Key, typename Value, typename Comparator>
void map<Key, Value, Comparator>::swap(map& other) {
  AVLtree<Key, Value, Comparator>::tree_swap(other);
}

template <typename Key, typename Value, typename Comparator>
void map<Key, Value, Comparator>::merge(map& other) {
  AVLtree<Key, Value, Comparator>::tree_merge_unique(other);
}

template <typename Key, typename Value, typename Comparator>
bool map<Key, Value, Comparator>::contains(const Key& key) const {
  return AVLtree<Key, Value, Comparator>::tree_contains(key);
}

template <typename Key, typename Value, typename Comparator>
template <class... Args>
std::vector<std::pair<typename map<Key, Value, Comparator>::iterator, bool>>
map<Key, Value, Comparator>::insert_many(Args&&... args) {
  std::vector<std::pair<typename map<Key, Value, Comparator>::iterator, bool>>
      result;
  for (const auto& item : {args...}) {
    result.push_back(insert(item));
  }
  return result;
}

}  // namespace s21

#endif