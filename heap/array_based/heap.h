#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include "../../display_structure/display_structure.h"


// The heap class.
template<class T>
class Heap
{
public:
	Heap(const bool maxHeap = true);
	Heap(const Heap<T>& other);
	~Heap();

	Heap<T>& operator=(const Heap<T>& other);
	Heap<T> operator+(const T element);
	Heap<T>& operator+=(const T element);
	Heap<T>& operator--();
	Heap<T> operator--(int);

	void bft();
	void clear();
	Heap<T> clone();
	bool contains(const T element) const;
	void dft();
	void display();
	unsigned height() const;
	bool isEmpty() const;
	bool isMaxHeap() const;
	bool isMinHeap() const;
	bool isNotEmpty() const;
	void push(const T element);
	T pop();
	unsigned size() const;
	void toggleMaxMin();

private:
	// bool compare(const T left, const T right) const;
	// bool contains(HeapNode<T>* node, const T& element) const;
	// void clear(HeapNode<T>* node);
	// void clone(HeapNode<T>* thisNode, HeapNode<T>* otherNode);
	// void dft(HeapNode<T>* node);
	// void heapify(HeapNode<T>* node);
	// void updateHeight(HeapNode<T>* node);

	unsigned numElements;
	unsigned capacity;
	bool maxHeap;
};


#include "heap.cpp"

#endif
