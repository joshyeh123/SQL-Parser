#ifndef MYSTACK_H
#define MYSTACK_H

#include <iomanip>
#include <iostream>

#include "linked_list_functions.h"

using namespace std;

template <typename T> class Stack {
public:
  class Iterator {
  public:
    // Give access to list to access _ptr
    friend class Stack;

    // Default CTOR
    Iterator() {}
    // Point Iterator to where p is pointing to
    Iterator(node<T> *p) { _ptr = p; }

    // Casting operator: true if _ptr not NULL
    // This turned out to be a pain!
    operator bool() {
      if (_ptr == nullptr) {
        return false;
      }
      return true;
    }

    // dereference operator
    T &operator*() { return _ptr->_item; }
    // member access operator
    T *operator->() { return *_ptr; }
    // true if _ptr is NULL
    bool is_null() {
      if (_ptr == nullptr) {
        return true;
      }
      return false;
    }

    // true if left != right
    friend bool operator!=(const Iterator &left, const Iterator &right) {
      if (left._ptr == right._ptr) {
        return false;
      }
      return true;
    }
    // true if left == right
    friend bool operator==(const Iterator &left, const Iterator &right) {
      if (left._ptr == right._ptr) {
        return true;
      }
      return false;
    }

    // member operator:  ++it; or ++it = new_value
    Iterator &operator++() {
      this = this->_ptr->_next;
      return this;
    }
    // friend operator: it++
    friend Iterator operator++(Iterator &it, int unused) {
      Iterator oldIt = it;
      it = it._ptr->_next;
      return oldIt;
    }

  private:
    node<T> *_ptr; // pointer being encapsulated
  };

  // constructor: CTOR
  Stack();

  // BIG 3:
  Stack(const Stack<T> &copyMe);
  ~Stack();
  Stack<T> &operator=(const Stack<T> &RHS);

  // Operations:
  void push(T item);
  void pop();

  // Accessors:
  Iterator begin() const {
    Iterator *head = new Iterator(_top);
    return *head;
  }                                        // Iterator to the head node
  Iterator end() const { return nullptr; } // Iterator to NULL

  // Checkers:
  int size() const;
  bool empty();
  T top();

  // template <typename U>
  // friend ostream &operator<<(ostream &outs, const Stack<U> &printMe) {
  //   _print_list(printMe._top);
  //   return outs;
  // }

private:
  node<T> *_top;
  int _size;
};

// Definition
template <class T> Stack<T>::Stack() { _top = nullptr; };

template <class T> Stack<T>::Stack(const Stack<T> &copyMe) {
  _size = copyMe._size;
  _top = _copy_list(copyMe._top);
}
template <class T> Stack<T>::~Stack() { _clear_list(_top); }
template <class T> Stack<T> &Stack<T>::operator=(const Stack<T> &RHS) {
  _size = RHS._size;
  _top = _copy_list(RHS._top);
  return *this;
}

// Operations:
template <class T> void Stack<T>::push(T item) { _insert_head(_top, item); }
template <class T> void Stack<T>::pop() {
  node<T> *temp = _top;
  _top = _top->_next;
  delete temp;
}

template <class T> int Stack<T>::size() const {
  int counter = 0;
  node<T> *walker = _top;
  while (walker != nullptr) {
    walker = walker->_next;
    counter++;
  }
  return counter;
}

template <class T> bool Stack<T>::empty() {
  if (_top == nullptr) {
    return true;
  }
  return false;
}
template <class T> T Stack<T>::top() { return _top->_item; }

#endif // MYSTACK_H