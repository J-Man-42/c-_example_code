#include <iostream>
#include <sstream>
#include "binary_search_tree.h"
#include "../queue/queue.h"
using namespace std;


// The constructor.
template<class T>
BinarySearchTree<T>::BinarySearchTree() {
	root = nullptr;
}


// The destructor.
template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
	clear();
}



// Breadth First Traversal.
template<class T>
void BinarySearchTree<T>::bft() {

	// Return if root is null.
	if (!root) {
		cout << endl;
		return;
	}

	// Create queue and add root.
	Queue<BSTNode<T>*> queue;
	queue.push(root);

	// Loop while the queue is not empty.
	BSTNode<T>* nodePtr;
	while (!queue.isEmpty()) {
		nodePtr = queue.pop();
		cout << "  " << nodePtr->data;

		// Add left child if not null.
		if (nodePtr->left) {
			queue.push(nodePtr->left);
		}

		// Add right child if not null.
		if (nodePtr->right) {
			queue.push(nodePtr->right);
		}
	}

	// Final newline.
	cout << endl;
}



// Clears all entries in the tree.
template<class T>
void BinarySearchTree<T>::clear() {
	clear(root);
	root = nullptr;
}

// Recursive part of clear.
template<class T>
void BinarySearchTree<T>::clear(BSTNode<T>* node) {
	
	// Simply return if node is null.
	if (!node) {
		return;
	}

	// Traverse both left and right children.
	clear(node->left);
	clear(node->right);

	// Delete the node afterwards.
	delete node;
}



// Returns true if the element is in the tree.
template<class T>
bool BinarySearchTree<T>::contains(const T element) const {
	return contains(root, element);
}

// Recursively search for element in tree.
template<class T>
bool BinarySearchTree<T>::contains(BSTNode<T>* node, const T& element) const {

	// Return false if node is null.
	if (!node) {
		return false;
	}

	// Return true if element is found.
	if (node->data == element) {
		return true;
	}

	// Traverse left if element is smaller than current node.
	if (element < node->data) {
		return contains(node->left, element);
	}

	// Traverse right otherwise.
	return contains(node->right, element);
}



// Depth First Traversal.
template<class T>
void BinarySearchTree<T>::dft() {
	dft(root);
	cout << endl;
}

// Recursive part of the DFT.
template<class T>
void BinarySearchTree<T>::dft(BSTNode<T>* node) {

	// Stop if node is null.
	if (!node) {
		return;
	}

	// Traverse left, print current, then traverse right.
	dft(node->left);
	cout << "  " << node->data;
	dft(node->right);
}



// Insert into the tree.
template<class T>
void BinarySearchTree<T>::insert(const T element) {

	// If root is null, create root.
	if (!root) {
		root = new BSTNode<T>(element);
	}

	// Otherwise, recursively traverse root.
	else insert(root, element);
}

// The recursive insertion function.
template<class T>
void BinarySearchTree<T>::insert(BSTNode<T>* node, const T& element) {

	// Element smaller than current node.
	if (element < node->data) {

		// Traverse left if not null, otherwise create left.
		if (node->left) {
			insert(node->left, element);
		} else {
			node->left = new BSTNode<T>(element);
		}
	}

	// Element larger than or equal to current node.
	else {

		// Traverse right if not null, otherwise create right.
		if (node->right) {
			insert(node->right, element);
		} else {
			node->right = new BSTNode<T>(element);
		}
	}
}



// Removed the given element from the tree.
template<class T>
void BinarySearchTree<T>::remove(const T element) {
	remove(nullptr, root, element);
}

// The recursive remove function.
template<class T>
void BinarySearchTree<T>::remove(
	BSTNode<T>* parent, BSTNode<T>* node, const T& element) {

	// If node is null, throw error.
	if (!node) {
		throw "Error! Element '"+to_string(element)+"' not found";
	}

	// Traverse left if element is smaller than current node.
	if (element < node->data) {
		remove(node, node->left, element);
	}

	// Traverse right if element is larger than current node.
	else if (element > node->data) {
		remove(node, node->right, element);
	}

	// It's found otherwise.
	else {
		BSTNode<T>* deleteNode = node;
		BSTNode<T>* child = node->left;
		while (child && child->right) {
			node = child;
			child = child->right;
		}

		// No left highest node.
		if (!child) {
			if (parent) {
				if (parent->right == node) {
					parent->right = node->right;
				} else {
					parent->left = node->right;
				}
			} else {
				root = node->right;
			}
		}

		// There is a left highest node.
		else {
			if (node->right == child) {
				node->right = child->left;
			} else {
				node->left = child->left;
			}
			deleteNode->data = child->data;
			deleteNode = child;
		}

		// Delete the node.
		delete deleteNode;
	}
}