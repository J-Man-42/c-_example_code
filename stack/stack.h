#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>


// The node class.
template<class T>
class Node
{
public:
	Node(const T data) {
		this->data = data;
		this->next = nullptr;
	}
	~Node() {
		this->next = nullptr;
	}
	T data;
	Node<T>* next;
};


// The stack class.
template<class T>
class Stack
{
public:
	Stack();
	Stack(const Stack<T>& other);
	Stack(const T array[], const uint SIZE);
	~Stack();

	template<class U>
	friend std::ostream& operator<<(
		std::ostream& out, Stack<U>& stack);

	Stack<T>& operator=(const Stack<T>& other);
	Stack<T> operator+(const T element);
	Stack<T> operator+(const Stack<T>& other);
	Stack<T>& operator+=(const T element);
	Stack<T>& operator+=(const Stack<T>& other);
	void clear();
	Stack<T> clone();
	bool contains(const T element) const;
	bool isEmpty() const;
	T pop();
	void push(const T element);
	uint size() const;
	T& top();
	T* toDynamicArray();
	T* toDynamicArray(const uint SIZE);
	std::string toString();
private:
	uint length;
	Node<T>* head;
};


#include "stack.cpp"

#endif
