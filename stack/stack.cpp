#include <iostream>
#include <sstream>
#include "stack.h"
using namespace std;


// The constructor.
template<class T>
Stack<T>::Stack() {
	head = nullptr;
	length = 0;
}


// The copy constructor.
template<class T>
Stack<T>::Stack(const Stack<T>& other) {

	// If the two stacks are equal, do nothing.
	if (this == &other) {
		return;
	}

	// Set the initial parameters.
	this->length = other.length;
	this->head = nullptr;

	// Copy other.head if not null.
	if (other.head) {
		this->head = new StackNode<T>(other.head->data);

		// Copy all remaining elements.
		StackNode<T>* otherPtr = other.head->next;
		StackNode<T>* thisPtr = this->head;
		while (otherPtr) {
			thisPtr->next = new StackNode<T>(otherPtr->data);
			thisPtr = thisPtr->next;
			otherPtr = otherPtr->next;
		}
	}
}


// Construct a Stack from the given array.
template<class T>
Stack<T>::Stack(const T array[], const uint SIZE) {
	this->head = nullptr;
	this->length = 0;
	for (int i = SIZE-1; i >= 0; i--) {
		this->push(array[i]);
	}
}


// The destructor.
template<class T>
Stack<T>::~Stack() {
	clear();
}



// Output stream the stack to string.
template<class T>
ostream& operator<<(ostream& out, Stack<T>& stack) {
	out << stack.toString();
	return out;
}



// Overload the assignment operator.
template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {

	// Only make changes if this and other are different stacks.
	if (this != &other) {
		this->clear();
		this->length = other.length;

		// Copy other.head if not null.
		if (other.head) {
			this->head = new StackNode<T>(other.head->data);

			// Copy all remaining elements.
			StackNode<T>* otherPtr = other.head->next;
			StackNode<T>* thisPtr = this->head;
			while (otherPtr) {
				thisPtr->next = new StackNode<T>(otherPtr->data);
				thisPtr = thisPtr->next;
				otherPtr = otherPtr->next;
			}
		}
	}

	return *this;
}



// Returns a copied stack with element added to the end.
template<class T>
Stack<T> Stack<T>::operator+(const T element) {
	Stack<T> stack = this->clone();
	stack.push(element);
	return stack;
}



// Returns a copied stack with the other stack added to the end.
template<class T>
Stack<T> Stack<T>::operator+(const Stack<T>& other) {
	Stack<T> topStack;
	Stack<T> bottomStack;
	StackNode<T>* nodePtr = nullptr;

	// Copy other.head if not null.
	if (other.head) {
		topStack.length = other.length;
		topStack.head = new StackNode<T>(other.head->data);

		// Copy all remaining elements.
		nodePtr = topStack.head;
		StackNode<T>* otherPtr = other.head->next;
		while (otherPtr) {
			nodePtr->next = new StackNode<T>(otherPtr->data);
			nodePtr = nodePtr->next;
			otherPtr = otherPtr->next;
		}
	}

	// Append the stacks and return the resulting stack.
	bottomStack = this->clone();
	if (nodePtr) {
		nodePtr->next = bottomStack.head;
		topStack.length += bottomStack.length;
		bottomStack.head = nullptr;
		return topStack;
	}
	return bottomStack;
}



// Add the element to the end of this stack.
template<class T>
Stack<T>& Stack<T>::operator+=(const T element) {
	this->push(element);
	return *this;
}



// Add the stack to the end of this stack.
template<class T>
Stack<T>& Stack<T>::operator+=(const Stack<T>& other) {
	Stack<T> topStack;
	StackNode<T>* nodePtr = nullptr;

	// Copy other.head if not null.
	if (other.head) {
		topStack.length = other.length;
		topStack.head = new StackNode<T>(other.head->data);

		// Copy all remaining elements.
		nodePtr = topStack.head;
		StackNode<T>* otherPtr = other.head->next;
		while (otherPtr) {
			nodePtr->next = new StackNode<T>(otherPtr->data);
			nodePtr = nodePtr->next;
			otherPtr = otherPtr->next;
		}
	}

	// Append the stacks and return the resulting stack.
	if (nodePtr) {
		nodePtr->next = this->head;
		this->head = topStack.head;
		this->length += topStack.length;
		topStack.head = nullptr;
	}
	return *this;
}



// Delete all entries in the stack.
template<class T>
void Stack<T>::clear() {
	length = 0;

	// Check if head is not null.
	if (!isEmpty()) {

		// Delete all nodes except.
		StackNode<T>* nodePtr = head;
		while (head) {
			head = head->next;
			delete nodePtr;
			nodePtr = head;
		}
	}
}



// Returns a hard copy of this stack.
template<class T>
Stack<T> Stack<T>::clone() {
	return Stack<T>(*this);
}



// Returns true if the element is in the stack.
template<class T>
bool Stack<T>::contains(const T element) const {
	StackNode<T>* nodePtr = head;
	while (nodePtr) {
		if (nodePtr->data == element) {
			return true;
		}
		nodePtr = nodePtr->next;
	}
	return false;
}



// Returns true if head is null.
template<class T>
bool Stack<T>::isEmpty() const {
	return head == nullptr;
}



// Remove the element at head.
template<class T>
T Stack<T>::pop() {

	// Throw an error if the stack is empty.
	if (isEmpty()) {
		throw "Error! The stack is empty";
	}

	// Update length and extract the element.
	T element = head->data;
	length--;

	// Delete top of stack.
	StackNode<T>* nodePtr = head;
	head = head->next;
	delete nodePtr;

	// Return the element.
	return element;
}



// Add an element to the back of the stack.
template<class T>
void Stack<T>::push(const T element) {
	length++;

	// See if it's the first element.
	if (isEmpty()) {
		head = new StackNode<T>(element);
	}

	// Otherwise, add to the top.
	else {
		StackNode<T>* nodePtr = new StackNode<T>(element);
		nodePtr->next = head;
		head = nodePtr;
	}
}



// Get the number of elements in the stack.
template<class T>
uint Stack<T>::size() const {
	return length;
}



// Returns the top the stack.
template<class T>
T& Stack<T>::top() {

	// Throw an error if the stack is empty.
	if (isEmpty()) {
		throw "Error! The stack is empty";
	}

	// Returns the element at head.
	return head->data;
}



// Converts the stack into a dynamic array.
template<class T>
T* Stack<T>::toDynamicArray() {

	// Throw an error if the stack is empty.
	if (isEmpty()) {
		throw "Error! The stack is empty";
	}

	// Returns array of stack's length.
	return toDynamicArray(length);
}


// Converts the stack into a dynamic array of the given size.
template<class T>
T* Stack<T>::toDynamicArray(const uint SIZE) {

	// Copy all elements to the new array.
	T* array = new T[SIZE];
	StackNode<T>* nodePtr = head;
	size_t limit = (length > SIZE ? SIZE : length);
	for (size_t i = 0; i < limit; i++) {
		array[i] = nodePtr->data;
		nodePtr = nodePtr->next;
	}

	// Return the final array.
	return array;
}



// Returns the string representation of the stack.
template<class T>
string Stack<T>::toString() {

	// Return empty parenthesis if empty stack.
	if (isEmpty()) {
		return "()";
	}

	// Iterate through all elements.
	StackNode<T>* nodePtr = head;
	stringstream ss;
	ss << "(";
	while (nodePtr->next) {
		ss << nodePtr->data << ")──(";
		nodePtr = nodePtr->next;
	}
	ss << nodePtr->data << ")";
	return ss.str();
}
