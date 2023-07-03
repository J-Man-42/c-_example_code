#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include "../display_structure/display_structure.h"


// The node class.
template<class T>
class BSTNode
{
public:
	BSTNode() {
		this->data = NULL;
		this->height = 0;
		this->left = nullptr;
		this->right = nullptr;
	}
	BSTNode(const T data) {
		this->data = data;
		this->height = 1;
		this->left = nullptr;
		this->right = nullptr;
	}
	BSTNode(BSTNode* other) {
		this->data = other->data;
		this->height = other->height;
		this->left = nullptr;
		this->right = nullptr;
	}
	~BSTNode() {
		this->left = nullptr;
		this->right = nullptr;
	}
	T data;
	int height;
	BSTNode<T>* left;
	BSTNode<T>* right;
};


// The binary search tree class.
template<class T>
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<T>& other);
	~BinarySearchTree();

	BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other);
	BinarySearchTree<T> operator+(const T element);
	BinarySearchTree<T>& operator+=(const T element);
	BinarySearchTree<T> operator-(const T element);
	BinarySearchTree<T>& operator-=(const T element);

	void balanceTree();
	void bft();
	void clear();
	BinarySearchTree<T> clone();
	bool contains(const T element) const;
	void dft();
	void display();
	uint height() const;
	void insert(const T element);
	bool isEmpty() const;
	void remove(const T element);

private:
	void calibrateHeights(BSTNode<T>* node);
	void clear(BSTNode<T>* node);
	void clone(BSTNode<T>* thisNode, BSTNode<T>* otherNode);
	bool contains(BSTNode<T>* node, const T& element) const;
	void createBackbone();
	void dft(BSTNode<T>* node);
	void insert(BSTNode<T>* node, const T& element);
	void linkParent(
		BSTNode<T>* parent, BSTNode<T>* node, BSTNode<T>* child);
	void remove(BSTNode<T>* parent, BSTNode<T>* node, const T& element);
	void rotateLeft(BSTNode<T>* parent, BSTNode<T>* node);
	void rotateRight(BSTNode<T>* parent, BSTNode<T>* node);
	void updateHeight(BSTNode<T>* node);
	BSTNode<T>* root;
};


// Simplify the binary search tree type.
template<class T>
using BST = BinarySearchTree<T>;


#include "binary_search_tree.cpp"

#endif
