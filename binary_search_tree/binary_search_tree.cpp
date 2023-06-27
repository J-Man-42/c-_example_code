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


// The copy constructor.
template<class T>
BinarySearchTree<T>::BinarySearchTree(const BST<T>& other) {

	// If the same trees have been provided, do nothing.
	if (this == &other) {
		return;
	}

	// Copy other.root if not null.
	this->root = nullptr;
	if (other.root) {
		this->root = new BSTNode<T>(other.root);

		// Recursively clone all children.
		clone(this->root, other.root);
	}
}


// The destructor.
template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
	clear();
}



// Overload the assignment operator.
template<class T>
BST<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& other) {

	// If the same trees have been provided, do nothing.
	if (this != &other) {
		this->clear();

		// Copy other.root if not null.
		if (other.root) {
			this->root = new BSTNode<T>(other.root);

			// Recursively clone all children.
			clone(this->root, other.root);
		}
	}

	return *this;
}



// Breadth First Traversal.
template<class T>
void BinarySearchTree<T>::bft() {

	// Return if root is null.
	if (isEmpty()) {
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



// Create a hard copy of this tree.
template<class T>
BST<T> BinarySearchTree<T>::clone() {
	return BST<T>(*this);
}

// The recursive clone function.
template<class T>
void BinarySearchTree<T>::clone(
	BSTNode<T>* thisNode, BSTNode<T>* otherNode) {

	// Clone left child.
	if (otherNode->left) {
		thisNode->left = new BSTNode<T>(otherNode->left);
		clone(thisNode->left, otherNode->left);
	}

	// Clone right child.
	if (otherNode->right) {
		thisNode->right = new BSTNode<T>(otherNode->right);
		clone(thisNode->right, otherNode->right);
	}
}



// Returns true if the element is in the tree.
template<class T>
bool BinarySearchTree<T>::contains(const T element) const {
	return contains(root, element);
}

// Recursively search for element in tree.
template<class T>
bool BinarySearchTree<T>::contains(
	BSTNode<T>* node, const T& element) const {

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



// Returns the height of the tree.
template<class T>
uint BinarySearchTree<T>::height() const {
	if (isEmpty()) {
		return 0;
	}
	return root->height;
}



// Insert into the tree.
template<class T>
void BinarySearchTree<T>::insert(const T element) {

	// If root is null, create root.
	if (isEmpty()) {
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

	// Update node height.
	updateHeight(node);
}



// Returns true if root is null.
template<class T>
bool BinarySearchTree<T>::isEmpty() const {
	return root == nullptr;
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



// Updates the node's height based on it's left and right child.
template<class T>
void BinarySearchTree<T>::updateHeight(BSTNode<T>* node) const {

	// Check for left child.
	if (node->left && node->left->height >= node->height) {
		node->height = node->left->height + 1;
	}

	// Check for right child.
	else if (node->right && node->right->height >= node->height) {
		node->height = node->right->height + 1;
	}
}