#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"
#include <algorithm>
#include <codecvt>
#include <iostream>
#include <iterator>
#include <ostream>

template <class T> class LinkedList {
public:
  LinkedList();
  ~LinkedList();

  void addAtFront(T node);
  void addAtBack(T node);
  void addAfterNode(T oldNode, T nodeToInsert);
  void removeNode(T node);
  
  void printList();
  int size();


  friend std::ostream &operator<< (std::ostream &out, const LinkedList<T> &obj) {
    Node<T> *tmp = obj.head;
    while (tmp != nullptr) {
      out << *tmp->getData() << std::endl;
      tmp = tmp->getNext();
    }
    // std::cout << std::endl;
    return out;
  }

private:
  Node<T> *head;
  
};


template <class T> LinkedList<T>::LinkedList() : head(0) {
  
}

template <class T> LinkedList<T>::~LinkedList() {
  Node<T> *node = head, *tmpNode;

  while (node != nullptr) {
    tmpNode = node;
    node = node->next;
    delete tmpNode;
  }
}

template <class T> void LinkedList<T>::addAtFront(T node) {
  Node<T> *newNode = new Node<T>();
  newNode->data = node;

  if (head == nullptr) {
    head = newNode;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return;
  }

  newNode->next = head;
  head->prev = newNode;
  head = newNode;
}


template <class T> void LinkedList<T>::addAtBack(T node) {
  Node<T> *newNode = new Node<T>();
  newNode->data = node;
  if (head == nullptr) {
    head = newNode;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return;
  }

  Node<T> *tmpNode = head;
  while (tmpNode->next != nullptr) {
    tmpNode = tmpNode->next;
  }

  tmpNode->next = newNode;
  newNode->prev = tmpNode;
}
// fixme: this block has segfault 
#if 0
template <class T> void LinkedList<T>::addAfterNode(T oldNode, T nodeToInsert) {
  Node<T> *newNode = new Node<T>();
  newNode->data = nodeToInsert;

  Node<T> *oNode = new Node<T>();
  oNode->data = oldNode;

  if (head == nullptr) {
    head = newNode;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return;
  } else {
    Node<T> *tmpNode = head, *tmpNode2;
    while (tmpNode->data == oNode->data){
      if(tmpNode->next == nullptr) {
	std::cout << "Node not found in the list" << std::endl;
	break;
      } else {
	tmpNode = tmpNode->next;
      }
    }

    tmpNode2 = tmpNode->next;
    tmpNode->next = newNode;
    newNode->prev = tmpNode;
    newNode->next = tmpNode2;
    tmpNode2->prev = newNode;
  } 
    
}
#endif

template <class T> void LinkedList<T>::removeNode(T node) {
  Node<T> *tmpNode, *tmpNode2;
  if (head == nullptr) {   
    std::cout << "List is empty" << std::endl;    
    return;
  } else if (head->data == node) {
    tmpNode = head;
    if (head->next != nullptr) {
      head = head->next;
      head->prev = nullptr;
      delete tmpNode;
      tmpNode = nullptr;
    } else {
      delete head;
      head = nullptr;      
      delete tmpNode;
      tmpNode = nullptr;
      return;
    }
  }
  // a node in between two nodes
  tmpNode2 = head;
  while (tmpNode2->next->next != nullptr) {
    if (tmpNode2->next->data == node) {
      tmpNode = tmpNode2->next;
      tmpNode2->next = tmpNode->next;
      tmpNode->next->prev = tmpNode2;
      delete tmpNode;
      tmpNode = nullptr;
      return;
    }
    tmpNode2 = tmpNode2->next;
  }


  // what if we have the last element in the lest
  if (tmpNode2->next->data == node) {
    tmpNode = tmpNode2->next;
    delete tmpNode;
    tmpNode = nullptr;
    tmpNode2->next = nullptr;
    return;     
  }

  // if none of that is the case
  std::cout << "Element not found" << std::endl;      
}

template <class T> void LinkedList<T>::printList() {
  Node<T> *tmp = head;
  if (tmp == nullptr) {
    std::cout << "List is empty" << std::endl;
    return;
  }

  if (tmp->next == nullptr) {
    std::cout << tmp->data << std::endl;
    return;
  } else {
    while (tmp != nullptr) {
      std::cout << tmp->data << std::endl;
      tmp = tmp->next;
    }
  }
}

template <class T> int LinkedList<T>::size() {
  if (head == nullptr) return 0;

  Node<T> *tmp = head;
  int nodeCounter = 0;
  while (tmp != nullptr) {
    nodeCounter++;
    tmp = tmp->next;      
  }

  return nodeCounter;
}

#endif
