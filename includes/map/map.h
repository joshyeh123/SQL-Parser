#ifndef MAP_H
#define MAP_H

#include <cstdlib> // Provides std::size_t

#include "bplustree.h"
#include "pair.h"

template <typename K, typename V> class Map {
public:
  // TYPEDEFS and MEMBER CONSTANTS
  typedef BPlusTree<Pair<K, V>> map_base;
  // NESTED CLASS DEFINITION
  class Iterator {
  public:
    friend class Map;
    // CONSTRUCTORS
    Iterator(typename map_base::Iterator it = nullptr) { _it = it; }
    // OPERATORS
    Iterator operator++(int unused) { return ++_it; }
    Iterator operator++() { return _it++; }
    Pair<K, V> operator*() { return *_it; }
    friend bool operator==(const Iterator &lhs, const Iterator &rhs) {
      return (lhs._it == rhs._it);
    }
    friend bool operator!=(const Iterator &lhs, const Iterator &rhs) {
      return !(lhs == rhs);
    }

  private:
    typename map_base::Iterator _it;
  };

  // CONSTRUCTORS
  Map() {}
  // ITERATORS
  Iterator begin() { return map.begin(); }
  Iterator end() { return map.end(); }
  // CAPACITY
  std::size_t size() { return map.size(); }
  std::size_t count() const { return map.count(); }
  bool empty() const { return map.empty(); }
  // ELEMENT ACCESS
  V &operator[](const K &key) {
    Pair<K, V> pair(key);
    map.insert(pair);
    return map.get(pair).value;
  }
  const V &operator[](const K &key) const {
    Pair<K, V> pair(key);
    map.insert(pair);
    return map.get(pair).value;
  }
  V &at(const K &key) {
    Pair<K, V> pair = Pair<K, V>(key);
    return map.get(pair).value;
  }
  const V &at(const K &key) const {
    Pair<K, V> pair = Pair<K, V>(key);
    return map.get(pair).value;
  }
  // MODIFIERS
  void insert(const K &k, const V &v) {
    Pair<K, V> pair = Pair<K, V>(k, v);
    if (!contains(pair)) {
      map.insert(pair);
    }
  }
  void erase(const K &key) {
    Pair<K, V> pair = Pair<K, V>(key);
    map.erase(pair);
  }
  void clear() { map.clear_tree(); }
  // OPERATIONS
  Iterator find(const K &key) {
    Pair<K, V> pair(key);
    return Iterator(map.find(pair));
  }
  bool contains(const Pair<K, V> &target) const { return map.contains(target); }
  V &get(const K &key) {
    Pair<K, V> pair(key);
    if (!contains(pair)) {
      insert(key, V());
    }
    return map.get(pair).value;
  }
  Iterator lower_bound(const K &key) { return Iterator(map.lower_bound(key)); }
  Iterator upper_bound(const K &key) { return Iterator(map.upper_bound(key)); }
  bool is_valid() { return map.is_valid(); }
  // OVERLOADED OPERATORS
  friend std::ostream &operator<<(std::ostream &outs,
                                  const Map<K, V> &print_me) {
    outs << print_me.map << std::endl;
    return outs;
  }

private:
  BPlusTree<Pair<K, V>> map;
};

#endif // MAP_H