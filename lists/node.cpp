#include "node.h"


// The constructor.
template <class T>
Node<T>::Node(const T data) {
	this->data = data;
	this->next = nullptr;
	this->prev = nullptr;
}


// The destructor.
template <class T>
Node<T>::~Node() {
	this->next = nullptr;
	this->prev = nullptr;
}