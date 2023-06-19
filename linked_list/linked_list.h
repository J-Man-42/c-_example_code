#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "node.h"

// The doubly linked list class.
template<class T>
class LinkedList
{
public:
	LinkedList();
	LinkedList(const LinkedList<T>& other);
	LinkedList(const T array[], const uint SIZE);
	~LinkedList();

	template<class U>
	friend std::ostream& operator<<(
		std::ostream& out, LinkedList<U>& list);
	
	LinkedList<T>& operator=(const LinkedList<T>& other);
	T& operator[](const uint index);
	LinkedList<T> operator+(const T element);
	LinkedList<T> operator+(const LinkedList<T>& other);
	LinkedList<T>& operator+=(const T element);
	LinkedList<T>& operator+=(const LinkedList<T>& other);
	void add(const T element);
	void clear();
	LinkedList<T> clone();
	T& get(const uint index);
	T& getFirst();
	T& getLast();
	T& getNext();
	int indexOf(const T element);
	void insert(const uint index, const T element);
	bool isEmpty() const;
	void remove(const T element);
	T removeAt(const uint index);
	void resetNext();
	void set(const uint index, const T element);
	void setFirst(const T element);
	void setLast(const T element);
	uint size() const;
	LinkedList<T>* subList(const uint start, const uint end);
	T* toDynamicArray();
	T* toDynamicArray(const uint SIZE);
	std::string toString();
private:
	Node<T>* findIndex(const uint index);
	uint length;
	Node<T>* head;
	Node<T>* tail;
	Node<T>* current;
};

#include "linked_list.cpp"

#endif