#ifndef BTREE_ARRAY_FUNCTIONS_H
#define BTREE_ARRAY_FUNCTIONS_H

#include <cassert>  // Provides assert
#include <cstdlib>  // Provides size_t
#include <iomanip>  // Provides std::setw
#include <iostream> // Provides std::cout
#include <vector>
// Declaration

template <class T> void swap(T &a, T &b) { // swap the two items
  T temp = a;
  a = b;
  b = temp;
}

template <class T>
T maximal(const T &a, const T &b) { // return the larger of the two items
  if (a > b) {
    return a;
  }
  return b;
}
template <class T>
std::size_t index_of_maximal(
    T data[],
    std::size_t n) { // return index of the largest item in data with length n
  int max = 0;
  for (int i = 1; i < n; i++) {
    if (data[max] < data[i]) {
      max = i;
    }
  }
  return max;
}
template <class T>
std::size_t first_ge(
    const T data[], std::size_t n,
    const T &entry) { // return the first index such that data[i] is not less
                      // than the entry if there is no such index, then return n
                      // indicating all of data are less than the entry.
  for (int i = 0; i < n; i++) {
    if (!(data[i] < entry)) {
      return i;
    }
  }
  return n;
}
template <class T>
void insert_item(T data[], std::size_t i, std::size_t &n,
                 T entry) { // insert entry at index i in data
  for (int j = n; j > i; j--) {
    data[j] = data[j - 1];
  }
  data[i] = entry;
  n++;
}
template <class T>
void ordered_insert(
    T data[], std::size_t &n,
    T entry) { // insert entry into the sorted array data with length n
  int index = -1;
  for (int i = 0; i < n; i++) {
    if (entry < data[i]) {
      index = i;
      break;
    }
  }
  if (index == -1) {
    index = n;
  }
  for (int i = n; i > index; i--) {
    data[i] = data[i - 1];
  }
  data[index] = entry;
  n++;
}
template <class T>
void attach_item(T data[], std::size_t &n,
                 const T &entry) { // append entry to the right of data
  data[n] = entry;
  n++;
}
template <class T>
void delete_item(T data[], std::size_t i, std::size_t &n,
                 T &entry) { // delete item at index i and place it in entry
  entry = data[i];
  for (int j = i; j < n - 1; j++) {
    data[j] = data[j + 1];
  }
  n--;
}
template <class T>
void detach_item(
    T data[], std::size_t &n,
    T &entry) { // remove the last element in data and place it in entry
  n--;
  entry = data[n];
}
template <class T>
void merge(
    T data1[], std::size_t &n1, T data2[],
    std::size_t &n2) { // append data2 to the right of data1 and set n2 to 0
  for (int i = 0; i < n2; i++) {
    data1[n1 + i] = data2[i];
  }
  n1 += n2;
  n2 = 0;
}
template <class T>
void split(T data1[], std::size_t &n1, T data2[],
           std::size_t &n2) { // move n/2 elements from the right of data1 to
                              // beginning of data2
  int n = n1 / 2;
  for (int i = 0; i < n; i++) {
    data2[i] = data1[n1 - n + i];
  }
  n1 -= n;
  n2 = n;
}
template <class T>
void copy_array(
    T dest[], const T src[], std::size_t &dest_size,
    std::size_t src_size) { // copy all entries from src[] to replace dest[]
  for (int i = 0; i < src_size; i++) {
    dest[i] = src[i];
  }
  dest_size = src_size;
}
template <class T>
bool is_le(const T data[], std::size_t n,
           const T &item) { // return true if item <= all data[i], otherwise
                            // return false
  for (int i = 0; i < n; i++) {
    if (item > data[i]) {
      return false;
    }
  }
  return true;
}
template <class T>
bool is_gt(const T data[], std::size_t n,
           const T &item) { // return true if item > all data[i], otherwise
                            // return false
  for (int i = 0; i < n; i++) {
    if (item <= data[i]) {
      return false;
    }
  }
  return true;
}
template <class T>
void print_array(const T data[], std::size_t n,
                 std::size_t pos = 0) { // print array data
  for (int i = pos; i < n - 1; i++) {
    std::cout << data[i] << ", ";
  }
  std::cout << data[n - 1];
  std::cout << std::endl;
}

template <typename T>
std::vector<T> &operator+=(std::vector<T> &list, const T &addme) {
  list.push_back(addme);
  return list;
}

template <typename T>
std::ostream &operator<<(std::ostream &outs, const std::vector<T> &print_me) {
  for (int i = 0; i < print_me.size(); i++) {
    std::cout << print_me[i];
    if (i != print_me.size() - 1) {
      std::cout << " ";
    }
  }
  return outs;
}
// Definition

// TODO

#endif // BTREE_ARRAY_FUNCTIONS_H