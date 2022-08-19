#ifndef NODE_H
#define NODE_H

#include <iostream>

template<class T>
class LinkedList;

template<class T> class Node {
  // we we access to the linked list members
  friend class LinkedList<T>;

public:
  Node();
  Node(T);
  T getData();
  Node<T> *getNext() {return next;}

  Node<T> *getPrev() {return prev;}

  friend std::ostream &operator<<(std::ostream &out, const Node<T> &node) {
    out << node.data;
    return out;
  }

private:
  T data;
  Node<T> *next;
  Node<T> *prev;
  
};

template <class T> Node<T>::Node() {
  data = 0;
  next = 0;
  prev = 0;
}

template <class T> Node<T>::Node(T node) {
  data = node;
  next = 0;
  prev = 0;
}

template <class T> T Node<T>::getData() { return data; }


#endif
