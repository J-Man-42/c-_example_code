#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include "../display_structure/display_structure.h"


// The node class.
template<class T>
class AVLNode
{
public:
	AVLNode() {
		this->data = NULL;
		this->height = 0;
		this->colour = '\0';
		this->left = nullptr;
		this->right = nullptr;
	}
	AVLNode(const T data) {
		this->data = data;
		this->height = 1;
		this->colour = '\0';
		this->left = nullptr;
		this->right = nullptr;
	}
	AVLNode(AVLNode* other) {
		this->data = other->data;
		this->height = other->height;
		this->colour = other->colour;
		this->left = nullptr;
		this->right = nullptr;
	}
	~AVLNode() {
		this->left = nullptr;
		this->right = nullptr;
	}
	T data;
	int height;
	char colour;
	AVLNode<T>* left;
	AVLNode<T>* right;
};


// The binary search tree class.
template<class T>
class AVLTree
{
public:
	AVLTree();
	AVLTree(const AVLTree<T>& other);
	~AVLTree();

	AVLTree<T>& operator=(const AVLTree<T>& other);
	AVLTree<T> operator+(const T element);
	AVLTree<T>& operator+=(const T element);
	AVLTree<T> operator-(const T element);
	AVLTree<T>& operator-=(const T element);

	void bft();
	void clear();
	AVLTree<T> clone();
	bool contains(const T element) const;
	void dft();
	void display();
	uint height() const;
	void insert(const T element);
	bool isEmpty() const;
	bool isNotEmpty() const;
	void remove(const T element);

private:
	void clear(AVLNode<T>* node);
	void clone(AVLNode<T>* thisNode, AVLNode<T>* otherNode);
	bool contains(AVLNode<T>* node, const T& element) const;
	AVLNode<T>* deleteByCopying(
		AVLNode<T>* origin, AVLNode<T>* parent, AVLNode<T>* node);
	void dft(AVLNode<T>* node);
	uint height(AVLNode<T>* node) const;
	void insert(AVLNode<T>* parent, AVLNode<T>* node, const T& element);
	void linkParent(
		AVLNode<T>* parent, AVLNode<T>* node,
		AVLNode<T>* child = nullptr);
	void remove(AVLNode<T>* parent, AVLNode<T>* node, const T& element);
	void rotateIfUnbalanced(AVLNode<T>* parent, AVLNode<T>* node);
	void rotateLeft(AVLNode<T>* parent, AVLNode<T>* node);
	void rotateRight(AVLNode<T>* parent, AVLNode<T>* node);
	void updateHeight(AVLNode<T>* node);
	AVLNode<T>* root;
};


#include "avl_tree.cpp"

#endif
