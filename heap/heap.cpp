#include <iostream>
// #include <algorithm>
#include <cmath>
// #include <sstream>
#include "../queue/queue.h"
#include "heap.h"
using namespace std;


// The constructor.
template<class T>
Heap<T>::Heap() {
	root = nullptr;
	leftmost = nullptr;
	numElements = 0;
}


// // The copy constructor.
// template<class T>
// Heap<T>::Heap(const Heap<T>& other) {

// 	// If the same trees have been provided, do nothing.
// 	if (this == &other) {
// 		return;
// 	}

// 	// Copy other.root if not null.
// 	this->root = nullptr;
// 	if (other.root) {
// 		this->root = new HeapNode<T>(other.root);

// 		// Recursively clone all children.
// 		clone(this->root, other.root);
// 	}
// }


// The destructor.
template<class T>
Heap<T>::~Heap() {
	clear();
}



// // Overload the assignment operator.
// template<class T>
// Heap<T>& Heap<T>::operator=(const Heap<T>& other) {

// 	// If the same trees have been provided, do nothing.
// 	if (this != &other) {
// 		this->clear();

// 		// Copy other.root if not null.
// 		if (other.root) {
// 			this->root = new HeapNode<T>(other.root);

// 			// Recursively clone all children.
// 			clone(this->root, other.root);
// 		}
// 	}

// 	return *this;
// }


// // Returns a copied tree with element inserted.
// template<class T>
// Heap<T> Heap<T>::operator+(const T element) {
// 	Heap<T> tree = this->clone();
// 	tree.insert(element);
// 	return tree;
// }


// // Insert the element into the tree.
// template<class T>
// Heap<T>& Heap<T>::operator+=(const T element) {
// 	this->insert(element);
// 	return *this;
// }


// // Returns a copied tree with element removed.
// template<class T>
// Heap<T> Heap<T>::operator-(const T element) {
// 	Heap<T> tree = this->clone();
// 	tree.remove(element);
// 	return tree;
// }


// // Remove the element from the tree.
// template<class T>
// Heap<T>& Heap<T>::operator-=(const T element) {
// 	this->remove(element);
// 	return *this;
// }



// Breadth First Traversal.
template<class T>
void Heap<T>::bft() {

	// Return if root is null.
	if (isEmpty()) {
		cout << endl;
		return;
	}

	// Create queue and add root.
	Queue<HeapNode<T>*> queue;
	queue.push(root);

	// Loop while the queue is not empty.
	HeapNode<T>* nodePtr;
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



// // Completely calculate heights from the ground up.
// template<class T>
// void Heap<T>::calibrateHeights(HeapNode<T>* node) {

// 	// Stop when null.
// 	if (!node) {
// 		return;
// 	}

// 	// Calibrate heights of both children.
// 	calibrateHeights(node->left);
// 	calibrateHeights(node->right);

// 	// Update height of current node.
// 	updateHeight(node);
// }



// Clears all entries in the tree.
template<class T>
void Heap<T>::clear() {
	clear(root);
	root = nullptr;
	leftmost = nullptr;
	numElements = 0;
}

// Recursive part of clear.
template<class T>
void Heap<T>::clear(HeapNode<T>* node) {

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



// // Create a hard copy of this tree.
// template<class T>
// Heap<T> Heap<T>::clone() {
// 	return Heap<T>(*this);
// }

// // The recursive clone function.
// template<class T>
// void Heap<T>::clone(
// 	HeapNode<T>* thisNode, HeapNode<T>* otherNode) {

// 	// Clone left child.
// 	if (otherNode->left) {
// 		thisNode->left = new HeapNode<T>(otherNode->left);
// 		clone(thisNode->left, otherNode->left);
// 	}

// 	// Clone right child.
// 	if (otherNode->right) {
// 		thisNode->right = new HeapNode<T>(otherNode->right);
// 		clone(thisNode->right, otherNode->right);
// 	}
// }



// // Returns true if the element is in the tree.
// template<class T>
// bool Heap<T>::contains(const T element) const {
// 	return contains(root, element);
// }

// // Recursively search for element in tree.
// template<class T>
// bool Heap<T>::contains(
// 	HeapNode<T>* node, const T& element) const {

// 	// Return false if node is null.
// 	if (!node) {
// 		return false;
// 	}

// 	// Return true if element is found.
// 	if (node->data == element) {
// 		return true;
// 	}

// 	// Traverse left if element is smaller than current node.
// 	if (element < node->data) {
// 		return contains(node->left, element);
// 	}

// 	// Traverse right otherwise.
// 	return contains(node->right, element);
// }



// Depth First Traversal.
template<class T>
void Heap<T>::dft() {
	dft(root);
	cout << endl;
}

// Recursive part of the DFT.
template<class T>
void Heap<T>::dft(HeapNode<T>* node) {

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
void Heap<T>::display() {
	displayTree<HeapNode<T>>(root);
}



// Returns the height of the tree.
template<class T>
unsigned Heap<T>::height() const {
	if (isEmpty()) {
		return 0;
	}
	return root->height;
}



// Returns true if root is null.
template<class T>
bool Heap<T>::isEmpty() const {
	return root == nullptr;
}


// Returns true if root is not null.
template<class T>
bool Heap<T>::isNotEmpty() const {
	return root != nullptr;
}



// Push an element onto the heap.
template<class T>
void Heap<T>::push(const T element) {

	// Increment the number of elements.
	numElements++;

	// If root is null, create root.
	if (isEmpty()) {
		root = leftmost = new HeapNode<T>(element);
		root->next = root->prev = root;
		return;
	}

	// Create the new node.
	HeapNode<T>* newNode = new HeapNode<T>(element);
	unsigned test = pow(2, int(log2(numElements)));
	
	// Place new node at a new depth.
	if (numElements == test) {
		leftmost->left = newNode;
		newNode->parent = leftmost;
		leftmost = leftmost->left;
		leftmost->next = leftmost->prev = leftmost;
	}

	// Place new node in current row.
	else {
		newNode->next = leftmost;
		newNode->prev = leftmost->prev;
		newNode->prev->next = newNode;
		newNode->next->prev = newNode;

		// Right child.
		if (newNode->prev->parent->left == newNode->prev) {
			newNode->parent = newNode->prev->parent;
			newNode->parent->right = newNode;
		}

		// Left child.
		else {
			newNode->parent = newNode->prev->parent->next;
			newNode->parent->left = newNode;
		}
	}

	// Heapify and update heights.
	HeapNode<T>* nodePtr = newNode;
	while (nodePtr) {
		if (nodePtr->parent && nodePtr->data > nodePtr->parent->data) {
			swap(nodePtr->data, nodePtr->parent->data);
		}
		updateHeight(nodePtr);
		nodePtr = nodePtr->parent;
	}
}



// Remove the value at root and heapify.
template<class T>
T Heap<T>::pop() {}



// Returns the size of the heap.
template<class T>
unsigned Heap<T>::size() const {
	return numElements;
}



// Updates the node's height based on it's left and right child.
template<class T>
void Heap<T>::updateHeight(HeapNode<T>* node) {

	// If node is null, do nothing.
	if (!node) {
		return;
	}

	// Get the left and right child heights.
	unsigned left = (node->left ? node->left->height : 0);
	unsigned right = (node->right ? node->right->height : 0);

	// Height of node is max height of children + 1.
	node->height = max(left, right) + 1;
}
