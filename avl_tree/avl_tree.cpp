#include <iostream>
#include <algorithm>
#include <sstream>
#include "../queue/queue.h"
#include "avl_tree.h"
using namespace std;


// The constructor.
template<class T>
AVLTree<T>::AVLTree() {
	root = nullptr;
}


// The copy constructor.
template<class T>
AVLTree<T>::AVLTree(const AVLTree<T>& other) {

	// If the same trees have been provided, do nothing.
	if (this == &other) {
		return;
	}

	// Copy other.root if not null.
	this->root = nullptr;
	if (other.root) {
		this->root = new AVLNode<T>(other.root);

		// Recursively clone all children.
		clone(this->root, other.root);
	}
}


// The destructor.
template<class T>
AVLTree<T>::~AVLTree() {
	clear();
}



// Overload the assignment operator.
template<class T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& other) {

	// If the same trees have been provided, do nothing.
	if (this != &other) {
		this->clear();

		// Copy other.root if not null.
		if (other.root) {
			this->root = new AVLNode<T>(other.root);

			// Recursively clone all children.
			clone(this->root, other.root);
		}
	}

	return *this;
}


// Returns a copied tree with element inserted.
template<class T>
AVLTree<T> AVLTree<T>::operator+(const T element) {
	AVLTree<T> tree = this->clone();
	tree.insert(element);
	return tree;
}


// Insert the element into the tree.
template<class T>
AVLTree<T>& AVLTree<T>::operator+=(const T element) {
	this->insert(element);
	return *this;
}


// Returns a copied tree with element removed.
template<class T>
AVLTree<T> AVLTree<T>::operator-(const T element) {
	AVLTree<T> tree = this->clone();
	tree.remove(element);
	return tree;
}


// Remove the element from the tree.
template<class T>
AVLTree<T>& AVLTree<T>::operator-=(const T element) {
	this->remove(element);
	return *this;
}



// Breadth First Traversal.
template<class T>
void AVLTree<T>::bft() {

	// Return if root is null.
	if (isEmpty()) {
		cout << endl;
		return;
	}

	// Create queue and add root.
	Queue<AVLNode<T>*> queue;
	queue.push(root);

	// Loop while the queue is not empty.
	AVLNode<T>* nodePtr;
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
void AVLTree<T>::clear() {
	clear(root);
	root = nullptr;
}

// Recursive part of clear.
template<class T>
void AVLTree<T>::clear(AVLNode<T>* node) {

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
AVLTree<T> AVLTree<T>::clone() {
	return AVLTree<T>(*this);
}

// The recursive clone function.
template<class T>
void AVLTree<T>::clone(
	AVLNode<T>* thisNode, AVLNode<T>* otherNode) {

	// Clone left child.
	if (otherNode->left) {
		thisNode->left = new AVLNode<T>(otherNode->left);
		clone(thisNode->left, otherNode->left);
	}

	// Clone right child.
	if (otherNode->right) {
		thisNode->right = new AVLNode<T>(otherNode->right);
		clone(thisNode->right, otherNode->right);
	}
}



// Returns true if the element is in the tree.
template<class T>
bool AVLTree<T>::contains(const T element) const {
	return contains(root, element);
}

// Recursively search for element in tree.
template<class T>
bool AVLTree<T>::contains(
	AVLNode<T>* node, const T& element) const {

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



// Delete the node by copying.
template<class T>
AVLNode<T>* AVLTree<T>::deleteByCopying(
	AVLNode<T>* origin, AVLNode<T>* parent, AVLNode<T>* node) {

	// There is still a right child.
	AVLNode<T>* deleteNode;
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
void AVLTree<T>::dft() {
	dft(root);
	cout << endl;
}

// Recursive part of the DFT.
template<class T>
void AVLTree<T>::dft(AVLNode<T>* node) {

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
void AVLTree<T>::display() {
	displayTree<AVLNode<T>>(root);
}



// Returns the height of the tree.
template<class T>
uint AVLTree<T>::height() const {
	if (isEmpty()) {
		return 0;
	}
	return root->height;
}



// Insert into the tree.
template<class T>
void AVLTree<T>::insert(const T element) {

	// If root is null, create root.
	if (isEmpty()) {
		root = new AVLNode<T>(element);
	}

	// Otherwise, recursively traverse root.
	else insert(root, element);
}

// The recursive insertion function.
template<class T>
void AVLTree<T>::insert(AVLNode<T>* node, const T& element) {

	// Element smaller than current node.
	if (element < node->data) {

		// Traverse left if not null, otherwise create left.
		if (node->left) {
			insert(node->left, element);
		} else {
			node->left = new AVLNode<T>(element);
		}
	}

	// Element larger than or equal to current node.
	else {

		// Traverse right if not null, otherwise create right.
		if (node->right) {
			insert(node->right, element);
		} else {
			node->right = new AVLNode<T>(element);
		}
	}

	// Update node height.
	updateHeight(node);
}



// Returns true if root is null.
template<class T>
bool AVLTree<T>::isEmpty() const {
	return root == nullptr;
}


// Returns true if root is not null.
template<class T>
bool AVLTree<T>::isNotEmpty() const {
	return root != nullptr;
}



// Properly links the parent and child nodes.
template<class T>
void AVLTree<T>::linkParent(
	AVLNode<T>* parent, AVLNode<T>* node, AVLNode<T>* child) {

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
void AVLTree<T>::remove(const T element) {
	remove(nullptr, root, element);

	// Update root's height.
	updateHeight(root);
}

// The recursive remove function.
template<class T>
void AVLTree<T>::remove(
	AVLNode<T>* parent, AVLNode<T>* node, const T& element) {

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
	AVLNode<T>* deleteNode = node;

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
void AVLTree<T>::rotateLeft(
	AVLNode<T>* parent, AVLNode<T>* node) {

	// Do nothing if right child is null.
	if (!node->right) {
		return;
	}

	// Link parent to right child.
	AVLNode<T>* child = node->right;
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
void AVLTree<T>::rotateRight(
	AVLNode<T>* parent, AVLNode<T>* node) {

	// Do nothing if left child is null.
	if (!node->left) {
		return;
	}

	// Link parent to left child.
	AVLNode<T>* child = node->left;
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
void AVLTree<T>::updateHeight(AVLNode<T>* node) {

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
