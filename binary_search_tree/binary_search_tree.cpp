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
	else {
		insert(root, element);
	}
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