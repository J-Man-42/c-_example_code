#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include "../display_structure/display_structure.h"


// The node class.
template<class T>
class HeapNode
{
public:
	HeapNode() {
		this->data = NULL;
		this->height = 0;
		this->colour = '\0';
		this->left = nullptr;
		this->right = nullptr;
		this->previous = nullptr;
	}
	HeapNode(const T data) {
		this->data = data;
		this->height = 1;
		this->colour = '\0';
		this->left = nullptr;
		this->right = nullptr;
		this->previous = nullptr;
	}
	HeapNode(HeapNode* other) {
		this->data = other->data;
		this->height = other->height;
		this->colour = other->colour;
		this->left = nullptr;
		this->right = nullptr;
		this->previous = nullptr;
	}
	~HeapNode() {
		this->left = nullptr;
		this->right = nullptr;
		this->previous = nullptr;
	}
	T data;
	unsigned height;
	char colour;
	HeapNode<T>* left;
	HeapNode<T>* right;
	HeapNode<T>* previous;
};


// The binary search tree class.
template<class T>
class Heap
{
public:
	Heap();
	Heap(const Heap<T>& other);
	~Heap();

	Heap<T>& operator=(const Heap<T>& other);
	Heap<T> operator+(const T element);
	Heap<T>& operator+=(const T element);
	Heap<T> operator-(const T element);
	Heap<T>& operator-=(const T element);

	void bft();
	void clear();
	Heap<T> clone();
	bool contains(const T element) const;
	void dft();
	void display();
	unsigned height() const;
	bool isEmpty() const;
	bool isNotEmpty() const;
	void push(const T element);
	T pop();
	unsigned size() const;

private:
	void calibrateHeights(HeapNode<T>* node);
	void clear(HeapNode<T>* node);
	void clone(HeapNode<T>* thisNode, HeapNode<T>* otherNode);
	bool contains(HeapNode<T>* node, const T& element) const;
	void dft(HeapNode<T>* node);
	void insert(HeapNode<T>* node, const T& element);
	void linkParent(
		HeapNode<T>* parent, HeapNode<T>* node,
		HeapNode<T>* child = nullptr);
	void updateHeight(HeapNode<T>* node);
	
	HeapNode<T>* root;
	unsigned numElements;
};


#include "heap.cpp"

#endif
