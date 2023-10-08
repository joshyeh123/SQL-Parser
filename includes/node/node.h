#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <typename T> struct node {
public:
  node(const T &item = T(), node *next = nullptr);
  // template <typename U>
  // friend ostream &operator<<(ostream &outs, const node<U> &printMe) {
  //   cout << printMe._item;
  //   return outs;
  // }

  T _item;
  node *_next;
  node *_prev;
};

// Definition
template <typename T> node<T>::node(const T &item, node *next) {
  _item = item;
  _next = next;
}

#endif // NODE_H