#include "linked_list.h"


// The constructor.
template <class T>
LinkedList<T>::LinkedList() {
	head = tail = nullptr;
	length = 0;
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