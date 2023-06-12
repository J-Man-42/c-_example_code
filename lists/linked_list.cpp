#include <iostream>
#include "linked_list.h"
using namespace std;


// The constructor.
template <class T>
LinkedList<T>::LinkedList() {
	head = tail = nullptr;
	length = 0;
}


// The copy constructor.
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) {
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
			this->tail->next->prev = this->tail;
			this->tail = this->tail->next;
			otherPtr = otherPtr->next;
		}
	}
}


// The destructor.
template <class T>
LinkedList<T>::~LinkedList() {
	clear();
}



// Add an element to the end of the list.
template <class T>
void LinkedList<T>::add(const T element) {
	length++;

	// See if it's the first element.
	if (!tail) {
		head = tail = new Node<T>(element);
	}

	// Otherwise, add to the end.
	else {
		tail->next = new Node<T>(element);
		tail->next->prev = tail;
		tail = tail->next;
	}
}



// Delete all entries in the list.
template <class T>
void LinkedList<T>::clear() {
	length = 0;

	// Check if head is not null.
	if (head) {

		// Delete all nodes except the last.
		while (head != tail) {
			head = head->next;
			delete head->prev;
		}

		// Delete the final node.
		delete head;
		head = tail = nullptr;
	}
}



// Insert element at the specified index.
template <class T>
void LinkedList<T>::insert(const uint index, const T element) {
	Node<T>* newNode = new Node<T>(element);
	length++;

	// If empty list, assign as head and tail.
	if (!head) {
		head = tail = newNode;
		return;
	}

	// See if element is simply appended to the end.
	if (index >= length-1) {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
		return;
	}

	// See if element should be added to the front.
	if (index == 0) {
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
		return;
	}

	// See if index is closer to head.
	Node<T>* nodePtr;
	if (length-index-1 >= index) {
		nodePtr = head;
		for (size_t i = 0; i < index; i++) {
			nodePtr = nodePtr->next;
		}
	}

	// Otherwise, index is closer to tail.
	else {
		nodePtr = tail;
		for (size_t i = length-2; i > index; i--) {
			nodePtr = nodePtr->prev;
		}
	}

	// Create and link the new node.
	newNode->next = nodePtr;
	newNode->prev = nodePtr->prev;
	newNode->next->prev = newNode;
	newNode->prev->next = newNode;
}



// Elegantly prints the contents of the list.
template <class T>
void LinkedList<T>::print() {

	// Do nothing if empty list.
	if (!head) {
		return;
	}

	// Iterate through all elements.
	Node<T>* nodePtr = head;
	cout << "(";
	while (nodePtr->next) {
		cout << nodePtr->data << ")──(";
		nodePtr = nodePtr->next;
	}
	cout << nodePtr->data << ")" << endl;
}



// Removes the first instance of the given element.
template <class T>
T LinkedList<T>::remove(const T element) {
	bool found = false;
	Node<T>* nodePtr = head;

	// Iterate until null or element found.
	while (nodePtr) {
		if (nodePtr->data == element) {
			found = true;
			break;
		}
		nodePtr = nodePtr->next;
	}

	// If not found, throw error.
	if (!found) {
		throw "Error! Element '"+to_string(element)+"' not found";
	}

	// The only element.
	if (head == tail) {
		delete head;
		head = tail = nullptr;
	}

	// The element is the first element.
	else if (head == nodePtr) {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
	}

	// The element is the last element.
	else if (tail == nodePtr) {
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
	}

	// Otherwise, it is somewhere in the middle.
	else {
		nodePtr->prev->next = nodePtr->next;
		nodePtr->next->prev = nodePtr->prev;
		delete nodePtr;
	}

	// Return the element.
	length--;
	return element;
}



// Removes the element at the given index.
template <class T>
T LinkedList<T>::removeAt(const uint index) {
	Node<T>* nodePtr;
	T element;

	// If not found, throw error.
	if (index >= length) {
		throw "Error! Index out of bounds";
	}

	// See if index is closer to head.
	if (length-index >= index) {
		nodePtr = head;
		for (size_t i = 0; i < index; i++) {
			nodePtr = nodePtr->next;
		}
	}

	// Otherwise, index is closer to tail.
	else {
		nodePtr = tail;
		for (size_t i = length-1; i > index; i--) {
			nodePtr = nodePtr->prev;
		}
	}

	// Assign the element to return.
	element = nodePtr->data;

	// The only element.
	if (head == tail) {
		delete head;
		head = tail = nullptr;
	}

	// The element is the first element.
	else if (head == nodePtr) {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
	}

	// The element is the last element.
	else if (tail == nodePtr) {
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
	}

	// Otherwise, it is somewhere in the middle.
	else {
		nodePtr->prev->next = nodePtr->next;
		nodePtr->next->prev = nodePtr->prev;
		delete nodePtr;
	}

	// Return the element.
	length--;
	return element;
}



// Get the number of elements in the list.
template <class T>
uint LinkedList<T>::size() const {
	return length;
}



// Converts the list into a dynamic array.
template <class T>
T* LinkedList<T>::toDynamicArray() {

	// Throw an error if the list is empty.
	if (!head) {
		throw "Error! No elements in the list";
	}

	// Returns array of list length.
	return toDynamicArray(length);
}


// Converts the list into a dynamic array of the given size.
template <class T>
T* LinkedList<T>::toDynamicArray(const uint SIZE) {
	
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