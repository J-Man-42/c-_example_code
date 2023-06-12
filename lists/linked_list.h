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
	void add(const T element);
	void clear();
	void insert(const uint index, const T element);
	void print();
	T remove(const T element);
	T removeAt(const uint index);
	uint size() const;
	T* toDynamicArray();
	T* toDynamicArray(const uint SIZE);
private:
	uint length;
	Node<T>* head;
	Node<T>* tail;
};


#endif