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
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
		this->next = nullptr;
		this->prev = nullptr;
	}
	HeapNode(const T data) {
		this->data = data;
		this->height = 1;
		this->colour = '\0';
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
		this->next = nullptr;
		this->prev = nullptr;
	}
	HeapNode(HeapNode* other) {
		this->data = other->data;
		this->height = other->height;
		this->colour = other->colour;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
		this->next = nullptr;
		this->prev = nullptr;
	}
	~HeapNode() {
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
		this->next = nullptr;
		this->prev = nullptr;
	}
	T data;
	unsigned height;
	char colour;
	HeapNode<T>* parent;
	HeapNode<T>* left;
	HeapNode<T>* right;
	HeapNode<T>* next;
	HeapNode<T>* prev;
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
	void clear(HeapNode<T>* node);
	void clone(HeapNode<T>* thisNode, HeapNode<T>* otherNode);
	bool contains(HeapNode<T>* node, const T& element) const;
	void dft(HeapNode<T>* node);
	void updateHeight(HeapNode<T>* node);
	
	HeapNode<T>* root;
	HeapNode<T>* leftmost;
	unsigned numElements;
};


#include "heap.cpp"

#endif
