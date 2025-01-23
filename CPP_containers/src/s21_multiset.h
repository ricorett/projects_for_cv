#ifndef S21_SRC_MULTISET_H
#define S21_SRC_MULTISET_H

#include <vector>

#include "AVLtree.h"

namespace s21 {
template <typename Key, typename Comparator = std::less<Key>>
class multiset : private AVLtree<Key, Key, Comparator> {
 public:
  class multiset_iterator;
  class const_multiset_iterator;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using pointer = value_type*;
  using const_reference = const value_type&;
  using const_pointer = const value_type*;
  using iterator = multiset_iterator;
  using const_iterator = const_multiset_iterator;
  using size_type = size_t;

  class multiset_iterator : public AVLtree<Key, Key, Comparator>::iterator {
   public:
    multiset_iterator() = default;
    multiset_iterator(
        const typename AVLtree<Key, Key, Comparator>::iterator& other);
    multiset_iterator(typename AVLtree<Key, Key, Comparator>::node* node);
    reference operator*();
  };

  class const_multiset_iterator
      : public AVLtree<Key, Key, Comparator>::const_iterator {
   public:
    const_multiset_iterator() = default;
    const_multiset_iterator(
        const typename AVLtree<Key, Key, Comparator>::const_iterator& other);
    const_multiset_iterator(typename AVLtree<Key, Key, Comparator>::node* node);
    const_reference operator*();
  };

  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms);
  ~multiset() = default;
  multiset& operator=(const multiset& ms);
  multiset& operator=(multiset&& ms);

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  size_type count(const Key& key) const;
  iterator find(const Key& key);
  bool contains(const Key& key) const;
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};

template <typename Key, typename Comparator>
multiset<Key, Comparator>::multiset() : AVLtree<Key, Key, Comparator>() {}

template <typename Key, typename Comparator>
multiset<Key, Comparator>::multiset(
    std::initializer_list<value_type> const& items)
    : multiset() {
  for (auto item : items) {
    AVLtree<Key, Key, Comparator>::tree_insert({item, item});
  }
}

template <typename Key, typename Comparator>
multiset<Key, Comparator>::multiset(const multiset& ms)
    : AVLtree<Key, Key, Comparator>(ms) {}

template <typename Key, typename Comparator>
multiset<Key, Comparator>::multiset(multiset&& ms)
    : AVLtree<Key, Key, Comparator>(std::move(ms)) {}

template <typename Key, typename Comparator>
multiset<Key, Comparator>& multiset<Key, Comparator>::operator=(
    const multiset& ms) {
  AVLtree<Key, Key, Comparator>::operator=(ms);
  return *this;
}

template <typename Key, typename Comparator>
multiset<Key, Comparator>& multiset<Key, Comparator>::operator=(multiset&& ms) {
  AVLtree<Key, Key, Comparator>::operator=(std::move(ms));
  return *this;
}

template <typename Key, typename Comparator>
typename multiset<Key, Comparator>::iterator
multiset<Key, Comparator>::begin() {
  return multiset_iterator(AVLtree<Key, Key, Comparator>::root->parent_);
}

template <typename Key, typename Comparator>
typename multiset<Key, Comparator>::const_iterator
multiset<Key, Comparator>::begin() const {
  return const_multiset_iterator(AVLtree<Key, Key, Comparator>::root->parent_);
}

template <typename Key, typename Comparator>
typename multiset<Key, Comparator>::iterator multiset<Key, Comparator>::end() {
  return multiset_iterator(
      static_cast<typename AVLtree<Key, Key, Comparator>::node*>(
          AVLtree<Key, Key, Comparator>::root));
}

template <typename Key, typename Comparator>
typename multiset<Key, Comparator>::const_iterator
multiset<Key, Comparator>::end() const {
  return const_multiset_iterator(
      static_cast<typename AVLtree<Key, Key, Comparator>::node*>(
          AVLtree<Key, Key, Comparator>::root));
}

template <typename Key, typename Comparator>
bool multiset<Key, Comparator>::empty() const {
  return AVLtree<Key, Key, Comparator>::tree_empty();
}

template <typename Key, typename Comparator>
typename multiset<Key, Comparator>::size_type multiset<Key, Comparator>::size()
    const {
  return AVLtree<Key, Key, Comparator>::tree_size();
}

template <typename Key, typename Comparator>
typename multiset<Key, Comparator>::size_type
multiset<Key, Comparator>::max_size() const {
  return AVLtree<Key, Key, Comparator>::tree_max_size();
}

template <typename Key, typename Comparator>
void multiset<Key, Comparator>::clear() {
  AVLtree<Key, Key, Comparator>::tree_clear();
}

template <typename Key, typename Comparator>
typename multiset<Key, Comparator>::iterator multiset<Key, Comparator>::insert(
    const value_type& value) {
  iterator result = AVLtree<Key, Key, Comparator>::tree_insert({value, value});
  return result;
}

template <typename Key, typename Comparator>
void multiset<Key, Comparator>::erase(iterator pos) {
  AVLtree<Key, Key, Comparator>::tree_erase(pos);
}

template <typename Key, typename Comparator>
void multiset<Key, Comparator>::swap(multiset& other) {
  AVLtree<Key, Key, Comparator>::tree_swap(other);
}

template <typename Key, typename Comparator>
void multiset<Key, Comparator>::merge(multiset& other) {
  AVLtree<Key, Key, Comparator>::tree_merge(other);
}

template <typename Key, typename Comparator>
typename multiset<Key, Comparator>::size_type multiset<Key, Comparator>::count(
    const Key& key) const {
  return AVLtree<Key, Key, Comparator>::tree_count(key);
}

template <typename Key, typename Comparator>
typename multiset<Key, Comparator>::iterator multiset<Key, Comparator>::find(
    const Key& key) {
  return AVLtree<Key, Key, Comparator>::tree_find(key);
}

template <typename Key, typename Comparator>
bool multiset<Key, Comparator>::contains(const Key& key) const {
  return AVLtree<Key, Key, Comparator>::tree_contains(key);
}

template <typename Key, typename Comparator>
inline std::pair<typename multiset<Key, Comparator>::iterator,
                 typename multiset<Key, Comparator>::iterator>
multiset<Key, Comparator>::equal_range(const Key& key) {
  return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
}

template <typename Key, typename Comparator>
typename multiset<Key, Comparator>::iterator
multiset<Key, Comparator>::lower_bound(const Key& key) {
  return iterator(AVLtree<Key, Key, Comparator>::tree_lower_bound(key));
}

template <typename Key, typename Comparator>
typename multiset<Key, Comparator>::iterator
multiset<Key, Comparator>::upper_bound(const Key& key) {
  return iterator(AVLtree<Key, Key, Comparator>::tree_upper_bound(key));
}

template <typename Key, typename Comparator>
inline multiset<Key, Comparator>::multiset_iterator::multiset_iterator(
    const typename AVLtree<Key, Key, Comparator>::iterator& other)
    : AVLtree<Key, Key, Comparator>::iterator::iterator(other) {}

template <typename Key, typename Comparator>
multiset<Key, Comparator>::multiset_iterator::multiset_iterator(
    typename AVLtree<Key, Key, Comparator>::node* node)
    : AVLtree<Key, Key, Comparator>::iterator::iterator(node) {}

template <typename Key, typename Comparator>
typename multiset<Key, Comparator>::reference
multiset<Key, Comparator>::multiset_iterator::operator*() {
  return AVLtree<Key, Key, Comparator>::iterator::current_node->data_.second;
}

template <typename Key, typename Comparator>
multiset<Key, Comparator>::const_multiset_iterator::const_multiset_iterator(
    const typename AVLtree<Key, Key, Comparator>::const_iterator& other)
    : AVLtree<Key, Key, Comparator>::const_iterator::const_iterator(other) {}

template <typename Key, typename Comparator>
multiset<Key, Comparator>::const_multiset_iterator::const_multiset_iterator(
    typename AVLtree<Key, Key, Comparator>::node* node)
    : AVLtree<Key, Key, Comparator>::const_iterator::const_iterator(node) {}

template <typename Key, typename Comparator>
typename multiset<Key, Comparator>::const_reference
multiset<Key, Comparator>::const_multiset_iterator::operator*() {
  return AVLtree<Key, Key, Comparator>::const_iterator::current_node->data_
      .second;
}

template <typename Key, typename Comparator>
template <class... Args>
std::vector<std::pair<typename multiset<Key, Comparator>::iterator, bool>>
multiset<Key, Comparator>::insert_many(Args&&... args) {
  std::vector<std::pair<typename multiset<Key, Comparator>::iterator, bool>>
      result;
  for (const auto& item : {args...}) {
    result.push_back({insert(item), true});
  }
  return result;
}

}  // namespace s21

#endif