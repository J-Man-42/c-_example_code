#include <iostream>
#include <sstream>
#include "binary_search_tree.h"
using namespace std;


// The constructor.
template<class T>
BinarySearchTree<T>::BinarySearchTree() {
	root = nullptr;
}


// Breadth First Traversal.
template<class T>
void BinarySearchTree<T>::bft() {}



// Depth First Traversal.
template<class T>
void BinarySearchTree<T>::dft() {
	dft(root);
	cout << endl;
}

// Recursive part of the DFT.
template<class T>
void BinarySearchTree<T>::dft(Node<T>* node) {

	// Stop if node is null.
	if (node)
		return;

	// Traverse left, print current, then traverse right.
	dft(node->left);
	cout << node->data << " ";
	dft(node->right);
}



// Insert into the tree.
template<class T>
void BinarySearchTree<T>::insert(const T element) {

	// If root is null, create root.
	if (!root) {
		root = new Node<T>(element);
	}

	// Otherwise, recursively traverse root.
	else {
		insert(root, element);
	}
}

// The recursive insertion function.
template<class T>
void BinarySearchTree<T>::insert(Node<T>* node, const T& element) {

	// Element smaller than current node.
	if (element < node->data) {

		// Traverse left if not null, otherwise create left.
		if (node->left) {
			insert(node->left, element);
		} else {
			node->left = new Node<T>(element);
		}
	}

	// Element larger than or equal to current node.
	else {

		// Traverse right if not null, otherwise create right.
		if (node->right) {
			insert(node->right, element);
		} else {
			node->right = new Node<T>(element);
		}
	}
}