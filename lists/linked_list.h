#ifndef LINKED_LIST_H
#define LINKED_LIST_H


#include <iostream>


// The Node struct.
template<class T>
struct Node
{
	T data;
	Node* next = nullptr;
	Node* prev = nullptr;
};


// The doubly linked list class.
template<class T>
class LinkedList
{
public:
	LinkedList();
	LinkedList(const LinkedList<T>& other);
	~LinkedList();
	void add(T element);
	void clear();
	void insert(uint index, T element);
	uint size() const;
private:
	uint length;
	Node<T>* head;
	Node<T>* tail;
};


#endif