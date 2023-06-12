#include "linked_list.h"


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
void LinkedList<T>::add(T element) {
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
void LinkedList<T>::insert(uint index, T element) {
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
	if (true) {
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



template <class T>
T LinkedList<T>::remove(T element) {}



template <class T>
T LinkedList<T>::removeAt(uint index) {}



// Get the number of elements in the list.
template <class T>
uint LinkedList<T>::size() const {
	return length;
}