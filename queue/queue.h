#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>


// The node class.
template<class T>
class QueueNode
{
public:
	QueueNode(const T data) {
		this->data = data;
		this->next = nullptr;
	}
	~QueueNode() {
		this->next = nullptr;
	}
	T data;
	QueueNode<T>* next;
};


// The queue class.
template<class T>
class Queue
{
public:
	Queue();
	Queue(const Queue<T>& other);
	Queue(const T array[], const unsigned SIZE);
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
	bool isNotEmpty() const;
	T pop();
	void push(const T element);
	unsigned size() const;
	T* toDynamicArray();
	T* toDynamicArray(const unsigned SIZE);
	std::string toString();
private:
	unsigned length;
	QueueNode<T>* head;
	QueueNode<T>* tail;
};


#include "queue.cpp"

#endif
