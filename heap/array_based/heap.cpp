#include <iostream>
#include <cmath>
#include "heap.h"
using namespace std;


// The constructor.
template<class T>
Heap<T>::Heap(const bool maxHeap, const unsigned maxCapacity) {
	this->numElements = 0;
	this->maxCapacity = maxCapacity;
	this->maxHeap = maxHeap;
	this->array = new T[maxCapacity];
}


// The copy constructor.
template<class T>
Heap<T>::Heap(const Heap<T>& other) {

	// If the same heaps have been provided, do nothing.
	if (this == &other) {
		return;
	}

	// Copy heap parameters.
	this->numElements = other.numElements;
	this->maxCapacity = other.maxCapacity;
	this->maxHeap = other.maxHeap;
	this->array = new T[maxCapacity];

	// Copy all elements.
	for (unsigned i = 0; i < numElements; i++) {
		this->array[i] = other.array[i];
	}
}


// Construct heap from a given array.
template<class T>
Heap<T>::Heap(const T array[], const unsigned SIZE, const bool maxHeap) {
	
	// Set defaults.
	this->numElements = 0;
	this->maxCapacity = 100;
	this->maxHeap = maxHeap;
	this->array = new T[maxCapacity];

	// Iteratively push all array elements.
	for (unsigned i = 0; i < SIZE; i++) {
		this->push(array[i]);
	}
}


// The destructor.
template<class T>
Heap<T>::~Heap() {
	clear();
	delete [] array;
}



// Overload the assignment operator.
template<class T>
Heap<T>& Heap<T>::operator=(const Heap<T>& other) {

	// If the same heaps have been provided, do nothing.
	if (this != &other) {
		this->clear();
		delete [] array;

		// Copy heap parameters.
		this->numElements = other.numElements;
		this->maxCapacity = other.maxCapacity;
		this->maxHeap = other.maxHeap;
		this->array = new T[maxCapacity];

		// Copy all elements.
		for (unsigned i = 0; i < numElements; i++) {
			this->array[i] = other.array[i];
		}
	}

	return *this;
}


// Returns a copied heap with element pushed.
template<class T>
Heap<T> Heap<T>::operator+(const T element) {
	Heap<T> heap = this->clone();
	heap.push(element);
	return heap;
}


// Push the element into the heap.
template<class T>
Heap<T>& Heap<T>::operator+=(const T element) {
	this->push(element);
	return *this;
}


// Pop from heap and return resulting heap.
template<class T>
Heap<T>& Heap<T>::operator--() {
	this->pop();
	return *this;
}


// Pop from heap and return copy of initial heap.
template<class T>
Heap<T> Heap<T>::operator--(int) {
	Heap<T> heap = this->clone();
	this->pop();
	return heap;
}



// Breadth First Traversal.
template<class T>
void Heap<T>::bft() {
	for (unsigned i = 0; i < numElements; i++) {
		cout << "  " << array[i];
	}
	cout << endl;
}



// Returns the current heap capacity.
template<class T>
unsigned Heap<T>::capacity() const {
	return maxCapacity;
}



// Clears all entries in the heap.
template<class T>
void Heap<T>::clear() {
	numElements = 0;
}



// Create a hard copy of this heap.
template<class T>
Heap<T> Heap<T>::clone() {
	return Heap<T>(*this);
}



// Max Heap:  returns status of left > right.
// Min Heap:  returns status of left < right.
template<class T>
bool Heap<T>::compare(const T left, const T right) const {
	if (maxHeap)
		return left > right;
	return left < right;
}



// Returns true if the element is in the heap.
template<class T>
bool Heap<T>::contains(const T element) const {

	// If heap is empty, return false.
	if (isEmpty()) {
		return false;
	}

	// Search heap otherwise.
	return contains(0, element);
}

// Recursive part of the search function.
template<class T>
bool Heap<T>::contains(const unsigned index, const T& element) const {
	bool found;

	// See if found.
	if (array[index] == element) {
		return true;
	}

	// Calculate the left and right child indices.
	unsigned left = 2*index + 1;
	unsigned right = 2*index + 2;

	// See if possibly at left child.
	if (left < numElements && !compare(element, array[left])) {
		found = contains(left, element);
		if (found) {
			return true;
		}
	}

	// See if possibly at right child.
	if (right < numElements && !compare(element, array[right])) {
		found = contains(right, element);
		if (found) {
			return true;
		}
	}

	// Return false otherwise.
	return false;
}



// Depth First Traversal.
template<class T>
void Heap<T>::dft() {
	dft(0);
	cout << endl;
}

// Recursive part of the DFT.
template<class T>
void Heap<T>::dft(const unsigned index) {

	// Stop if index >= numElements.
	if (index >= numElements) {
		return;
	}

	// Calculate the left and right child indices.
	unsigned left = 2*index + 1;
	unsigned right = 2*index + 2;

	// Traverse left, print current, then traverse right.
	dft(left);
	cout << "  " << array[index];
	dft(right);
}



// Elegantly displays the heap.
template<class T>
void Heap<T>::display() {
	displayHeap(array, numElements);
}



// Ensures the heap properties remain for the given node.
template<class T>
void Heap<T>::heapify(unsigned index) {

	// Heapify all children of the given node.
	unsigned child, left, right;
	while (index < numElements) {
		child = index;

		// Calculate the left and right child indices.
		left = 2*index + 1;
		right = 2*index + 2;

		// Get the maximum amongst node, left, and right child.
		if (right < numElements && compare(array[right], array[index])) {
			child = right;
		}
		if (left < numElements && compare(array[left], array[child])) {
			child = left;
		}

		// Check if swapping is needed.
		if (child == index) {
			index = numElements;
		} else {
			swap(array[index], array[child]);
			index = child;
		}
	}
}



// Returns the height of the heap.
template<class T>
unsigned Heap<T>::height() const {
	if (isEmpty()) {
		return 0;
	}
	return log2(numElements) + 1;
}



// Returns true numElements is zero.
template<class T>
bool Heap<T>::isEmpty() const {
	return numElements == 0;
}


// Returns true if configured as a max heap.
template<class T>
bool Heap<T>::isMaxHeap() const {
	return maxHeap;
}


// Returns true if configured as a min heap.
template<class T>
bool Heap<T>::isMinHeap() const {
	return !maxHeap;
}


// Returns true numElements is not zero.
template<class T>
bool Heap<T>::isNotEmpty() const {
	return numElements != 0;
}



// Push an element onto the heap.
template<class T>
void Heap<T>::push(const T element) {

	// Increment the number of elements.
	numElements++;

	// If heap is empty, create root.
	if (isEmpty()) {
		array[0] = element;
		return;
	}

	// Place element at end of heap.
	unsigned index = numElements - 1;
	array[index] = element;

	// Heapify.
	unsigned parent = (index - 1) / 2;
	while (index > 0) {
		if (compare(array[index], array[parent])) {
			swap(array[index], array[parent]);
			index = parent;
			parent = (index - 1) / 2;
		} else break;

	}

	// If at max capacity, increase array size.
	if (numElements == maxCapacity) {
		maxCapacity = maxCapacity*1.5;
		T* temp = new T[maxCapacity];
		for (unsigned i = 0; i < numElements; i++) {
			temp[i] = array[i];
		}
		delete [] array;
		array = temp;
	}
}



// Remove the value at root and heapify.
template<class T>
T Heap<T>::pop() {

	// If heap is empty, throw error.
	if (isEmpty()) {
		throw "Error! Heap is empty";
	}

	// Decrement the number of elements.
	numElements--;

	// Only one element in heap.
	if (numElements == 0) {
		return array[0];
	}

	// Swap last element and root.
	swap(array[0], array[numElements]);

	// Heapify from root.
	heapify(0);

	// Return data.
	return array[numElements];
}



// Returns the size of the heap.
template<class T>
unsigned Heap<T>::size() const {
	return numElements;
}



// Converts the heap into a dynamic array.
template<class T>
T* Heap<T>::toDynamicArray() {

	// Throw an error if the heap is empty.
	if (isEmpty()) {
		throw "Error! No elements in the heap";
	}

	// Returns array with heap's number of elements.
	return toDynamicArray(numElements);
}


// Converts the heap into a dynamic array of the specified size.
template<class T>
T* Heap<T>::toDynamicArray(const unsigned SIZE) {

	// Initialise a new array.
	T* newArray = new T[SIZE];

	// Copy all elements into new array.
	for (unsigned i = 0; i < SIZE; i++) {
		newArray[i] = this->array[i];
	}

	// Return the new array.
	return newArray;
}



// Converts between max heap <--> min heap.
template<class T>
void Heap<T>::toggleMaxMin() {

	// Switch between max and min heap.
	maxHeap = !maxHeap;

	// If at most one element in the heap, do nothing.
	if (numElements <= 1) {
		return;
	}

	// Iterate backwards through all rows excluding leaf nodes.
	for (int i = numElements / 2 - 1; i >= 0; i--) {
		heapify(i);
	}
}
