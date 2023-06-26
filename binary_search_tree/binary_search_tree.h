#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>


// The node class.
template<class T>
class BSTNode
{
public:
	BSTNode() {
		this->data = NULL;
		this->left = nullptr;
		this->right = nullptr;
	}
	BSTNode(const T data) {
		this->data = data;
		this->left = nullptr;
		this->right = nullptr;
	}
	~BSTNode() {
		this->left = nullptr;
		this->right = nullptr;
	}
	T data;
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

	void bft();
	void clear();
	BinarySearchTree<T> clone();
	bool contains(const T element) const;
	void dft();
	void insert(const T element);
	void remove(const T element);

private:
	void clear(BSTNode<T>* node);
	void clone(BSTNode<T>* thisNode, BSTNode<T>* otherNode);
	bool contains(BSTNode<T>* node, const T& element) const;
	void dft(BSTNode<T>* node);
	void insert(BSTNode<T>* node, const T& element);
	void remove(BSTNode<T>* parent, BSTNode<T>* node, const T& element);
	BSTNode<T>* root;
};


// Simplify the binary search tree type.
template<class T>
using BST = BinarySearchTree<T>;


#include "binary_search_tree.cpp"

#endif
