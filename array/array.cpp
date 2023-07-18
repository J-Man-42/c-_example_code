#include <iostream>
#include <sstream>
#include "array.h"
using namespace std;


// The constructor.
template<class T>
Array<T>::Array(const unsigned capacity) {
	this->length = 0;
	this->capacity = capacity;
	this->array = new T[capacity];
}


// The copy constructor.
template<class T>
Array<T>::Array(const Array<T>& other) {

	// If the same array has been provided, do nothing.
	if (this == &other) {
		return;
	}

	// Copy length, capacity, and all array elements.
	this->length = other.length;
	this->capacity = other.capacity;
	this->array = new T[capacity];
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
		
		// Copy length, capacity, and all array elements.
		this->capacity = other.capacity;
		this->length = other.length;
		this->array = new T[capacity];
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
	unsigned newCapacity = (length == capacity ? capacity+100 : capacity);
	Array<T> newArray(newCapacity);
	newArray.length = length+1;

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

	// Calculate capacity of new array.
	unsigned newLength = this->size() + other.size();
	unsigned newCapacity = updateCapacity(newLength);

	// Create new array.
	Array<T> newArray(newCapacity);
	newArray.length = newLength;

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

	// If array at max capacity, grow array by 100.
	if (length == capacity) {
		capacity += 100;
		T* temp = new T[capacity];

		// Copy all elements from this array to temporary array.
		for (unsigned i = 0; i < length; i++) {
			temp[i] = this->array[i];
		}

		// Update this array.
		delete [] this->array;
		this->array = temp;
	}

	// Add new element to array and update its length.
	array[length] = element;
	length++;
	return *this;
}


// Add the other array to the end of this array.
template<class T>
Array<T>& Array<T>::operator+=(const Array<T>& other) {

	// Calculate new capacity.
	unsigned newLength = this->size() + other.size();
	unsigned newCapacity = updateCapacity(newLength);

	// If new capacity is greater than before, grow array.
	if (newCapacity > this->capacity) {
		this->capacity = newCapacity;
		T* temp = new T[capacity];

		// Copy all elements from this array to temporary array.
		for (unsigned i = 0; i < length; i++) {
			temp[i] = array[i];
		}

		// Update this array.
		delete [] array;
		array = temp;
	}

	// Copy all elements from other array to this array.
	for (unsigned i = length, j = 0; j < other.size(); i++, j++) {
		array[i] = other.array[j];
	}

	// Update length of this array.
	this->length = newLength;
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
	T* temp = this->array;

	// If array at max capacity, grow array by 100.
	if (length == capacity) {
		capacity += 100;
		temp = new T[capacity];
	}

	// Copy/shift all elements from this array to temporary array.
	for (unsigned i = length; i > 0; i--) {
		temp[i] = array[i-1];
	}

	// If needed, update this array.
	if (temp != array) {
		delete [] array;
		array = temp;
	}

	// Insert element at beginning of array.
	array[0] = element;
	length++;
}



// Insert element at the specified index.
template<class T>
void Array<T>::insertAt(const int signedIndex, const T element) {
	T* temp = this->array;

	// Get the positive array index.
	unsigned index = handleNegativeIndex(signedIndex);

	// If array at max capacity, grow array by 100.
	if (length == capacity) {
		capacity += 100;
		temp = new T[capacity];

		// Copy all elements up to the insert index.
		for (unsigned i = 0; i < index; i++) {
			temp[i] = array[i];
		}
	}

	// Copy/shift up all elements after the insert index.
	for (unsigned i = length; i > index; i--) {
		temp[i] = array[i-1];
	}

	// If needed, update this array.
	if (temp != array) {
		delete [] array;
		array = temp;
	}

	// Insert element at the correct index.
	array[index] = element;
	length++;
}



// Returns the capacity of the array.
template<class T>
unsigned Array<T>::maxCapacity() const {
	return capacity;
}



// Removes the first instance of the given element.
template<class T>
void Array<T>::remove(const T element) {
	T* temp = this->array;

	// Find index of element and throw error if not found.
	unsigned index = indexOf(element);
	if (index > length) {
		throw "Error! Element not in array";
	}

	// If array 150 items below capacity, shrink array.
	if (capacity - length >= 150) {
		capacity -= 100;
		temp = new T[capacity];

		// Copy all elements up to the remove index.
		for (unsigned i = 0; i < index; i++) {
			temp[i] = array[i];
		}
	}

	// Shift down all elements after the remove index.
	for (unsigned i = index; i < length; i++) {
		temp[i] = array[i+1];
	}

	// Update the length.
	length--;
}



// Removes the element at the given index.
template<class T>
T Array<T>::removeAt(const int signedIndex) {
	T* temp = this->array;

	// Get the positive array index.
	unsigned index = handleNegativeIndex(signedIndex);

	// Save the element to remove.
	T element = array[index];

	// If array 150 items below capacity, shrink array.
	if (capacity - length >= 150) {
		capacity -= 100;
		temp = new T[capacity];

		// Copy all elements up to the remove index.
		for (unsigned i = 0; i < index; i++) {
			temp[i] = array[i];
		}
	}

	// Shift down all elements after the remove index.
	for (unsigned i = index; i < length; i++) {
		array[i] = array[i+1];
	}

	// Update the length and return the removed element.
	length--;
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
	Array newArray(capacity);
	newArray.length = this->length;
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



// Return an updated array capacity based on the length.
template<class T>
unsigned Array<T>::updateCapacity(const unsigned length) {
	unsigned newCapacity = length;
	if (length % 100 != 0) {
		newCapacity += 100 - (length % 100);
	}
	return newCapacity;
}
