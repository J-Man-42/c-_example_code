#include <iostream>
#include "linked_list.h"
using namespace std;


// The constructor.
template<class T>
LinkedList<T>::LinkedList() {
	head = tail = nullptr;
	length = 0;
}


// The copy constructor.
template<class T>
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
template<class T>
LinkedList<T>::~LinkedList() {
	clear();
}



// Overload the subscript operator.
template<class T>
T& LinkedList<T>::operator[](const uint index) {
	return findIndex(index)->data;
}



// Add an element to the end of the list.
template<class T>
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
template<class T>
void LinkedList<T>::clear() {
	length = 0;

	// Check if head is not null.
	if (!isEmpty()) {

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



// Returns the first element in the list.
template<class T>
T& LinkedList<T>::first() {

	// Throw an error if the list is empty.
	if (isEmpty()) {
		throw "Error! No elements in the list";
	}

	// Returns the element at head.
	return head->data;
}



// Returns the element at the given index.
template<class T>
T& LinkedList<T>::get(const uint index) {
	return (*this)[index];
}



// Insert element at the specified index.
template<class T>
void LinkedList<T>::insert(const uint index, const T element) {
	Node<T>* newNode = new Node<T>(element);

	// If empty list, assign as head and tail.
	if (isEmpty()) {
		head = tail = newNode;
	}

	// See if element is simply appended to the end.
	else if (index >= length) {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}

	// See if element should be added to the front.
	else if (index == 0) {
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
	}

	// It is somewhere in the middle.
	else {
		Node<T>* nodePtr = findIndex(index);
		newNode->next = nodePtr;
		newNode->prev = nodePtr->prev;
		newNode->next->prev = newNode;
		newNode->prev->next = newNode;
	}

	// Increment the length.
	length++;
}



// Returns true if head is null.
template<class T>
bool LinkedList<T>::isEmpty() const {
	return head == nullptr;
}




// Returns the last element in the list.
template<class T>
T& LinkedList<T>::last() {
	
	// Throw an error if the list is empty.
	if (isEmpty()) {
		throw "Error! No elements in the list";
	}

	// Returns the element at head.
	return tail->data;
}



// Elegantly prints the contents of the list.
template<class T>
void LinkedList<T>::print() {

	// Do nothing if empty list.
	if (isEmpty()) {
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
template<class T>
void LinkedList<T>::remove(const T element) {
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

	// Decrement the length.
	length--;
}



// Removes the element at the given index.
template<class T>
T& LinkedList<T>::removeAt(const uint index) {

	// Throw error if index out of bounds.
	if (index >= length) {
		throw "Error! Index out of bounds";
	}

	// Find correct node and get the element.
	Node<T>* nodePtr = findIndex(index);
	T& element = nodePtr->data;

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



// Set the element at the given index.
template<class T>
void LinkedList<T>::set(const uint index, const T element) {

	// If index out of bounds, add to the end.
	if (index >= length) {
		add(element);
		return;
	}

	// Find the node and set the element.
	Node<T>* nodePtr = findIndex(index);
	nodePtr->data = element;
}



// Get the number of elements in the list.
template<class T>
uint LinkedList<T>::size() const {
	return length;
}



// Returns a sub list from start to end.
template<class T>
LinkedList<T>* LinkedList<T>::subList(const uint start, const uint end) {

	// Throw error if invalid index.
	if (start >= end || start >= length || end > length) {
		throw "Error! Index out of bounds";
	}

	// Create the new list.
	LinkedList<T>* list = new LinkedList();

	// Find the starting point.
	Node<T>* nodePtr = findIndex(start);

	// Copy elements from start to end.
	for (size_t i = start; i < end; i++) {
		list->add(nodePtr->data);
		nodePtr = nodePtr->next;
	}

	// Return the sublist.
	return list;
}



// Converts the list into a dynamic array.
template<class T>
T* LinkedList<T>::toDynamicArray() {

	// Throw an error if the list is empty.
	if (isEmpty()) {
		throw "Error! No elements in the list";
	}

	// Returns array of list length.
	return toDynamicArray(length);
}


// Converts the list into a dynamic array of the given size.
template<class T>
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



// Find the node corresponding to the given index.
template<class T>
Node<T>* LinkedList<T>::findIndex(const uint index) {
	Node<T>* nodePtr;

	// Throw error if index out of bounds.
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

	// Return the element.
	return nodePtr;
}
