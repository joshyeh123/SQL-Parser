// FILE: bplustree.h
// TEMPLATE CLASS PROVIDED: BPlusTree<Item>
//   (a container template class for a BPlusTree of items)
//
// TYPEDEFS for the BPlusTree<Item> class:
//   BPlusTree<Item>::value_type
//     BPlusTree<Item>::value_type is the data type of the items in the
//     BPlusTree. It may be any of the C++ built-in types (int, char, etc.), or
//     a class with a default constructor, a copy constructor, an assignment
//     operator, and a less-than operator forming a strict weak ordering.
//
// CONSTRUCTOR for the BPlusTree<Item> class:
//   BPlusTree()
//     Postcondition: The BPlusTree is empty.
//
//   BPlusTree(const BPlusTree& source)
//     Postcondition: The BPlusTree is same as source. (copy constructor)
//
//   BPlusTree(Item* a, std::size_t size)
//     Postcondition: Insert entry from array to BPlusTree.
//
// MODIFICATION MEMBER FUNCTIONS for the BPlusTree<Item> class:
//   void clear_tree()
//     Postcondition: The BPlusTree is empty, delete all nodes etc.
//
//   void copy_tree(const BPlusTree& source)
//     Postcondition: The BPlusTree is copied.
//
//   void copy_tree(const BPlusTree& source, BPlusTree*& last_node);
//     Postcondition: The BPlusTree is copied.
//
//   bool insert(const Item& entry)
//     Postcondition: If an equal entry was already in the BPlusTree, the
//     BPlusTree is unchanged and the return value is false. Otherwise, entry
//     was added to the BPlusTree and the return value is true.
//
//   bool erase(const Item& target)
//     Postcondition: If target was in the BPlusTree, then it has been removed
//     from the BPlusTree and the return value is true. Otherwise the BPlusTree
//     is unchanged and the return value is false.
//
// NON-CONSTANT MEMBER FUNCTIONS for the BPlusTree<Item> class:
//   Item* find(const Item& entry)
//     Postcondition: Returns a pointer of found entry, otherwise return
//     nullptr.
//
//   Item& get(const Item& entry)
//     Postcondition: Returns a reference of entry.
//
//   std::size_t size()
//     Postcondition: Returns count the number of leaves in the tree
//
//   std::size_t size_list()
//     Postcondition: Returns count the total number of value in the tree
//
//   Iterator lower_bound(const Item& key)
//     Postcondition: Returns an iterator pointing to the first element in the
//     leaves of the BPlusTree that is not less than (i.e. greater or equal to)
//     key.
//
//   Iterator upper_bound(const Item& key)
//     Postcondition: Returns an iterator pointing to the first element in the
//     leaves of the BPlusTree that is greater than key.
//
//   Iterator begin()
//     Postcondition: Returns an iterator pointing to the first element in the
//     leaves of the BPlusTree.
//
//   Iterator end()
//     Postcondition: Returns an empty iterator.
//
// CONSTANT MEMBER FUNCTIONS for the BPlusTree<Item> class:
//   bool contains(const Item& entry) const
//     Postcondition: Returns true if entry can be found, otherwise return
//     false.
//
//   const Item& get(const Item& entry) const
//     Postcondition: Returns a reference of entry.
//
//   std::size_t count() const
//     Postcondition: Returns count the number of nodes in the tree
//
//   bool empty() const
//     Postcondition: Returns true if the BPlusTree is empty; otherwise returns
//     false.
//
//   void print(int indent=0, std::ostream& outs = std::cout) const
//     Postcondition: Print the BPlusTree in readable version
//
//   bool is_valid() const
//     Postcondition: Returns true if the BPlusTree is valid, otherwise return
//     false.
//
// SUGGESTED FUNCTION FOR DEBUGGING
//   std::string in_order()
//     Postcondition: traverse the tree in_order, return a string of all the
//     data items with vertical delimiters
//
//   std::string pre_order()
//     Postcondition: traverse the tree pre_order, return a string of all the
//     data items with vertical delimiters
//
//   std::string post_order()
//     Postcondition: traverse the tree post_order, return a string of all the
//     data items with vertical delimiters
//
// HELPER MEMBER FUNCTIONS
//   bool is_leaf() const
//     Postcondition: Returns true if the BPlusTree is a leaf, otherwise return
//     false.
//
//   BPlusTree<Item>* get_smallest_node()
//     Postcondition: Returns a pointer to the smallest node in the BPlusTree.
//
//   bool loose_insert(const Item& entry)
//     Precondition: The entire B-tree is valid.
//     Postcondition: If entry was already in the BPlusTree, then the BPlusTree
//     is unchanged and the return value is false. Otherwise, the entry has been
//     added to the BPlusTree, the return value is true, and the entire B-tree
//     is still valid EXCEPT that the number of entries in the root of this
//     BPlusTree might be one more than the allowed maximum.
//
//   void fix_excess(std::size_t i);
//     Precondition: (i < child_count) and the entire B-tree is valid EXCEPT
//     that subset[i] has MAXIMUM + 1 entries. Postcondition: The tree has been
//     rearranged so that the entire B-tree is valid EXCEPT that the number of
//     entries in the root of this BPlusTree might be one more than the allowed
//     maximum.
//
//   bool loose_erase(const Item& target);
//     Precondition: The entire B-tree is valid.
//     Postcondition: If target was not in the BPlusTree, then the BPlusTree is
//     unchanged and the return value is false. Otherwise, the target has been
//     removed, the return value is true, and the entire B-tree is still valid
//     EXCEPT that the number of entries in the root of this BPlusTree might be
//     one less than the allowed minimum.
//
//   void fix_shortage(std::size_t i);
//     Precondition: (i < child_count) and the entire B-tree is valid EXCEPT
//     that subset[i] has MINIMUM - 1 entries. Postcondition: The tree has been
//     rearranged so that the entire B-tree is valid EXCEPT that the number of
//     entries in the root of this BPlusTree might be one less than the allowed
//     minimum.
//
//    void delete_internal_node(std::size_t i, const Item& target, const Item&
//    next_smallest)
//       Precondition: subset[i] is an internal node.
//       Postcondition: find target in data[i] or subset[i] or subset[i+1],
//       if so, replace it with next_smallest.
//
//    void transfer_from_left(std::size_t i)
//       Precondition: subset[i] has only MINIMUM - 1 entries, and
//       subset[i-1] has more than the minimum number of entries.
//       Postcondition: transfer an extra entry from subset[i-1].
//
//    void transfer_from_right(std::size_t i)
//       Precondition: subset[i] has only MINIMUM - 1 entries, and
//       subset[i+1] has more than the minimum number of entries.
//       Postcondition: transfer an extra entry from subset[i+1].
//
//    void merge_with_next_subset(std::size_t i)
//       Precondition: subset[i+1] has only MINIMUM - 1 entries, and
//       subset[i] has only minimum number of entries.
//       Postcondition: combine subset[i] with subset[i+1].

#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <cassert>  // Provides assert
#include <cstdlib>  // Provides size_t
#include <iomanip>  // Provides std::setw
#include <iostream> // Provides std::cout
#include <string>   // Provides std::to_string

#include "btree_array_functions.h" // Include the implementation.

template <class Item> class BPlusTree {
public:
  // TYPEDEFS and MEMBER CONSTANTS
  typedef Item value_type;
  // NESTED CLASS DEFINITION
  class Iterator {
  public:
    friend class BPlusTree;
    // CONSTRUCTORS
    Iterator(BPlusTree *_it = nullptr, std::size_t _key_ptr = 0)
        : it(_it), key_ptr(_key_ptr) {}
    // MODIFICATION MEMBER FUNCTIONS
    Item operator*() { return it->data[key_ptr]; }
    const Item operator*() const { return it->data[key_ptr]; }
    Iterator operator++(int un_used) { // Postfix ++ (it++)
      Iterator oldIt = *this;
      if (key_ptr == ((it->data_count) - 1)) {
        it = it->next;
        key_ptr = 0;
      } else {
        key_ptr++;
      }
      return oldIt;
    }
    Iterator operator++() { // Prefix ++ (++it)
      if (key_ptr == ((it->data_count) - 1)) {
        it = it->next;
        key_ptr = 0;
      } else {
        key_ptr++;
      }
      return *this;
    }
    // OVERLOADED OPERATORS
    friend bool operator==(const Iterator &lhs, const Iterator &rhs) {
      if ((lhs.it == rhs.it)) {
        return true;
      }
      return false;
    }
    friend bool operator!=(const Iterator &lhs, const Iterator &rhs) {
      return !(lhs == rhs);
    }
    // HELPER FUNCTIONS
    bool is_null() { return !it; }
    void print_Iterator() {
      std::cout << "iterator: " << it << " key_ptr: " << key_ptr << std::endl;
    }
    void info() const {}

  private:
    BPlusTree<Item> *it;
    std::size_t key_ptr;
  };

  // CONSTRUCTORS and DESTRUCTOR
  BPlusTree() {
    data_count = 0;
    child_count = 0;
    next = nullptr;
  }
  BPlusTree(const BPlusTree &source) {
    child_count = source.child_count;
    data_count = source.data_count;
    for (int i = 0; i < data_count; i++) {
      data[i] = source.data[i];
    }
    for (int i = 0; i < child_count; i++) {
      subset[i] = new BPlusTree(*(source.subset[i]));
    }
    next = nullptr;
  }
  BPlusTree(Item *a, std::size_t size) {
    data_count = 0;
    child_count = 0;
    next = nullptr;
    for (int i = 0; i < size; i++) {
      insert(a[i]);
    }
  }
  ~BPlusTree() { clear_tree(); }
  // MODIFICATION MEMBER FUNCTIONS
  BPlusTree &operator=(const BPlusTree &source) {
    copy_tree(source);
    return *this;
  }
  void clear_tree() {
    for (int i = 0; i < child_count; i++) {
      subset[i]->clear_tree();
      delete subset[i];
    }
    child_count = 0;
    data_count = 0;
    next = nullptr;
  }
  void copy_tree(const BPlusTree &source) {
    BPlusTree *none = new BPlusTree();
    copy_tree(source, none);
    none = none->next;
    delete none;
  }
  void copy_tree(const BPlusTree &source, BPlusTree *&last_node) {
    child_count = source.child_count;
    data_count = source.data_count;
    if (is_leaf()) {
      last_node->next = this;
      last_node = this;
    }
    next = nullptr;
    for (int i = 0; i < data_count; i++) {
      data[i] = source.data[i];
    }
    for (int i = 0; i < child_count; i++) {
      subset[i] = new BPlusTree();
      subset[i]->copy_tree(*source.subset[i], last_node);
    }
  }
  bool insert(const Item &entry) {
    if (!loose_insert(entry)) {
      return false;
    }
    if (data_count > MAXIMUM) {
      BPlusTree *newNode = new BPlusTree();
      copy_array(newNode->data, data, newNode->data_count, data_count);
      copy_array(newNode->subset, subset, newNode->child_count, child_count);
      data_count = 0;
      child_count = 0;
      next = nullptr;
      insert_item(subset, 0, child_count, newNode);
      fix_excess(0);
    }
    return true;
  }
  bool erase(const Item &target) {
    if (!loose_erase(target)) {
      return false;
    }
    if (data_count == 0 && child_count == 1) {
      BPlusTree *temp = subset[0];
      copy_array(data, temp->data, data_count, temp->data_count);
      copy_array(subset, temp->subset, child_count, temp->child_count);
      temp->child_count = 0;
      delete temp;
    }
    return true;
  }
  // NON-CONSTANT MEMBER FUNCTIONS
  Iterator find(const Item &entry) {
    int i = first_ge(data, data_count, entry);
    if (is_leaf()) {
      return i < data_count && !(data[i] > entry) ? Iterator(this, i)
                                                  : Iterator();
    } else {
      return i < data_count && !(data[i] > entry) ? subset[i + 1]->find(entry)
                                                  : subset[i]->find(entry);
    }
  }
  Item &get(const Item &entry) {
    Iterator iter = find(entry);
    return iter.it->data[iter.key_ptr];
  }
  std::size_t size() {
    BPlusTree *walker = get_smallest_node();
    int counter = 0;
    while (walker != nullptr) {
      for (int i = 0; i < walker->data_count; i++) {
        counter++;
      }
      walker = walker->next;
    }
    return counter;
  }
  std::size_t size_list() { return 1; }
  Iterator lower_bound(const Item &key) {
    Iterator walker = Iterator(get_smallest_node());
    while (walker != end()) {
      if (!(*walker < key)) {
        return walker;
      }
      walker++;
    }
    return walker;
  }
  Iterator upper_bound(const Item &key) {
    Iterator walker = Iterator(get_smallest_node());
    while (walker != end()) {
      if (*walker > key) {
        return walker;
      }
      walker++;
    }
    return walker;
  }
  Iterator begin() {
    if (empty()) {
      return Iterator();
    } else {
      return Iterator(get_smallest_node());
    }
  }
  Iterator end() { return Iterator(); }
  // CONSTANT MEMBER FUNCTIONS
  bool contains(const Item &entry) const {
    if (!(data_count > 0)) {
      return false;
    }
    int index = first_ge(data, data_count, entry);
    if (!(entry < data[index]) && index < data_count) {
      return true;
    } else {
      if (is_leaf()) {
        return false;
      }
      return subset[index]->contains(entry);
    }
    return false;
  }
  const Item &get(const Item &entry) const {
    Iterator iter = find(entry);
    return *iter;
  }
  std::size_t count() const {
    int count = data_count;
    if (!is_leaf()) {
      for (int i = 0; i < child_count; i++) {
        count += subset[i]->count();
      }
    }
    return count;
  }
  bool empty() const { return (data_count == 0 && is_leaf()); }
  void print(int indent = 0, std::ostream &outs = std::cout) const {
    std::string down_bracket = "\357\271\207"; // ﹇
    std::string up_bracket = "\357\271\210";   // ﹈
    if (is_leaf()) {
      std::cout << std::string(indent * 4, ' ') << down_bracket << std::endl;
      for (int i = data_count - 1; i > -1; i--) {
        std::cout << std::string(indent * 4, ' ') << data[i] << std::endl;
      }
      std::cout << std::string(indent * 4, ' ') << up_bracket << std::endl;
    } else {
      int i;
      for (i = child_count - 1; i > 0; i--) {
        subset[i]->print(indent + 1);
        if (i == child_count - 1) {
          std::cout << std::string(indent * 4, ' ') << down_bracket
                    << std::endl;
        }
        std::cout << std::string(indent * 4, ' ') << data[i - 1] << std::endl;
        if (i == 1) {
          std::cout << std::string(indent * 4, ' ') << up_bracket << std::endl;
        }
      }
      subset[i]->print(indent + 1);
    }
  }
  bool is_valid() const;
  // OVERLOAD OPERATOR FUNCTIONS
  friend std::ostream &operator<<(std::ostream &outs,
                                  const BPlusTree<Item> &btree) {
    btree.print(0, outs);
    return outs;
  }
  // SUGGESTED FUNCTION FOR DEBUGGING
  std::string in_order() {
    std::string str = "";
    if (!is_leaf()) {
      int i;
      for (i = 0; i < data_count; i++) {
        str += subset[i]->in_order();
        str += std::to_string(data[i]) + "|";
      }
      str += subset[i]->in_order();
    } else {
      for (int i = 0; i < data_count; i++) {
        str += std::to_string(data[i]) + "|";
      }
    }
    return str;
  }
  std::string pre_order() {
    std::string str = "";
    if (!is_leaf()) {
      int i;
      for (i = 0; i < data_count; i++) {
        str += std::to_string(data[i]) + "|";
        str += subset[i]->pre_order();
      }
      str += subset[i]->pre_order();
    } else {
      for (int i = 0; i < data_count; i++) {
        str += std::to_string(data[i]) + "|";
      }
    }
    return str;
  }
  std::string post_order() {
    std::string str = "";
    if (!is_leaf()) {
      for (int i = 0; i < data_count; i++) {
        if (i == 0) {
          str += subset[i]->post_order();
        }
        str += subset[i + 1]->post_order();
        str += std::to_string(data[i]) + "|";
      }
    } else {
      for (int i = 0; i < data_count; i++) {
        str += std::to_string(data[i]) + "|";
      }
    }
    return str;
  }

private:
  // MEMBER CONSTANTS
  static const std::size_t MINIMUM = 1;
  static const std::size_t MAXIMUM = 2 * MINIMUM;
  // MEMBER VARIABLES
  std::size_t data_count;
  Item data[MAXIMUM + 1];
  std::size_t child_count;
  BPlusTree *subset[MAXIMUM + 2];
  BPlusTree *next;
  // HELPER MEMBER FUNCTIONS
  bool is_leaf() const { return (child_count == 0); }
  BPlusTree<Item> *get_smallest_node() {

    if (!is_leaf()) {
      return subset[0]->get_smallest_node();
    } else {
      return this;
    }
  }
  // insert element functions
  bool loose_insert(const Item &entry) {
    int i = first_ge(data, data_count, entry);
    if (is_leaf() && i < data_count && !(entry < data[i])) {
      return false;
    }
    if (is_leaf()) {
      ordered_insert(data, data_count, entry);
      return true;
    }
    if (!is_leaf() && i < data_count && !(entry < data[i])) {
      bool temp = subset[i + 1]->loose_insert(entry);
      if (subset[i + 1]->data_count > MAXIMUM) {
        fix_excess(i + 1);
      }
      return temp;
    }
    if (!is_leaf()) {
      bool temp = subset[i]->loose_insert(entry);
      if (subset[i]->data_count > MAXIMUM) {
        fix_excess(i);
      }
      return temp;
    }
    return false;
  }
  void fix_excess(std::size_t i) {
    BPlusTree *right = new BPlusTree();
    insert_item(subset, i + 1, child_count, right);
    split(subset[i]->subset, subset[i]->child_count, right->subset,
          right->child_count);
    split(subset[i]->data, subset[i]->data_count, right->data,
          right->data_count);
    Item entry;
    detach_item(subset[i]->data, subset[i]->data_count, entry);
    if (subset[i]->is_leaf()) {
      subset[i + 1]->next = subset[i]->next;
      subset[i]->next = right;
      ordered_insert(subset[i + 1]->data, subset[i + 1]->data_count, entry);
    }
    ordered_insert(data, data_count, entry);
  }
  // remove element functions
  bool loose_erase(const Item &target) {
    int i = first_ge(data, data_count, target);
    Item targ = target;
    if (is_leaf()) {
      if (i == data_count) {
        return false;
      }
      if (i < data_count && !(target < data[i])) {
        delete_item(data, i, data_count, targ);
        return true;
      }
    }
    if (!is_leaf() && (i == data_count || target < data[i])) {
      bool temp = subset[i]->loose_erase(target);
      if (subset[i]->data_count < MINIMUM) {
        fix_shortage(i);
      }
      return temp;
    }
    if (!is_leaf() && i < data_count && !(target < data[i])) {
      bool temp = subset[i + 1]->loose_erase(target);
      Iterator it = upper_bound(target);
      if (contains(target)) {
        delete_internal_node(i, target, *it);
      } else {
        Item hi;
        delete_item(data, i, data_count, hi);
      }
      return temp;
    }
    return false;
  }
  void fix_shortage(std::size_t i) {
    if (i > 0 && subset[i - 1]->data_count > MINIMUM) {
      transfer_from_left(i);
      return;
    }
    if (i < child_count - 1 && subset[i + 1]->data_count > MINIMUM) {
      transfer_from_right(i);
      return;
    }
    if (i > 0 && subset[i - 1]->data_count == MINIMUM) {
      Item temp;
      delete_item(data, i - 1, data_count, temp);
      merge_with_next_subset(i - 1);
      if (!subset[i - 1]->is_leaf()) {
        ordered_insert(subset[i - 1]->data, subset[i - 1]->data_count, temp);
      }
      return;
    }
    if (i < child_count - 1 && subset[i + 1]->data_count == MINIMUM) {
      Item temp;
      delete_item(data, i, data_count, temp);
      merge_with_next_subset(i);
      if (!subset[i]->is_leaf()) {
        ordered_insert(subset[i]->data, subset[i]->data_count, temp);
      }
      return;
    }
  }
  void delete_internal_node(std::size_t i, const Item &target,
                            const Item &next_smallest) {
    if (subset[i + 1]->data_count < MINIMUM) {
      fix_shortage(i + 1);
    }
    int j = first_ge(data, data_count, target);
    if (j < data_count && !(target < data[j])) {
      data[j] = next_smallest;
      return;
    }
    j = first_ge(subset[i]->data, subset[i]->data_count, target);
    if (j < subset[i]->data_count && !(target < subset[i]->data[j])) {
      subset[i]->data[j] = next_smallest;
      return;
    }
    j = first_ge(subset[i + 1]->data, subset[i + 1]->data_count, target);
    if (j < subset[i + 1]->data_count && !(target < subset[i + 1]->data[j])) {
      subset[i + 1]->data[j] = next_smallest;
      return;
    }
  }
  void transfer_from_left(std::size_t i) {
    Item transfer;
    if (subset[i]->is_leaf()) {
      detach_item(subset[i - 1]->data, subset[i - 1]->data_count, transfer);
      ordered_insert(subset[i]->data, subset[i]->data_count, transfer);
      data[i - 1] = transfer;
    }
    if (!subset[i]->is_leaf()) {
      delete_item(data, i - 1, data_count, transfer);
      ordered_insert(subset[i]->data, subset[i]->data_count, transfer);
      detach_item(subset[i - 1]->data, subset[i - 1]->data_count, transfer);
      ordered_insert(data, data_count, transfer);
      BPlusTree *transfer2;
      detach_item(subset[i - 1]->subset, subset[i - 1]->child_count, transfer2);
      insert_item(subset[i]->subset, 0, subset[i]->child_count, transfer2);
    }
  }
  void transfer_from_right(std::size_t i) {
    Item transfer;
    if (subset[i]->is_leaf()) {
      delete_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, transfer);
      attach_item(subset[i]->data, subset[i]->data_count, transfer);
      data[i] = subset[i + 1]->data[0];
      if (i > 0) {
        data[i - 1] = subset[i]->data[0];
      }
    }
    if (!subset[i]->is_leaf()) {
      delete_item(data, i, data_count, transfer);
      ordered_insert(subset[i]->data, subset[i]->data_count, transfer);
      delete_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, transfer);
      ordered_insert(data, data_count, transfer);
      BPlusTree *transfer2;
      delete_item(subset[i + 1]->subset, 0, subset[i + 1]->child_count,
                  transfer2);
      attach_item(subset[i]->subset, subset[i]->child_count, transfer2);
    }
  }
  void merge_with_next_subset(std::size_t i) {
    merge(subset[i]->data, subset[i]->data_count, subset[i + 1]->data,
          subset[i + 1]->data_count);
    merge(subset[i]->subset, subset[i]->child_count, subset[i + 1]->subset,
          subset[i + 1]->child_count);
    BPlusTree *entry;
    if (subset[i]->is_leaf()) {
      subset[i]->next = subset[i + 1]->next;
    }
    delete_item(subset, i + 1, child_count, entry);
  }
};

// Implementation ITERATOR MEMBER FUNCTIONS

// TODO

// Implementation BPlusTree MEMBER FUNCTIONS

template <class Item> bool BPlusTree<Item>::is_valid() const {
  bool valid = true;
  // check if the node is empty
  if (empty())
    return true;
  // check if the node has too many entries
  if (data_count > MAXIMUM || data_count < MINIMUM) {
    return false;
  }
  // check if the node has too many children
  if (child_count > MAXIMUM + 1 || child_count < 0) {
    return false;
  }
  // check if the data is sorted
  for (size_t i = 0; i < data_count - 1; i++) {
    if (data[i] > data[i + 1])
      return false;
  }
  if (!is_leaf()) {
    // check if the child_count is not equal to data_count+1
    if (child_count != data_count + 1) {
      return false;
    }
    // check if data is in range of children
    for (size_t i = 0; i < data_count; i++) {
      // check if data[i] is greater than subset[i]
      valid = is_gt(subset[i]->data, subset[i]->data_count, data[i]);
      if (!valid)
        return false;
      // check if data[i] is less than subset[i+1]
      valid = is_le(subset[i + 1]->data, subset[i + 1]->data_count, data[i]);
      if (!valid)
        return false;
      // check if subset[i] is valid
      valid = subset[i]->is_valid();
      if (!valid)
        return false;
      // check if data[i] is the smallest node in subset[i+1]
      valid = data[i] == subset[i + 1]->get_smallest_node()->data[0];
      if (!valid)
        return false;
    }
    // check if the last child is valid
    valid = subset[data_count]->is_valid();
    if (!valid)
      return false;
  }
  return true;
}

// TODO

#endif // BPLUSTREE_H
