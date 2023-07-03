#include <iostream>
#include <algorithm>
#include <sstream>
#include "../queue/queue.h"
#include "binary_search_tree.h"
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


// Returns a copied tree with element inserted.
template<class T>
BST<T> BinarySearchTree<T>::operator+(const T element) {
	BST<T> tree = this->clone();
	tree.insert(element);
	return tree;
}


// Insert the element into the tree.
template<class T>
BST<T>& BinarySearchTree<T>::operator+=(const T element) {
	this->insert(element);
	return *this;
}


// Returns a copied tree with element removed.
template<class T>
BST<T> BinarySearchTree<T>::operator-(const T element) {
	BST<T> tree = this->clone();
	tree.remove(element);
	return tree;
}


// Remove the element from the tree.
template<class T>
BST<T>& BinarySearchTree<T>::operator-=(const T element) {
	this->remove(element);
	return *this;
}



// Balance the tree after creating the backbone.
template<class T>
void BinarySearchTree<T>::balanceTree() {

	// If tree is empty, do nothing.
	if (isEmpty()) {
		return;
	}

	// Create the backbone.
	createBackbone();

	// Get actual and ideal number of nodes.
	uint n = root->height;
	uint m = pow(2, int(log2(n+1))) - 1;

	// Node pointers.
	BSTNode<T>* parent = nullptr;
	BSTNode<T>* node = root;
	BSTNode<T>* child = root->right;

	// Initial set of rotations.
	for (uint i = m; i < n; i++) {
		rotateLeft(parent, node);
		parent = child;
		node = child->right;
		if (node) {
			child = node->right;
		}
	}

	// The remaining set of rotations.
	while (m > 1) {

		// Update variables and pointers.
		m /= 2;
		BSTNode<T>* parent = nullptr;
		BSTNode<T>* node = root;
		BSTNode<T>* child = root->right;

		// Make m rotations.
		for (uint i = 0; i < m; i++) {
			rotateLeft(parent, node);
			parent = child;
			node = child->right;
			child = node->right;
		}
	}

	// Recalibrate the tree heights.
	calibrateHeights(root);
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



// Completely calculate heights from the ground up.
template<class T>
void BinarySearchTree<T>::calibrateHeights(BSTNode<T>* node) {

	// Stop when null.
	if (!node) {
		return;
	}

	// Calibrate heights of both children.
	calibrateHeights(node->left);
	calibrateHeights(node->right);

	// Update height of current node.
	updateHeight(node);
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



// Turns the tree into a backbone for balancing the tree.
template<class T>
void BinarySearchTree<T>::createBackbone() {
	BSTNode<T>* parent = nullptr;
	BSTNode<T>* node = root;
	BSTNode<T>* child;

	// Traverse all right nodes.
	while (node) {
		child = node->left;

		// Rotate right if left child exists.
		if (child) {
			rotateRight(parent, node);
			node = child;
		}

		// Move down right otherwise.
		else {
			parent = node;
			node = node->right;
		}
	}

	// Recalibrate the tree heights.
	calibrateHeights(root);
}



// Delete the node by copying.
template<class T>
BSTNode<T>* BinarySearchTree<T>::deleteByCopying(
	BSTNode<T>* origin, BSTNode<T>* parent, BSTNode<T>* node) {

	// There is still a right child.
	BSTNode<T>* deleteNode;
	if (node->right) {
		deleteNode = deleteByCopying(origin, node, node->right);
		updateHeight(node);
		return deleteNode;
	}

	// Found the rightmost node.
	origin->data = node->data;
	if (parent == origin) {
		parent->left = node->left;
	} else {
		parent->right = node->left;
	}

	// Return the node to delete.
	return node;
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



// Elegantly displays the tree.
template<class T>
void BinarySearchTree<T>::display() {
	displayTree<BSTNode<T>>(root);
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



// Properly links the parent and child nodes.
template<class T>
void BinarySearchTree<T>::linkParent(
	BSTNode<T>* parent, BSTNode<T>* node, BSTNode<T>* child) {

	// Node is root.
	if (!parent) {
		root = child;
	}

	// Node is not root.
	else if (parent->left == node) {
		parent->left = child;
	} else {
		parent->right = child;
	}
}



// Removed the given element from the tree.
template<class T>
void BinarySearchTree<T>::remove(const T element) {
	remove(nullptr, root, element);

	// Update root's height.
	updateHeight(root);
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
		updateHeight(node);
		return;
	}

	// Traverse right if element is larger than current node.
	if (element > node->data) {
		remove(node, node->right, element);
		updateHeight(node);
		return;
	}

	// It's found otherwise.
	BSTNode<T>* deleteNode = node;

	// Case 1: node has a left child.
	if (node->left) {
		deleteNode = deleteByCopying(node, node, node->left);
		updateHeight(node);
	}

	// Case 2: node only has a right child.
	else if (node->right) {
		linkParent(parent, node, node->right);
	}

	// Case 3: node is leaf node.
	else {
		node->height = 0;
		linkParent(parent, node);
	}

	// Delete the node.
	delete deleteNode;
}



// Perform a left rotation.
template<class T>
void BinarySearchTree<T>::rotateLeft(
	BSTNode<T>* parent, BSTNode<T>* node) {

	// Do nothing if right child is null.
	if (!node->right) {
		return;
	}

	// Link parent to right child.
	BSTNode<T>* child = node->right;
	linkParent(parent, node, child);

	// Rearrange node and child.
	node->right = child->left;
	child->left = node;

	// Update their heights.
	updateHeight(node);
	updateHeight(child);
}



// Perform a right rotation.
template<class T>
void BinarySearchTree<T>::rotateRight(
	BSTNode<T>* parent, BSTNode<T>* node) {

	// Do nothing if left child is null.
	if (!node->left) {
		return;
	}

	// Link parent to left child.
	BSTNode<T>* child = node->left;
	linkParent(parent, node, child);

	// Rearrange node and child.
	node->left = child->right;
	child->right = node;

	// Update their heights.
	updateHeight(node);
	updateHeight(child);
}



// Updates the node's height based on it's left and right child.
template<class T>
void BinarySearchTree<T>::updateHeight(BSTNode<T>* node) {

	// If node is null, do nothing.
	if (!node) {
		return;
	}

	// Get the left and right child heights.
	uint left = (node->left ? node->left->height : 0);
	uint right = (node->right ? node->right->height : 0);

	// Height of node is max height of children + 1.
	node->height = max(left, right) + 1;
}
