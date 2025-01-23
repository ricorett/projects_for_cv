#ifndef S21_SRC_AVLTREE_H
#define S21_SRC_AVLTREE_H

#include <functional>
#include <limits>

namespace s21 {

template <typename Key, typename Value, typename Comparator = std::less<Key>>
class AVLtree {
 protected:
  struct node;
  struct base_node;

 public:
  using value_type = std::pair<const Key, Value>;
  using value_reference = value_type&;
  using const_reference = const value_type&;
  using value_pointer = value_type*;
  using const_pointer = const value_type*;
  using size_type = size_t;

  class iterator {
   public:
    friend AVLtree;
    iterator();
    iterator(const iterator& other);
    explicit iterator(node* node_ptr);
    void operator=(node* node_ptr);
    iterator& operator=(const iterator& other) = default;

    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);

    bool operator!=(const iterator& other) const;
    bool operator==(const iterator& other) const;

    value_reference operator*();
    value_pointer operator->();

   protected:
    node* current_node;
    void move_forward();
    void move_back();
  };

  class const_iterator {
   public:
    friend AVLtree;
    const_iterator();
    explicit const_iterator(node* node_ptr);
    void operator=(node* node_ptr);

    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator--();
    const_iterator operator--(int);

    bool operator!=(const const_iterator& other) const;
    bool operator==(const const_iterator& other) const;

    const_reference operator*();
    const_pointer operator->();

   protected:
    const node* current_node;
    void move_forward();
    void move_back();
  };

  AVLtree();
  AVLtree(const AVLtree& other);
  AVLtree(AVLtree&& other);
  ~AVLtree();
  AVLtree& operator=(const AVLtree& other);
  AVLtree& operator=(AVLtree&& other);

  iterator tree_insert(const_reference data);
  std::pair<iterator, bool> tree_unique_insert(const_reference value);
  std::pair<iterator, bool> tree_unique_insert(const Key& key,
                                               const Value& obj);
  std::pair<iterator, bool> tree_insert_or_assign(const Key& key,
                                                  const Value& obj);
  Value& at(const Key& key);
  Value& operator[](const Key& key);
  void tree_erase(iterator pos);
  void tree_clear();
  void tree_merge(AVLtree& other);
  void tree_merge_unique(AVLtree& other);
  void tree_swap(AVLtree& other);
  iterator tree_find(const Key& key);
  bool tree_contains(const Key& key) const;
  size_type tree_count(const Key& key) const;
  const_iterator tree_lower_bound(const Key& key) const;
  const_iterator tree_upper_bound(const Key& key) const;
  iterator tree_lower_bound(const Key& key);
  iterator tree_upper_bound(const Key& key);
  size_type tree_size() const;
  size_type tree_max_size() const;
  bool tree_empty() const;
  iterator tree_begin();
  const_iterator const_tree_begin() const;
  iterator tree_end();
  const_iterator const_tree_end() const;

 protected:
  struct base_node {
    node* left;
    node* right;
    node* parent_;
    base_node();
    base_node(node* Left, node* Right, node* Parent);
  };

  struct node : public base_node {
    value_type data_;
    int8_t height = 0;
    node(value_type data, node* parent);
  };

  int8_t get_height(node* node_ptr);
  int balance_factor(node* node_ptr);
  void set_height(node* node_ptr);
  void rotateright(node*& node_ptr);
  void rotateleft(node*& node_ptr);
  void balance(node*& node_ptr);
  iterator recursive_insert(node*& root, value_type data);
  std::pair<iterator, bool> unique_recursive_insert(node*& root,
                                                    value_type data);
  void recursive_delete(node*& node_ptr, value_type data);
  std::pair<iterator, node*> recursive_find(node* root, const Key& key) const;
  static node* find_min(node* node_ptr);
  static node* find_max(node* node_ptr);
  node* remove_min(node* node_ptr);
  node* copy_tree(node* node_ptr, node* parent);

  friend iterator;
  base_node* root;
  size_type size_;
  Comparator tree_comparator;

  void destroy(node* root);
};

//----AVLtree-logic-----//

template <typename Key, typename Value, typename Comparator>
inline AVLtree<Key, Value, Comparator>::AVLtree()
    : root(new base_node), size_(0) {}

template <typename Key, typename Value, typename Comparator>
AVLtree<Key, Value, Comparator>::AVLtree(const AVLtree& other) : AVLtree() {
  root->left = copy_tree(other.root->left, nullptr);
  root->left->parent_ = static_cast<node*>(root);
  root->parent_ = find_min(root->left);
  size_ = other.size_;
}

template <typename Key, typename Value, typename Comparator>
AVLtree<Key, Value, Comparator>::AVLtree(AVLtree&& other) : AVLtree() {
  tree_swap(other);
}

template <typename Key, typename Value, typename Comparator>
AVLtree<Key, Value, Comparator>::~AVLtree() {
  if (root->left != root) {
    destroy(root->left);
  }
  delete root;
  root = nullptr;
}

template <typename Key, typename Value, typename Comparator>
AVLtree<Key, Value, Comparator>& AVLtree<Key, Value, Comparator>::operator=(
    const AVLtree& other) {
  if (this != &other) {
    if (other.tree_size() > 0) {
      AVLtree copy(other);
      tree_clear();
      *this = std::move(copy);
    } else {
      tree_clear();
    }
  }
  return *this;
}

template <typename Key, typename Value, typename Comparator>
AVLtree<Key, Value, Comparator>& AVLtree<Key, Value, Comparator>::operator=(
    AVLtree&& other) {
  if (this != &other) {
    tree_clear();
    tree_swap(other);
  }
  return *this;
}

template <typename Key, typename Value, typename Comparator>
inline void AVLtree<Key, Value, Comparator>::tree_swap(AVLtree& other) {
  std::swap(root, other.root);
  std::swap(size_, other.size_);
  std::swap(tree_comparator, other.tree_comparator);
}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::destroy(node* root) {
  if (root == nullptr) {
    return;
  }
  destroy(root->left);
  destroy(root->right);
  delete root;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::iterator
AVLtree<Key, Value, Comparator>::tree_begin() {
  return iterator(root->parent_);
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::const_iterator
AVLtree<Key, Value, Comparator>::const_tree_begin() const {
  return const_iterator(root->parent_);
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::iterator
AVLtree<Key, Value, Comparator>::tree_end() {
  return iterator(static_cast<node*>(root));
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::const_iterator
AVLtree<Key, Value, Comparator>::const_tree_end() const {
  return const_iterator(static_cast<node*>(root));
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::iterator
AVLtree<Key, Value, Comparator>::tree_insert(const_reference data) {
  iterator result;
  if (root->left == static_cast<node*>(root)) {
    root->left = new node(data, nullptr);
    root->left->parent_ = static_cast<node*>(root);
    root->parent_ = root->left;
    result = root->left;
  } else {
    result = recursive_insert(root->left, data);
    root->parent_ = find_min(root->left);
  }
  ++size_;
  return result;
}

template <typename Key, typename Value, typename Comparator>
std::pair<typename AVLtree<Key, Value, Comparator>::iterator, bool>
AVLtree<Key, Value, Comparator>::tree_unique_insert(const_reference value) {
  std::pair<iterator, bool> result;
  if (root->left == static_cast<node*>(root)) {
    root->left = new node(value, nullptr);
    root->left->parent_ = static_cast<node*>(root);
    root->parent_ = root->left;
    result.first = root->left;
    result.second = true;
  } else {
    result = unique_recursive_insert(root->left, value);
    root->parent_ = find_min(root->left);
  }
  if (result.second) {
    ++size_;
  }
  return result;
}

template <typename Key, typename Value, typename Comparator>
std::pair<typename AVLtree<Key, Value, Comparator>::iterator, bool>
AVLtree<Key, Value, Comparator>::tree_unique_insert(const Key& key,
                                                    const Value& obj) {
  std::pair<iterator, bool> result;
  value_type value{key, obj};
  if (root->left == static_cast<node*>(root)) {
    root->left = new node(value, nullptr);
    root->left->parent_ = static_cast<node*>(root);
    root->parent_ = root->left;
    result.first = root->left;
    result.second = true;
  } else {
    result = unique_recursive_insert(root->left, value);
    root->parent_ = find_min(root->left);
  }
  if (result.second) {
    ++size_;
  }
  return result;
}

template <typename Key, typename Value, typename Comparator>
std::pair<typename AVLtree<Key, Value, Comparator>::iterator, bool>
AVLtree<Key, Value, Comparator>::tree_insert_or_assign(const Key& key,
                                                       const Value& obj) {
  std::pair<iterator, bool> result = tree_unique_insert(key, obj);
  if (result.second == false) {
    result.first.current_node->data_.second = obj;
  }
  return result;
}

template <typename Key, typename Value, typename Comparator>
Value& AVLtree<Key, Value, Comparator>::at(const Key& key) {
  iterator result = tree_find(key);
  if (result == tree_end()) {
    throw std::out_of_range("There is no element with this key");
  }
  return result.current_node->data_.second;
}

template <typename Key, typename Value, typename Comparator>
Value& AVLtree<Key, Value, Comparator>::operator[](const Key& key) {
  iterator search_result = AVLtree<Key, Value, Comparator>::tree_find(key);
  if (search_result == tree_end()) {
    auto insert_result =
        AVLtree<Key, Value, Comparator>::tree_unique_insert(key, Value{});
    return insert_result.first.current_node->data_.second;
  }
  return search_result.current_node->data_.second;
}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::tree_erase(iterator pos) {
  recursive_delete(root->left, pos.current_node->data_);
  root->parent_ = find_min(root->left);
}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::tree_clear() {
  if (root->left != root) {
    destroy(root->left);
  }
  delete root;
  root = new base_node;
  size_ = 0;
}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::tree_merge(AVLtree& other) {
  AVLtree copy(other);
  for (auto i = copy.tree_begin(); i != copy.tree_end(); ++i) {
    iterator insert_result = tree_insert(i.current_node->data_);
    other.tree_erase(insert_result);
  }
  if (other.tree_empty()) {
    other.tree_clear();
  }
}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::tree_merge_unique(AVLtree& other) {
  AVLtree copy(other);
  for (auto i = copy.tree_begin(); i != copy.tree_end(); ++i) {
    std::pair<iterator, bool> insert_result =
        tree_unique_insert(i.current_node->data_);
    if (insert_result.second) {
      other.tree_erase(insert_result.first);
    }
  }
  if (other.tree_empty()) {
    other.tree_clear();
  }
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::iterator
AVLtree<Key, Value, Comparator>::tree_find(const Key& key) {
  std::pair<iterator, node*> result = recursive_find(root->left, key);
  if (result.second == nullptr) {
    return tree_end();
  }
  return result.first;
}

template <typename Key, typename Value, typename Comparator>
bool AVLtree<Key, Value, Comparator>::tree_contains(const Key& key) const {
  return recursive_find(root->left, key).second != nullptr;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::size_type
AVLtree<Key, Value, Comparator>::tree_count(const Key& key) const {
  size_type count = 0;
  if (tree_contains(key)) {
    auto lowerbound = tree_lower_bound(key);
    auto upperbound = tree_upper_bound(key);
    while (lowerbound != upperbound) {
      ++count;
      ++lowerbound;
    }
  }
  return count;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::const_iterator
AVLtree<Key, Value, Comparator>::tree_lower_bound(const Key& key) const {
  const_iterator result = const_tree_begin();
  for (; result != const_tree_end(); ++result) {
    if (result.current_node->data_.first >= key) {
      break;
    }
  }
  return result;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::const_iterator
AVLtree<Key, Value, Comparator>::tree_upper_bound(const Key& key) const {
  const_iterator result = const_tree_end();
  if (!tree_empty()) {
    --result;
    for (; result != const_tree_begin(); --result) {
      if (result.current_node->data_.first == key) {
        ++result;
        break;
      }
    }
    --result;
    if (result.current_node->data_.first == key) {
      ++result;
    } else {
      result = const_tree_end();
    }
  }
  return result;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::iterator
AVLtree<Key, Value, Comparator>::tree_lower_bound(const Key& key) {
  auto result = tree_begin();
  for (; result != tree_end(); ++result) {
    if (result.current_node->data_.first >= key) {
      break;
    }
  }
  return result;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::iterator
AVLtree<Key, Value, Comparator>::tree_upper_bound(const Key& key) {
  auto result = tree_end();
  if (!tree_empty()) {
    --result;
    for (; result != tree_begin(); --result) {
      if (result.current_node->data_.first == key) {
        ++result;
        break;
      }
    }
    --result;
    if (result.current_node->data_.first == key) {
      ++result;
    } else {
      result = tree_end();
    }
  }
  return result;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::size_type
AVLtree<Key, Value, Comparator>::tree_size() const {
  return size_;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::size_type
AVLtree<Key, Value, Comparator>::tree_max_size() const {
  return ((std::numeric_limits<size_type>::max() -
           (sizeof(AVLtree) + sizeof(base_node))) /
          sizeof(node)) /
             2 +
         1;
}

template <typename Key, typename Value, typename Comparator>
bool AVLtree<Key, Value, Comparator>::tree_empty() const {
  return size_ == 0;
}

//---itarator-logic---/

template <typename Key, typename Value, typename Comparator>
AVLtree<Key, Value, Comparator>::iterator::iterator() : current_node(nullptr) {}

template <typename Key, typename Value, typename Comparator>
AVLtree<Key, Value, Comparator>::iterator::iterator(const iterator& other)
    : current_node(other.current_node) {}

template <typename Key, typename Value, typename Comparator>
inline AVLtree<Key, Value, Comparator>::iterator::iterator(node* node_ptr)
    : current_node(node_ptr) {}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::iterator::operator=(node* node_ptr) {
  current_node = node_ptr;
}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::iterator::move_forward() {
  if (current_node->right != nullptr) {
    current_node = find_min(current_node->right);
  } else {
    while (current_node != nullptr && current_node->parent_ != nullptr &&
           current_node == current_node->parent_->right) {
      current_node = current_node->parent_;
    }
    if (current_node) {
      current_node = current_node->parent_;
    }
  }
}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::iterator::move_back() {
  if (current_node->left != nullptr) {
    current_node = find_max(current_node->left);
  } else {
    node* tmp = current_node->parent_;
    while (tmp != nullptr && current_node == tmp->left) {
      current_node = tmp;
      tmp = current_node->parent_;
    }
    current_node = tmp;
  }
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::iterator&
AVLtree<Key, Value, Comparator>::iterator::operator++() {
  move_forward();
  return *this;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::iterator
AVLtree<Key, Value, Comparator>::iterator::operator++(int) {
  iterator copy = *this;
  move_forward();
  return copy;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::iterator&
AVLtree<Key, Value, Comparator>::iterator::operator--() {
  move_back();
  return *this;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::iterator
AVLtree<Key, Value, Comparator>::iterator::operator--(int) {
  iterator copy = *this;
  move_back();
  return copy;
}

template <typename Key, typename Value, typename Comparator>
bool AVLtree<Key, Value, Comparator>::iterator::operator==(
    const iterator& other) const {
  return current_node == other.current_node;
}

template <typename Key, typename Value, typename Comparator>
bool AVLtree<Key, Value, Comparator>::iterator::operator!=(
    const iterator& other) const {
  return !operator==(other);
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::value_reference
AVLtree<Key, Value, Comparator>::iterator::operator*() {
  return current_node->data_;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::value_pointer
AVLtree<Key, Value, Comparator>::iterator::operator->() {
  return &(current_node->data_);
}

// const-iterator logic//

template <typename Key, typename Value, typename Comparator>
AVLtree<Key, Value, Comparator>::const_iterator::const_iterator()
    : current_node(nullptr) {}

template <typename Key, typename Value, typename Comparator>
inline AVLtree<Key, Value, Comparator>::const_iterator::const_iterator(
    node* node_ptr)
    : current_node(node_ptr) {}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::const_iterator::operator=(
    node* node_ptr) {
  current_node = node_ptr;
}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::const_iterator::move_forward() {
  if (current_node->right != nullptr) {
    current_node = find_min(current_node->right);
  } else {
    while (current_node != nullptr && current_node->parent_ != nullptr &&
           current_node == current_node->parent_->right) {
      current_node = current_node->parent_;
    }
    current_node = current_node->parent_;
  }
}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::const_iterator::move_back() {
  if (current_node->left != nullptr) {
    current_node = find_max(current_node->left);
  } else {
    node* tmp = current_node->parent_;
    while (tmp != nullptr && current_node == tmp->left) {
      current_node = tmp;
      tmp = current_node->parent_;
    }
    current_node = tmp;
  }
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::const_iterator&
AVLtree<Key, Value, Comparator>::const_iterator::operator++() {
  move_forward();
  return *this;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::const_iterator
AVLtree<Key, Value, Comparator>::const_iterator::operator++(int) {
  const_iterator copy = *this;
  move_forward();
  return copy;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::const_iterator&
AVLtree<Key, Value, Comparator>::const_iterator::operator--() {
  move_back();
  return *this;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::const_iterator
AVLtree<Key, Value, Comparator>::const_iterator::operator--(int) {
  const_iterator copy = *this;
  move_back();
  return copy;
}

template <typename Key, typename Value, typename Comparator>
bool AVLtree<Key, Value, Comparator>::const_iterator::operator==(
    const const_iterator& other) const {
  return current_node == other.current_node;
}

template <typename Key, typename Value, typename Comparator>
bool AVLtree<Key, Value, Comparator>::const_iterator::operator!=(
    const const_iterator& other) const {
  return !operator==(other);
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::const_reference
AVLtree<Key, Value, Comparator>::const_iterator::operator*() {
  return current_node->data_;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::const_pointer
AVLtree<Key, Value, Comparator>::const_iterator::operator->() {
  return &(current_node->data_);
}

// nodes logic//

template <typename Key, typename Value, typename Comparator>
inline AVLtree<Key, Value, Comparator>::base_node::base_node()
    : left(static_cast<node*>(this)),
      right(nullptr),
      parent_(static_cast<node*>(this)) {}

template <typename Key, typename Value, typename Comparator>
inline AVLtree<Key, Value, Comparator>::base_node::base_node(node* Left,
                                                             node* Right,
                                                             node* Parent)
    : left(Left), right(Right), parent_(Parent) {}

template <typename Key, typename Value, typename Comparator>
inline AVLtree<Key, Value, Comparator>::node::node(value_type data,
                                                   node* parent)
    : base_node{nullptr, nullptr, parent}, data_(data) {}

template <typename Key, typename Value, typename Comparator>
inline int8_t AVLtree<Key, Value, Comparator>::get_height(node* node_ptr) {
  return node_ptr ? node_ptr->height : -1;
}

template <typename Key, typename Value, typename Comparator>
inline int AVLtree<Key, Value, Comparator>::balance_factor(node* node_ptr) {
  return node_ptr ? get_height(node_ptr->right) - get_height(node_ptr->left)
                  : 0;
}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::set_height(node* node_ptr) {
  int8_t hl = get_height(node_ptr->left);
  int8_t hr = get_height(node_ptr->right);
  node_ptr->height = (hl > hr ? hl : hr) + 1;
}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::rotateright(node*& node_ptr) {
  node* tmp = node_ptr->left;
  node_ptr->left = tmp->right;

  if (node_ptr->left) {
    node_ptr->left->parent_ = node_ptr;
  }

  tmp->right = node_ptr;
  tmp->parent_ = node_ptr->parent_;
  node_ptr->parent_ = tmp;
  set_height(node_ptr);
  set_height(tmp);
  node_ptr = tmp;
}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::rotateleft(node*& node_ptr) {
  node* tmp = node_ptr->right;
  node_ptr->right = tmp->left;

  if (node_ptr->right) {
    node_ptr->right->parent_ = node_ptr;
  }

  tmp->left = node_ptr;
  tmp->parent_ = node_ptr->parent_;
  node_ptr->parent_ = tmp;
  set_height(node_ptr);
  set_height(tmp);
  node_ptr = tmp;
}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::balance(node*& node_ptr) {
  if (balance_factor(node_ptr) == 2) {
    if (balance_factor(node_ptr->right) < 0) {
      rotateright(node_ptr->right);
    }
    rotateleft(node_ptr);
  }
  if (balance_factor(node_ptr) == -2) {
    if (balance_factor(node_ptr->left) > 0) {
      rotateleft(node_ptr->left);
    }
    rotateright(node_ptr);
  }
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::iterator
AVLtree<Key, Value, Comparator>::recursive_insert(node*& root,
                                                  value_type data) {
  iterator result;
  if (tree_comparator(data.first, root->data_.first)) {
    if (root->left == nullptr) {
      root->left = new node(data, root);
      result = root->left;
    } else {
      result = recursive_insert(root->left, data);
    }
  } else {
    if (root->right == nullptr) {
      root->right = new node(data, root);
      result = root->right;
    } else {
      result = recursive_insert(root->right, data);
    }
  }
  set_height(root);
  balance(root);
  return result;
}

template <typename Key, typename Value, typename Comparator>
std::pair<typename AVLtree<Key, Value, Comparator>::iterator, bool>
AVLtree<Key, Value, Comparator>::unique_recursive_insert(node*& root,
                                                         value_type data) {
  std::pair<iterator, bool> result;

  if (tree_comparator(data.first, root->data_.first)) {
    if (root->left == nullptr) {
      root->left = new node(data, root);
      result.first = root->left;
      result.second = true;
    } else {
      result = unique_recursive_insert(root->left, data);
    }
  } else if (tree_comparator(root->data_.first, data.first)) {
    if (root->right == nullptr) {
      root->right = new node(data, root);
      result.first = root->right;
      result.second = true;
    } else {
      result = unique_recursive_insert(root->right, data);
    }
  } else {
    result.first = root;
    result.second = false;
  }
  set_height(root);
  balance(root);

  return result;
}

template <typename Key, typename Value, typename Comparator>
void AVLtree<Key, Value, Comparator>::recursive_delete(node*& node_ptr,
                                                       value_type data) {
  if (!node_ptr) {
    node_ptr = nullptr;
    return;
  }
  if (tree_comparator(data.first, node_ptr->data_.first)) {
    recursive_delete(node_ptr->left, data);
  } else if (tree_comparator(node_ptr->data_.first, data.first)) {
    recursive_delete(node_ptr->right, data);
  } else {
    node* tmp_left = node_ptr->left;
    node* tmp_right = node_ptr->right;
    node* deleting_parent = node_ptr->parent_;
    delete node_ptr;
    node_ptr = nullptr;
    --size_;
    if (!tmp_right) {
      node_ptr = tmp_left;
      if (node_ptr) node_ptr->parent_ = deleting_parent;
      return;
    }
    node* min = find_min(tmp_right);
    min->right = remove_min(tmp_right);
    min->left = tmp_left;
    if (min->left) {
      min->left->parent_ = min;
    }
    if (min->right) {
      min->right->parent_ = min;
    }
    min->parent_ = deleting_parent;
    balance(min);
    node_ptr = min;
  }
  balance(node_ptr);
}

template <typename Key, typename Value, typename Comparator>
std::pair<typename AVLtree<Key, Value, Comparator>::iterator,
          typename AVLtree<Key, Value, Comparator>::node*>
AVLtree<Key, Value, Comparator>::recursive_find(node* root,
                                                const Key& key) const {
  std::pair<iterator, node*> result;
  if (root == nullptr) {
    result.second = root;
    return result;
  }
  if (root->data_.first == key) {
    result.first = root;
    result.second = root;
    return result;
  }
  if (tree_comparator(root->data_.first, key)) {
    result = recursive_find(root->right, key);
  } else {
    result = recursive_find(root->left, key);
  }
  if (result.second == nullptr) {
    result.first = root;
    result.second = nullptr;
  }
  return result;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::node*
AVLtree<Key, Value, Comparator>::find_min(node* node_ptr) {
  if (!node_ptr) {
    return nullptr;
  }
  return node_ptr->left ? find_min(node_ptr->left) : node_ptr;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::node*
AVLtree<Key, Value, Comparator>::find_max(node* node_ptr) {
  return node_ptr->right ? find_max(node_ptr->right) : node_ptr;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::node*
AVLtree<Key, Value, Comparator>::remove_min(node* node_ptr) {
  if (!node_ptr->left) {
    return node_ptr->right;
  }
  node_ptr->left = remove_min(node_ptr->left);
  balance(node_ptr);
  return node_ptr;
}

template <typename Key, typename Value, typename Comparator>
typename AVLtree<Key, Value, Comparator>::node*
AVLtree<Key, Value, Comparator>::copy_tree(node* node_ptr, node* parent) {
  if (!node_ptr) {
    return nullptr;
  }
  node* new_node = new node(node_ptr->data_, parent);
  new_node->left = copy_tree(node_ptr->left, new_node);
  new_node->right = copy_tree(node_ptr->right, new_node);
  return new_node;
}

}  // namespace s21

#endif