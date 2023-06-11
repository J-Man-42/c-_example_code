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


// Get the number of elements in the list.
template <class T>
uint LinkedList<T>::size() const {
	return length;
}