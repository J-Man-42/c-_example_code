#ifndef QUEUE_H
#define QUEUE_H

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


// The queue class.
template<class T>
class Queue
{
public:
	Queue();
	Queue(const Queue<T>& other);
	Queue(const T array[], const uint SIZE);
	~Queue();

	template<class U>
	friend std::ostream& operator<<(
		std::ostream& out, Queue<U>& queue);

	Queue<T>& operator=(const Queue<T>& other);
	Queue<T> operator+(const T element);
	Queue<T> operator+(const Queue<T>& other);
	Queue<T>& operator+=(const T element);
	Queue<T>& operator+=(const Queue<T>& other);
	T& back();
	void clear();
	Queue<T> clone();
	bool contains(const T element) const;
	T& front();
	bool isEmpty() const;
	T pop();
	void push(const T element);
	uint size() const;
	T* toDynamicArray();
	T* toDynamicArray(const uint SIZE);
	std::string toString();
private:
	uint length;
	Node<T>* head;
	Node<T>* tail;
};


#include "queue.cpp"

#endif
