#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iomanip>
#include <iostream>

#include "linked_list_functions.h"

using namespace std;

template <typename T> class Queue {
public:
  class Iterator {
  public:
    // Give access to list to access _ptr
    friend class Queue;

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
      _ptr = _ptr->_next;
      Iterator *it = new Iterator(_ptr);
      return *it;
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
  Queue();

  // BIG 3:
  Queue(const Queue<T> &copyMe);
  ~Queue();
  Queue<T> &operator=(const Queue<T> &RHS);

  // Operations:
  void push(T item); // Enqueue
  void pop();        // Dequeue

  // Accessors:
  Iterator begin() const {
    Iterator *head = new Iterator(_front);
    return *head;
  }                                        // Iterator to the head node
  Iterator end() const { return nullptr; } // Iterator to NULL

  // Checkers:
  int size() const;
  bool empty();
  bool empty() const {
    if (_front == nullptr) {
      return true;
    }
    return false;
  }
  T front();
  T back();
  node<T> *fron() { return _front; }
  void clear_list() { _clear_list(_front); }
  // template <typename U>
  // friend ostream &operator<<(ostream &outs, const Queue<U> &printMe);

private:
  node<T> *_front;
  node<T> *_rear;
  int _size;
};
// Definition

// constructor: CTOR
template <class T> Queue<T>::Queue() {
  _front = nullptr;
  _rear = nullptr;
  _size = 0;
};

// BIG 3:
template <class T> Queue<T>::Queue(const Queue<T> &copyMe) {
  // if (copyMe._size == 0) {
  //   _size = 0;
  //   _front = nullptr;
  //   _rear = nullptr;
  //   return;
  // }
  _size = copyMe._size;
  _front = _copy_list(copyMe._front);
  _rear = _last_node(_front);
}
template <class T> Queue<T>::~Queue() { _clear_list(_front); }
template <class T> Queue<T> &Queue<T>::operator=(const Queue<T> &RHS) {
  if (RHS.begin() == nullptr) {
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
  } else {
    _size = RHS._size;
    _front = _copy_list(RHS._front);
    _rear = _last_node(_front);
  }
  return *this;
}

// Operations:
template <class T> void Queue<T>::push(T item) {
  if (_front == nullptr) {
    _front = _insert_head(_front, item);
    _rear = _front;
  } else {
    _rear = _insert_after(_front, _rear, item);
  }
}
template <class T> void Queue<T>::pop() {
  node<T> *temp = _front;
  _front = _front->_next;
  delete temp;
}

// Checkers:
template <class T> int Queue<T>::size() const {
  int counter = 0;
  node<T> *walker = _front;
  while (walker != nullptr) {
    walker = walker->_next;
    counter++;
  }
  return counter;
}
template <class T> bool Queue<T>::empty() {
  if (_front == nullptr) {
    return true;
  }
  return false;
}
template <class T> T Queue<T>::front() { return _front->_item; }
template <class T> T Queue<T>::back() { return _rear->_item; }

#endif // MYQUEUE_H