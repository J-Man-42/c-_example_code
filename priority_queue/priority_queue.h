#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>


// The node class.
template<class T>
class PQueueNode
{
public:
	PQueueNode(const T data) {
		this->data = data;
		this->next = nullptr;
	}
	~PQueueNode() {
		this->next = nullptr;
	}
	T data;
	PQueueNode<T>* next;
};


// The priority queue class.
template<class T>
class PriorityQueue
{
public:
	PriorityQueue(const bool maxPriority = true);
	PriorityQueue(const PriorityQueue<T>& other);
	PriorityQueue(
		const T array[], const unsigned SIZE, const bool maxPriority = true);
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
	bool isMaxPriority() const;
	bool isMinPriority() const;
	bool isNotEmpty() const;
	T pop();
	void push(const T element);
	unsigned size() const;
	T* toDynamicArray();
	T* toDynamicArray(const unsigned SIZE);
	std::string toString();
private:
	bool compare(const T left, const T right) const;
	bool maxPriority;
	unsigned length;
	PQueueNode<T>* head;
	PQueueNode<T>* tail;
};


#include "priority_queue.cpp"

#endif
