#ifndef NODE_H
#define NODE_H


// The Node class.
template <class T>
class Node
{
public:
	Node(const T data);
	~Node();

	T data;
	Node<T>* next;
	Node<T>* prev;
	
};

#include "node.cpp"

#endif