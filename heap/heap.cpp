#include <iostream>
#include <cmath>
#include "heap.h"
using namespace std;


// The constructor.
template<class T>
Heap<T>::Heap() {
	root = nullptr;
	leftmost = nullptr;
	numElements = 0;
}


// The copy constructor.
template<class T>
Heap<T>::Heap(const Heap<T>& other) {

	// If the same trees have been provided, do nothing.
	if (this == &other) {
		return;
	}

	// Set defaults.
	this->root = nullptr;
	this->leftmost = nullptr;
	this->numElements = 0;

	// Copy other.root if not null.
	if (other.root) {
		this->root = this->leftmost = new HeapNode<T>(other.root);
		this->numElements = other.numElements;

		// Clone remaining children.
		clone(this->root, other.root);
	}
}


// The destructor.
template<class T>
Heap<T>::~Heap() {
	clear();
}



// Overload the assignment operator.
template<class T>
Heap<T>& Heap<T>::operator=(const Heap<T>& other) {

	// If the same trees have been provided, do nothing.
	if (this != &other) {
		this->clear();

		// Copy other.root if not null.
		if (other.root) {
			this->root = this->leftmost = new HeapNode<T>(other.root);
			this->numElements = other.numElements;

			// Clone remaining children.
			clone(this->root, other.root);
		}
	}

	return *this;
}


// Returns a copied tree with element pushed.
template<class T>
Heap<T> Heap<T>::operator+(const T element) {
	Heap<T> tree = this->clone();
	tree.push(element);
	return tree;
}


// Push the element into the tree.
template<class T>
Heap<T>& Heap<T>::operator+=(const T element) {
	this->push(element);
	return *this;
}



// Breadth First Traversal.
template<class T>
void Heap<T>::bft() {

	// Return if root is null.
	if (isEmpty()) {
		cout << endl;
		return;
	}

	// Iterate through the heap row by row.
	HeapNode<T>* nodePtr = root;
	HeapNode<T>* thisLeftmost = root;
	while (nodePtr) {
		cout << "  " << nodePtr->data;

		// Get next entry in the heap.
		if (nodePtr->next == thisLeftmost) {
			nodePtr = thisLeftmost = thisLeftmost->left;
		} else {
			nodePtr = nodePtr->next;
		}
	}

	// Final newline.
	cout << endl;
}



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



// Create a hard copy of this tree.
template<class T>
Heap<T> Heap<T>::clone() {
	return Heap<T>(*this);
}

// The private clone function.
template<class T>
void Heap<T>::clone(HeapNode<T>* thisNode, HeapNode<T>* otherNode) {

	// Clone all remaining children.
	HeapNode<T>* otherLeftmost = otherNode;
	for (unsigned i = 1; i < this->numElements; i++) {
		
		// End of the row.
		if (otherNode->next == otherLeftmost) {

			// Make the row circularly linked.
			thisNode->next = this->leftmost;
			this->leftmost->prev = thisNode;

			// Start new row.
			otherNode = otherLeftmost = otherLeftmost->left;
			this->leftmost->left = new HeapNode<T>(otherNode);
			this->leftmost->left->parent = this->leftmost;
			this->leftmost = this->leftmost->left;
			thisNode = this->leftmost;
		}

		// Continue with row.
		else {
			otherNode = otherNode->next;
			thisNode->next = new HeapNode<T>(otherNode);
			thisNode->next->prev = thisNode;
			thisNode = thisNode->next;

			// Right child.
			if (thisNode->prev->parent->left == thisNode->prev) {
				thisNode->parent = thisNode->prev->parent;
				thisNode->parent->right = thisNode;
			}

			// Left child.
			else {
				thisNode->parent = thisNode->prev->parent->next;
				thisNode->parent->left = thisNode;
			}
		}
	}

	// Make the final row circularly linked.
	thisNode->next = this->leftmost;
	this->leftmost->prev = thisNode;
}



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
