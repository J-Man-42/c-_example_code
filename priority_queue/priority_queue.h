#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

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


// The priority queue class.
template<class T>
class PriorityQueue
{
public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue<T>& other);
	PriorityQueue(const T array[], const uint SIZE);
	~PriorityQueue();

	template<class U>
	friend std::ostream& operator<<(
		std::ostream& out, PriorityQueue<U>& queue);

	PriorityQueue<T>& operator=(const PriorityQueue<T>& other);
	PriorityQueue<T> operator+(const T element);
	PriorityQueue<T> operator+(const PriorityQueue<T>& other);
	PriorityQueue<T>& operator+=(const T element);
	PriorityQueue<T>& operator+=(const PriorityQueue<T>& other);
	T& back();
	void clear();
	PriorityQueue<T> clone();
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


#include "priority_queue.cpp"

#endif
