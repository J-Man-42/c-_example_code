#include <iostream>
#include "random.h"
using namespace std;


// Main testing function.
int main() {

	// Set the minimum and maximum thresholds.
	int minInt = -5;
	int maxInt = 9;
	uint minUint = 2;
	uint maxUint = 19;
	double minDouble = 2.0;
	double maxDouble = 5.0;
	const size_t SIZE = 10;

	// Generate random values.
	cout << "\nrandInt("<<minInt<<", "<<maxInt<<") = ";
	cout << randInt(minInt, maxInt) << endl;
	cout << "randUint("<<minUint<<", "<<maxUint<<") = ";
	cout << randInt(minUint, maxUint) << endl;
	cout << "randDouble("<<minDouble<<", "<<maxDouble<<") = ";
	cout << randDouble(minDouble, maxDouble) << endl;


	// Generate random arrays.
	int* intArray = randIntArray(SIZE, minInt, maxInt);
	uint* uintArray = randUintArray(SIZE, minUint, maxUint);
	double* doubleArray = randDoubleArray(SIZE, minDouble, maxDouble);

	// Print all arrays.
	cout << "\nrandIntArray():" << endl;
	for (size_t i = 0; i < SIZE; i++) {
		cout << intArray[i] << "  ";
	}
	cout << "\n\nrandUintArray():" << endl;
	for (size_t i = 0; i < SIZE; i++) {
		cout << uintArray[i] << "  ";
	}
	cout << "\n\nrandDoubleArray():" << endl;
	for (size_t i = 0; i < SIZE; i++) {
		cout << doubleArray[i] << "  ";
	}
	cout << endl;

	// Shuffle all arrays.
	shuffle(intArray, SIZE);
	shuffle(uintArray, SIZE);
	shuffle(doubleArray, SIZE);
	cout << "\n\nAfter shuffling:" << endl;

	// Print all arrays.
	cout << "\nrandIntArray():" << endl;
	for (size_t i = 0; i < SIZE; i++) {
		cout << intArray[i] << "  ";
	}
	cout << "\n\nrandUintArray():" << endl;
	for (size_t i = 0; i < SIZE; i++) {
		cout << uintArray[i] << "  ";
	}
	cout << "\n\nrandDoubleArray():" << endl;
	for (size_t i = 0; i < SIZE; i++) {
		cout << doubleArray[i] << "  ";
	}
	cout << endl;

	// Delete dynamic arrays.
	delete [] intArray;
	delete [] uintArray;
	delete [] doubleArray;

	// Return.
	return 0;
}
