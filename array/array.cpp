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



// Returns a copied array with the element added to the end.
template<class T>
Array<T> Array<T>::operator+(const T element) {

	// Create new array.
	Array<T> newArray(length+1);

	// Copy all elements from this array to new array.
	for (unsigned i = 0; i < length; i++) {
		newArray[i] = array[i];
	}

	// Add final element and return new array.
	newArray[-1] = element;
	return newArray;
}


// Returns a copied array with the array added to the end.
template<class T>
Array<T> Array<T>::operator+(const Array<T>& other) {

	// Create new array.
	Array<T> newArray(this->size()+other.size());

	// Copy all elements from this array to new array.
	for (unsigned i = 0; i < this->size(); i++) {
		newArray[i] = this->array[i];
	}

	// Copy all elements from other array to new array.
	for (unsigned i = this->size(), j = 0; j < other.size(); i++, j++) {
		newArray[i] = other.array[j];
	}

	// Return the new array.
	return newArray;
}


// Add the element to the end of the array.
template<class T>
Array<T>& Array<T>::operator+=(const T element) {

	// Create temporary array.
	T* temp = new T[length+1];

	// Copy all elements from this array to temporary array.
	for (unsigned i = 0; i < length; i++) {
		temp[i] = this->array[i];
	}

	// Add final element.
	temp[length] = element;

	// Update this array and length.
	delete [] this->array;
	this->array = temp;
	this->length++;
	return *this;
}


// Add the other array to the end of this array.
template<class T>
Array<T>& Array<T>::operator+=(const Array<T>& other) {

	// Create temporary array.
	T* temp = new T[this->size()+other.size()];

	// Copy all elements from this array to temporary array.
	for (unsigned i = 0; i < this->size(); i++) {
		temp[i] = this->array[i];
	}

	// Copy all elements from other array to temporary array.
	for (unsigned i = this->size(), j = 0; j < other.size(); i++, j++) {
		temp[i] = other.array[j];
	}

	// Update this array and length.
	delete [] this->array;
	this->array = temp;
	this->length += other.length;
	return *this;
}



// Append element to the end of the array.
template<class T>
void Array<T>::append(const T element) {
	*this += element;
}



// Returns a hard copy of this array.
template<class T>
Array<T> Array<T>::clone() {
	return Array<T>(*this);
}



// Returns true if element in array.
template<class T>
bool Array<T>::contains(const T element) const {
	for (unsigned i = 0; i < length; i++) {
		if (array[i] == element) {
			return true;
		}
	}
	return false;
}



// Returns the element at the given index.
template<class T>
T& Array<T>::get(const int index) {
	return (*this)[index];
}



// Returns the array index of the given element.
template<class T>
int Array<T>::indexOf(const T element) {
	for (unsigned i = 0; i < length; i++) {
		if (array[i] == element) {
			return i;
		}
	}

	// Returns -1 if not found.
	return -1;
}



// Insert element at beginning of array.
template<class T>
void Array<T>::insert(const T element) {

	// Create temporary array.
	T* temp = new T[length+1];

	// Add element to beginning of temporary array.
	temp[0] = element;

	// Copy all elements from this array to temporary array.
	for (unsigned i = 0, j = 1; i < length; i++, j++) {
		temp[j] = array[i];
	}

	// Update this array and length.
	delete [] array;
	array = temp;
	length++;
}



// Insert element at the specified index.
template<class T>
void Array<T>::insertAt(const int signedIndex, const T element) {

	// Create temporary array.
	T* temp = new T[length+1];

	// Get the positive array index.
	unsigned index = handleNegativeIndex(signedIndex);

	// Copy all elements up to the insert index.
	for (unsigned i = 0; i < index; i++) {
		temp[i] = array[i];
	}

	// Insert the element.
	temp[index] = element;

	// Copy all elements after the insert index.
	for (unsigned i = index, j = index+1; i < length; i++, j++) {
		temp[j] = array[i];
	}

	// Update this array and length.
	delete [] array;
	array = temp;
	length++;
}



// Removes the first instance of the given element.
template<class T>
void Array<T>::remove(const T element) {

	// Find index of element and throw error if not found.
	unsigned index = indexOf(element);
	if (index > length) {
		throw "Error! Element not in array";
	}

	// Create temporary array.
	T* temp = new T[length-1];

	// Copy all elements up to the remove index.
	for (unsigned i = 0; i < index; i++) {
		temp[i] = array[i];
	}

	// Copy all elements after the remove index.
	for (unsigned i = index+1, j = index; i < length; i++, j++) {
		temp[j] = array[i];
	}

	// Update this array and length.
	delete [] array;
	array = temp;
	length--;
}



// Removes the element at the given index.
template<class T>
T Array<T>::removeAt(const int signedIndex) {

	// Get the positive array index.
	unsigned index = handleNegativeIndex(signedIndex);

	// Create temporary array.
	T* temp = new T[length-1];

	// Save the element to remove.
	T element = array[index];

	// Copy all elements up to the remove index.
	for (unsigned i = 0; i < index; i++) {
		temp[i] = array[i];
	}

	// Copy all elements after the remove index.
	for (unsigned i = index+1, j = index; i < length; i++, j++) {
		temp[j] = array[i];
	}

	// Update this array and length.
	delete [] array;
	array = temp;
	length--;

	// Return the removed element.
	return element;
}



// Reverse this array.
template<class T>
void Array<T>::reverse() {
	for (unsigned i = 0, j = length-1; i < j; i++, j--) {
		swap(array[i], array[j]);
	}
}



// Return a reversed version of this array.
template<class T>
Array<T> Array<T>::reversed() {
	Array newArray(length);
	for (unsigned i = 0, j = length-1; i < length; i++, j--) {
		newArray[i] = array[j];
	}
	return newArray;
}



// Set the element at the given index.
template<class T>
void Array<T>::set(const int index, const T element) {
	(*this)[index] = element;
}



// Returns the size of the array.
template<class T>
unsigned Array<T>::size() const {
	return length;
}



// Returns a sub array from start to end.
template<class T>
Array<T>* Array<T>::subArray(const unsigned start, const unsigned end) {

	// Swap indices if start is greater than end.
	if (start > end) {
		throw "Error! Start index > end index";
	}

	// Throw error if invalid index.
	if (start >= length || end > length) {
		throw "Error! Index out of bounds";
	}

	// Create the new array.
	Array<T>* newArray = new Array<T>(end-start);

	// Copy elements from start to end.
	for (unsigned i = start, j = 0; i < end; i++, j++) {
		newArray->set(j, array[i]);
	}

	// Return the sub array.
	return newArray;
}



// Returns the string representation of the array.
template<class T>
string Array<T>::toString() {

	// Iterate through all elements.
	stringstream ss;
	ss << "[";

	// Print first element.
	if (length > 0) {
		ss << array[0];
	}
	// Print second and remaining elements.
	for (unsigned i = 1; i < length; i++) {
		ss << ", " << array[i];
	}

	// Close bracket and return the string.
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
