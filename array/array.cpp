#include <iostream>
#include <sstream>
#include "array.h"
using namespace std;


// The constructor.
template<class T>
Array<T>::Array(const unsigned length) {
	this->length = length;
	this->array = new T[length];
}


// The copy constructor.
template<class T>
Array<T>::Array(const Array<T>& other) {

	// If the same array has been provided, do nothing.
	if (this == &other) {
		return;
	}

	// Copy length and all array elements.
	this->length = other.length;
	this->array = new T[length];
	for (unsigned i = 0; i < length; i++) {
		this->array[i] = other.array[i];
	}
}


// The destructor.
template<class T>
Array<T>::~Array() {
	delete [] array;
	array = nullptr;
}



// Output stream the array to string.
template<class T>
ostream& operator<<(ostream& out, Array<T>& array) {
	out << array.toString();
	return out;
}



// Overload the assignment operator.
template<class T>
Array<T>& Array<T>::operator=(const Array<T>& other) {

	// Only make changes if this and other are different arrays.
	if (this != &other) {
		delete [] this->array;
		
		// Copy length and all array elements.
		this->length = other.length;
		this->array = new T[length];
		for (unsigned i = 0; i < length; i++) {
			this->array[i] = other.array[i];
		}
	}

	return *this;
}



// Overload the subscript operator.
template<class T>
T& Array<T>::operator[](const int index) {
	return array[handleNegativeIndex(index)];
}



// Returns the string representation of the array.
template<class T>
string Array<T>::toString() {

	// Iterate through all elements.
	stringstream ss;
	ss << "[";
	if (length > 0) {
		ss << array[0];
	}
	for (unsigned i = 1; i < length; i++) {
		ss << ", " << array[i];
	}
	ss << "]";
	return ss.str();
}



// Return the positive index equivalent.
template<class T>
unsigned Array<T>::handleNegativeIndex(const int index) {
	int signedLength = length;
	
	// Throw error if index out of bounds.
	if (index >= signedLength || index < -signedLength) {
		throw "Error! Index out of bounds";
	}

	// Return adjusted index otherwise.
	if (index < 0)
		return length + index;
	return index;
}
