#ifndef STACK_H
#define STACK_H

#include <iostream>


// The node class.
template<class T>
class StackNode
{
public:
	StackNode(const T data) {
		this->data = data;
		this->next = nullptr;
	}
	~StackNode() {
		this->next = nullptr;
	}
	T data;
	StackNode<T>* next;
};


// The stack class.
template<class T>
class Stack
{
public:
	Stack();
	Stack(const Stack<T>& other);
	Stack(const T array[], const unsigned SIZE);
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
	bool isNotEmpty() const;
	T pop();
	void push(const T element);
	unsigned size() const;
	T& top();
	T* toDynamicArray();
	T* toDynamicArray(const unsigned SIZE);
	std::string toString();
private:
	unsigned length;
	StackNode<T>* head;
};


#include "stack.cpp"

#endif
