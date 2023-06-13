#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"

// The doubly linked list class.
template<class T>
class LinkedList
{
public:
	LinkedList();
	LinkedList(const LinkedList<T>& other);
	~LinkedList();
	T& operator[](const uint index);
	void add(const T element);
	void clear();
	T& get(const uint index);
	void insert(const uint index, const T element);
	void print();
	void remove(const T element);
	T& removeAt(const uint index);
	void set(const uint index, const T element);
	uint size() const;
	LinkedList<T>* subList(const uint start, const uint end);
	T* toDynamicArray();
	T* toDynamicArray(const uint SIZE);
private:
	Node<T>* findIndex(const uint index);
	uint length;
	Node<T>* head;
	Node<T>* tail;
};

#include "linked_list.cpp"

#endif