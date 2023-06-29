#include <iostream>
#include "random.h"
using namespace std;


// Main testing function.
int main() {

	// Set the minimum and maximum thresholds.
	int minInt = -10;
	int maxInt = 10;
	uint minUint = 0;
	uint maxUint = 20;
	double minDouble = 0.0;
	double maxDouble = 1.0;
	const size_t SIZE = 14;

	// Generate random values.
	cout << "\nRandom values:" << endl;
	cout << "========================================" << endl;
	cout << "randInt("<<minInt<<", "<<maxInt<<") = ";
	cout << randInt(minInt, maxInt) << endl;
	cout << "randUint("<<minUint<<", "<<maxUint<<") = ";
	cout << randInt(minUint, maxUint) << endl;
	cout << "randDouble("<<minDouble<<", "<<maxDouble<<") = ";
	cout << randDouble(minDouble, maxDouble) << endl;
	cout << "randChar(letter) = '";
	cout << randChar('l') << "'\n";
	cout << "randChar(number) = '";
	cout << randChar('n') << "'\n";
	cout << "randChar(symbol) = '";
	cout << randChar('s') << "'\n";
	cout << "randChar(any) = '";
	cout << randChar() << "'\n";
	cout << "========================================" << endl;


	// Generate random arrays.
	int* intArray = randIntArray(SIZE, minInt, maxInt);
	uint* uintArray = randUintArray(SIZE, minUint, maxUint);
	double* doubleArray = randDoubleArray(SIZE, minDouble, maxDouble);
	char* letterArray = randCharArray(SIZE, 'l');
	char* numberArray = randCharArray(SIZE, 'n');
	char* symbolArray = randCharArray(SIZE, 's');
	char* charArray = randCharArray(SIZE);

	// Print all arrays.
	cout << "\n\nRandom arrays:" << endl;
	cout << "==============" << endl;
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
	cout << "\n\nrandCharArray(number):" << endl;
	for (size_t i = 0; i < SIZE; i++) {
		cout << "'"<<numberArray[i]<<"'" << "  ";
	}
	cout << "\n\nrandCharArray(letter):" << endl;
	for (size_t i = 0; i < SIZE; i++) {
		cout << "'"<<letterArray[i]<<"'" << "  ";
	}
	cout << "\n\nrandCharArray(symbol):" << endl;
	for (size_t i = 0; i < SIZE; i++) {
		cout << "'"<<symbolArray[i]<<"'" << "  ";
	}
	cout << "\n\nrandCharArray(any):" << endl;
	for (size_t i = 0; i < SIZE; i++) {
		cout << "'"<<charArray[i]<<"'" << "  ";
	}
	cout << endl;

	// Shuffle all arrays.
	shuffle(intArray, SIZE);
	shuffle(uintArray, SIZE);
	shuffle(doubleArray, SIZE);
	shuffle(numberArray, SIZE);
	shuffle(letterArray, SIZE);
	shuffle(symbolArray, SIZE);
	shuffle(charArray, SIZE);

	// Print all arrays.
	cout << "\n\nAfter shuffling:" << endl;
	cout << "================" << endl;
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
	cout << "\n\nrandCharArray(number):" << endl;
	for (size_t i = 0; i < SIZE; i++) {
		cout << "'"<<numberArray[i]<<"'" << "  ";
	}
	cout << "\n\nrandCharArray(letter):" << endl;
	for (size_t i = 0; i < SIZE; i++) {
		cout << "'"<<letterArray[i]<<"'" << "  ";
	}
	cout << "\n\nrandCharArray(symbol):" << endl;
	for (size_t i = 0; i < SIZE; i++) {
		cout << "'"<<symbolArray[i]<<"'" << "  ";
	}
	cout << "\n\nrandCharArray(any):" << endl;
	for (size_t i = 0; i < SIZE; i++) {
		cout << "'"<<charArray[i]<<"'" << "  ";
	}
	cout << endl;

	// Delete dynamic arrays.
	delete [] intArray;
	delete [] uintArray;
	delete [] doubleArray;
	delete [] letterArray;
	delete [] numberArray;
	delete [] symbolArray;
	delete [] charArray;

	// Return.
	return 0;
}
