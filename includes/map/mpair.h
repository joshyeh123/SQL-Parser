#ifndef MPAIR_H
#define MPAIR_H

#include <cstdlib> // Provides std::size_t
#include <vector>  // Provides std::vector

template <typename K, typename V> struct MPair {
  K key;
  std::vector<V> value_list;

  //--------------------------------------------------------------------------------
  /*      MPair CTORs:
   *  must have these CTORs:
   *  - default CTOR / CTOR with a key and no value: this will create an empty
   * vector
   *  - CTOR with a key AND a value: pushes the value into the value_list
   *  - CTOR with a key and a vector of values (to replace value_list)
   */
  //--------------------------------------------------------------------------------
  MPair(const K &k = K()) { key = k; }
  MPair(const K &k, const V &v) {
    key = k;
    value_list.push_back(v);
  }
  MPair(const K &k, const std::vector<V> &vlist) {
    key = k;
    for (int i = 0; i < vlist.size(); i++) {
      value_list.push_back(vlist[i]);
    }
  }
  //--------------------------------------------------------------------------------

  // Overloaded operators
  friend std::ostream &operator<<(std::ostream &outs,
                                  const MPair<K, V> &print_me) {
    std::cout << print_me.key << " : [";
    for (int i = 0; i < print_me.value_list.size(); i++) {
      std::cout << print_me.value_list[i];
      if (i != print_me.value_list.size() - 1) {
        std::cout << " ";
      }
    }
    std::cout << "]";
    return outs;
  }
  friend bool operator==(const MPair<K, V> &lhs, const MPair<K, V> &rhs) {
    if (lhs.key == rhs.key) {
      return true;
    }
    return false;
  }
  friend bool operator<(const MPair<K, V> &lhs, const MPair<K, V> &rhs) {
    return lhs.key < rhs.key;
  }
  friend bool operator>(const MPair<K, V> &lhs, const MPair<K, V> &rhs) {
    if (lhs.key > rhs.key) {
      return true;
    }
    return false;
  }
  friend bool operator<=(const MPair<K, V> &lhs, const MPair<K, V> &rhs) {
    if (!(lhs.key > rhs.key)) {
      return true;
    }
    return false;
  }
  friend MPair<K, V> operator+(const MPair<K, V> &lhs, const MPair<K, V> &rhs) {
    return lhs.key + rhs.key;
    ;
  }
};

#endif // MPAIR_H