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
void BinarySearchTree<T>::bft() {

}



// Depth First Traversal.
template<class T>
void BinarySearchTree<T>::dft() {
	dft(root);
	cout << endl;
}

// Recursive part of the DFT.
template<class T>
void BinarySearchTree<T>::dft(Node<T>* node) {
	if (!node) {
		return;
	}

	dft(node->left);
	cout << node->data << " ";
	dft(node->right);
}



// Insert into the tree.
template<class T>
void BinarySearchTree<T>::insert(const T element) {
	if (!root) {
		root = new Node<T>(element);
	} else {
		insert(root, element);
	}
}

// The recursive insertion function.
template<class T>
void BinarySearchTree<T>::insert(Node<T>* node, const T& element) {
	if (element < node->data) {
		if (node->left) {
			insert(node->left, element);
		} else {
			node->left = new Node<T>(element);
		}
	} else {
		if (node->right) {
			insert(node->right, element);
		} else {
			node->right = new Node<T>(element);
		}
	}
}