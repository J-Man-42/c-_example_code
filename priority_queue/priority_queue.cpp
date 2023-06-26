#include <iostream>
#include <sstream>
#include "priority_queue.h"
using namespace std;


// The constructor.
template<class T>
PriorityQueue<T>::PriorityQueue() {
	head = tail = nullptr;
	length = 0;
}


// The copy constructor.
template<class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& other) {

	// If the two queues are equal, do nothing.
	if (this == &other) {
		return;
	}

	// Set the initial parameters.
	this->length = other.length;
	this->head = nullptr;
	this->tail = nullptr;

	// Copy other.head if not null.
	if (other.head) {
		this->head = new Node<T>(other.head->data);
		this->tail = this->head;

		// Copy all remaining elements.
		Node<T>* otherPtr = other.head->next;
		while (otherPtr) {
			this->tail->next = new Node<T>(otherPtr->data);
			this->tail = this->tail->next;
			otherPtr = otherPtr->next;
		}
	}
}


// Construct a PriorityQueue from the given array.
template<class T>
PriorityQueue<T>::PriorityQueue(const T array[], const uint SIZE) {
	this->head = nullptr;
	this->tail = nullptr;
	this->length = 0;
	for (size_t i = 0; i < SIZE; i++) {
		this->push(array[i]);
	}
}


// The destructor.
template<class T>
PriorityQueue<T>::~PriorityQueue() {
	clear();
}



// Output stream the queue to string.
template<class T>
ostream& operator<<(ostream& out, PriorityQueue<T>& queue) {
	out << queue.toString();
	return out;
}



// Overload the assignment operator.
template<class T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& other) {

	// Only make changes if this and other are different queues.
	if (this != &other) {
		this->clear();
		this->length = other.length;

		// Copy other.head if not null.
		if (other.head) {
			this->head = new Node<T>(other.head->data);
			this->tail = this->head;

			// Copy all remaining elements.
			Node<T>* otherPtr = other.head->next;
			while (otherPtr) {
				this->tail->next = new Node<T>(otherPtr->data);
				this->tail = this->tail->next;
				otherPtr = otherPtr->next;
			}
		}
	}

	return *this;
}



// Returns a copied queue with element added to the end.
template<class T>
PriorityQueue<T> PriorityQueue<T>::operator+(const T element) {
	PriorityQueue<T> queue = this->clone();
	queue.push(element);
	return queue;
}



// Returns a copied queue with the other queue added to the end.
template<class T>
PriorityQueue<T> PriorityQueue<T>::operator+(const PriorityQueue<T>& other) {
	PriorityQueue<T> queue = this->clone();
	Node<T>* nodePtr = other.head;
	while (nodePtr) {
		queue.push(nodePtr->data);
		nodePtr = nodePtr->next;
	}
	return queue;
}



// Add the element to the end of this queue.
template<class T>
PriorityQueue<T>& PriorityQueue<T>::operator+=(const T element) {
	this->push(element);
	return *this;
}



// Add the queue to the end of this queue.
template<class T>
PriorityQueue<T>& PriorityQueue<T>::operator+=(const PriorityQueue<T>& other) {
	Node<T>* nodePtr = other.head;
	while (nodePtr) {
		this->push(nodePtr->data);
		nodePtr = nodePtr->next;
	}
	return *this;
}



// Returns the element at the back of the queue.
template<class T>
T& PriorityQueue<T>::back() {

	// Throw an error if the queue is empty.
	if (isEmpty()) {
		throw "Error! The queue is empty";
	}

	// Returns the element at head.
	return tail->data;
}



// Delete all entries in the queue.
template<class T>
void PriorityQueue<T>::clear() {
	length = 0;

	// Check if head is not null.
	if (!isEmpty()) {

		// Delete all nodes except the last.
		Node<T>* nodePtr = head;
		while (head != tail) {
			head = head->next;
			delete nodePtr;
			nodePtr = head;
		}

		// Delete the final node.
		delete head;
		head = tail = nullptr;
	}
}



// Returns a hard copy of this queue.
template<class T>
PriorityQueue<T> PriorityQueue<T>::clone() {
	return PriorityQueue<T>(*this);
}



// Returns true if the element is in the queue.
template<class T>
bool PriorityQueue<T>::contains(const T element) const {
	Node<T>* nodePtr = head;
	while (nodePtr) {
		if (nodePtr->data == element)
			return true;
		if (nodePtr->data < element)
			return false;
		nodePtr = nodePtr->next;
	}
	return false;
}



// Returns the first element in the queue.
template<class T>
T& PriorityQueue<T>::front() {

	// Throw an error if the queue is empty.
	if (isEmpty()) {
		throw "Error! The queue is empty";
	}

	// Returns the element at head.
	return head->data;
}



// Returns true if head is null.
template<class T>
bool PriorityQueue<T>::isEmpty() const {
	return head == nullptr;
}



// Remove the element at head.
template<class T>
T PriorityQueue<T>::pop() {

	// Throw an error if the queue is empty.
	if (isEmpty()) {
		throw "Error! The queue is empty";
	}

	// Update length and extract the element.
	T element = head->data;
	length--;

	// Only one element in the queue.
	if (head == tail) {
		delete head;
		head = tail = nullptr;
	}

	// Otherwise, at least two elements in the queue.
	else {
		Node<T>* nodePtr = head;
		head = head->next;
		delete nodePtr;
	}

	// Return the element.
	return element;
}



// Add an element to the back of the queue.
template<class T>
void PriorityQueue<T>::push(const T element) {
	length++;

	// See if it's the first element.
	if (isEmpty()) {
		head = tail = new Node<T>(element);
	}

	// See if it's smaller than the last element.
	else if (tail->data >= element) {
		tail->next = new Node<T>(element);
		tail = tail->next;
	}

	// Otherwise, find position to insert.
	else {
		Node<T>* prevPtr = nullptr;
		Node<T>* nodePtr = head;
		while (nodePtr && nodePtr->data > element) {
			prevPtr = nodePtr;
			nodePtr = nodePtr->next;
		}
		if (prevPtr) {
			prevPtr->next = new Node<T>(element);
			prevPtr = prevPtr->next;
			prevPtr->next = nodePtr;
		} else {
			head = new Node<T>(element);
			head->next = nodePtr;
		}
	}
}



// Get the number of elements in the queue.
template<class T>
uint PriorityQueue<T>::size() const {
	return length;
}



// Converts the queue into a dynamic array.
template<class T>
T* PriorityQueue<T>::toDynamicArray() {

	// Throw an error if the queue is empty.
	if (isEmpty()) {
		throw "Error! The queue is empty";
	}

	// Returns array of queue's length.
	return toDynamicArray(length);
}


// Converts the queue into a dynamic array of the given size.
template<class T>
T* PriorityQueue<T>::toDynamicArray(const uint SIZE) {

	// Copy all elements to the new array.
	T* array = new T[SIZE];
	Node<T>* nodePtr = head;
	size_t limit = (length > SIZE ? SIZE : length);
	for (size_t i = 0; i < limit; i++) {
		array[i] = nodePtr->data;
		nodePtr = nodePtr->next;
	}

	// Return the final array.
	return array;
}



// Returns the string representation of the queue.
template<class T>
string PriorityQueue<T>::toString() {

	// Return empty parenthesis if empty queue.
	if (isEmpty()) {
		return "()";
	}

	// Iterate through all elements.
	Node<T>* nodePtr = head;
	stringstream ss;
	ss << "(";
	while (nodePtr->next) {
		ss << nodePtr->data << ")──(";
		nodePtr = nodePtr->next;
	}
	ss << nodePtr->data << ")";
	return ss.str();
}