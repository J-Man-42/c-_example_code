#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iostream>
#include "random.h"


// The static seed value.
static uint long seed = 0;


// Update the random seed to epoch time.
void updateSeed() {
	if (seed == 0) {
		seed = time(0);
		srand(seed);
	}
}


// Generate a random signed integer between minValue and maxValue.
int randInt(int minValue, int maxValue) {
	updateSeed();
	return rand() % (maxValue - minValue + 1) + minValue;
}


// Generate a random unsigned integer between minValue and maxValue.
uint randUint(uint minValue, uint maxValue) {
	updateSeed();
	return rand() % (maxValue - minValue + 1) + minValue;
}


// Generate a random double between minValue and maxValue.
double randDouble(double minValue, double maxValue) {
	updateSeed();
	double randValue = double(rand()) / RAND_MAX;
    return randValue * (maxValue - minValue) + minValue;
}


// Generates a random char based on type.
// Types include letters (l), numbers (n), and symbols (s).
char randChar(char type) {
	updateSeed();
	static short startLetter[2] = {65, 97};
	static short startSymbol[4] = {33, 58, 91, 123};
	static short endSymbol[4] = {47, 64, 96, 127};
	short start, index;

	// Switch statement for type.
	switch (type) {

	// Letter.
	case 'l':
		start = startLetter[randUint(0, 1)];
		return randUint(start, start+25);

	// Number.
	case 'n':
		return randUint(48, 57);

	// Symbol
	case 's':
		index = randUint(0, 3);
		return randUint(startSymbol[index], endSymbol[index]);

	// Any.
	default:
		return randUint(32, 127);
	}
}


// Generates a signed integer array with random values.
int* randIntArray(const uint SIZE, int minValue, int maxValue) {
	int* array = new int[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		array[i] = randInt(minValue, maxValue);
	}
	return array;
}


// Generates an unsigned integer array with random values.
uint* randUintArray(const uint SIZE, uint minValue, uint maxValue) {
	uint* array = new uint[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		array[i] = randUint(minValue, maxValue);
	}
	return array;
}


// Generates a double array with random values.
double* randDoubleArray(const uint SIZE, double minValue, double maxValue) {
	double* array = new double[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		array[i] = randDouble(minValue, maxValue);
	}
	return array;
}


// Generates a char array of random characters based on type.
char* randCharArray(const uint SIZE, char type) {
	char* array = new char[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		array[i] = randChar(type);
	}
	return array;
}


// Shuffle the given signed integer array.
void shuffle(int* array, const uint SIZE) {
	updateSeed();
	for (size_t j, i = SIZE-1; i > 0; i--) {
		j = randUint(0, SIZE-1);
		std::swap(array[i], array[j]);
	}
}


// Shuffle the given unsigned integer array.
void shuffle(uint* array, const uint SIZE) {
	updateSeed();
	for (size_t j, i = SIZE-1; i > 0; i--) {
		j = randUint(0, SIZE-1);
		std::swap(array[i], array[j]);
	}
}


// Shuffle the given double array.
void shuffle(double* array, const uint SIZE) {
	updateSeed();
	for (size_t j, i = SIZE-1; i > 0; i--) {
		j = randUint(0, SIZE-1);
		std::swap(array[i], array[j]);
	}
}


// Shuffle the given char array.
void shuffle(char* array, const uint SIZE) {
	updateSeed();
	for (size_t j, i = SIZE-1; i > 0; i--) {
		j = randUint(0, SIZE-1);
		std::swap(array[i], array[j]);
	}
}
