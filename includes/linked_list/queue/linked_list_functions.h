#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include <cassert>

#include "../../../includes/node/node.h"

using namespace std;

// Declaration
// Linked List General Functions:
template <typename T> void _print_list(node<T> *head);

// recursive fun! :)
template <typename T> void _print_list_backwards(node<T> *head);

// return ptr to key or NULL
template <typename T> node<T> *_search_list(node<T> *head, T key);

template <typename T> node<T> *_insert_head(node<T> *&head, T insert_this);

// insert after ptr
template <typename T>
node<T> *_insert_after(node<T> *&head, node<T> *after_this, T insert_this);

// insert before ptr
template <typename T>
node<T> *_insert_before(node<T> *&head, node<T> *before_this, T insert_this);

// ptr to previous node
template <typename T>
node<T> *_previous_node(node<T> *head, node<T> *prev_to_this);

// delete, return item
template <typename T> T _delete_node(node<T> *&head, node<T> *delete_this);

// duplicate the list
template <typename T> node<T> *_copy_list(node<T> *head);

// duplicate list and return the last node of the copy
template <typename T> node<T> *_copy_list(node<T> *&dest, node<T> *src);

// delete all the nodes
template <typename T> void _clear_list(node<T> *&head);

//_item at this position
template <typename T> T &_at(node<T> *head, int pos);

// Last node in the list, never use this function.
template <typename T> node<T> *_last_node(node<T> *head);

// Definition
template <typename T> void _print_list(node<T> *head) {
  node<T> *walker = head;
  while (walker != nullptr) {
    std::cout << *(walker->_item) << "->";
    walker = walker->_next;
  }
  std::cout << "|||" << endl;
}

// recursive fun! :)
template <typename T> void _print_list_backwards(node<T> *head) {
  if (head == nullptr) {
    return;
  }
  _print_list_backwards(head->_next);
  std::cout << head->_item << " ";
}

// return ptr to key or NULL
template <typename T> node<T> *_search_list(node<T> *head, T key) {
  node<T> *walker = head;
  while (walker != nullptr) {
    if (walker->_item == key) {
      return walker;
    }
    walker = walker->_next;
  }
  return nullptr;
}

template <typename T> node<T> *_insert_head(node<T> *&head, T insert_this) {
  if (head != nullptr) {
    node<T> *newHead = new node<T>(insert_this, head);
    newHead->_prev = nullptr;
    head->_prev = newHead;
    head = newHead;
  } else {
    node<T> *newHead = new node<T>(insert_this, nullptr);
    newHead->_prev = nullptr;
    head = newHead;
  }
  return head;
}

// insert after ptr
template <typename T>
node<T> *_insert_after(node<T> *&head, node<T> *after_this, T insert_this) {
  node<T> *newNode = new node<T>(insert_this, after_this->_next);
  newNode->_prev = after_this;
  if (after_this->_next != nullptr) {
    after_this->_next->_prev = newNode;
  }
  after_this->_next = newNode;
  return newNode;
}

// insert before ptr
template <typename T>
node<T> *_insert_before(node<T> *&head, node<T> *before_this, T insert_this) {
  node<T> *newNode = new node<T>(insert_this, before_this);
  newNode->_prev = before_this->_prev;
  if (before_this == head) {
    newNode->_prev = nullptr;
    head = newNode;
  } else {
    before_this->_prev->_next = newNode;
  }
  before_this->_prev = newNode;
  return newNode;
}

// ptr to previous node
template <typename T>
node<T> *_previous_node(node<T> *head, node<T> *prev_to_this) {
  return prev_to_this->_prev;
}

// delete, return item
template <typename T> T _delete_node(node<T> *&head, node<T> *delete_this) {
  T item = delete_this->_item;
  if (delete_this->_prev == nullptr) {
    head = delete_this->_next;
    delete_this->_next->_prev = nullptr;
  }
  if (delete_this->_next == nullptr) {
    delete_this->_prev->_next = nullptr;
  }
  if (delete_this->_prev != nullptr && delete_this->_next != nullptr) {
    delete_this->_prev->_next = delete_this->_next;
    delete_this->_next->_prev = delete_this->_prev;
  }
  delete delete_this;
  return item;
}
// duplicate the list
template <typename T> node<T> *_copy_list(node<T> *head) {
  if (head == nullptr) {
    return nullptr;
  }
  node<T> *temp = head;
  node<T> *newHead = new node<T>(temp->_item, nullptr);
  node<T> *prev_ptr = newHead;
  newHead->_prev = nullptr;
  temp = temp->_next;
  while (temp != nullptr) {
    node<T> *newNode = new node<T>(temp->_item, nullptr);
    prev_ptr->_next = newNode;
    newNode->_prev = prev_ptr;
    prev_ptr = newNode;
    temp = temp->_next;
  }
  return newHead;
}

// duplicate list and return the last node of the copy
template <typename T> node<T> *_copy_list(node<T> *&dest, node<T> *src) {
  node<T> *temp = src;
  dest = new node<T>(temp->_item, temp->_next);
  dest->_prev = temp->_prev;
  temp = temp->_next;
  while (temp->_next != nullptr) {
    node<T> *newNode = new node<T>(temp->_item, temp->_next);
    newNode->_prev = temp->_prev;
    temp = temp->_next;
  }
  return temp;
}
// delete all the nodes
template <typename T> void _clear_list(node<T> *&head) {
  node<T> *temp = head;
  while (temp != nullptr) {
    node<T> *next = temp->_next;
    delete temp;
    temp = next;
  }
  head = nullptr;
}

//_item at this position
template <typename T> T &_at(node<T> *head, int pos) {
  node<T> *temp = head;
  int counter = 1;
  while (temp != nullptr) {
    if (counter == pos) {
      break;
    }
    counter++;
    temp = temp->_next;
  }
  return temp->_item;
}

// Last node in the list, never use this function.
template <typename T> node<T> *_last_node(node<T> *head) {
  node<T> *temp = head;
  while (temp->_next != nullptr) {
    temp = temp->_next;
  }
  return temp;
}
#endif // LINKED_LIST_FUNCTIONS_H