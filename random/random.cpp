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


// Generates a signed integer array with random values.
int* randIntArray(const uint SIZE, int minValue, int maxValue) {
	updateSeed();
	int* array = new int[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		array[i] = randInt(minValue, maxValue);
	}
	return array;
}


// Generates an unsigned integer array with random values.
uint* randUintArray(const uint SIZE, uint minValue, uint maxValue) {
	updateSeed();
	uint* array = new uint[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		array[i] = randUint(minValue, maxValue);
	}
	return array;
}


// Generates double array with random values.
double* randDoubleArray(const uint SIZE, double minValue, double maxValue) {
	updateSeed();
	double* array = new double[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		array[i] = randDouble(minValue, maxValue);
	}
	return array;
}


// Shuffle the given signed integer array.
void shuffle(int* array, const uint SIZE) {
	updateSeed();
	for (size_t j, i = SIZE-1; i > 0; i--) {
		j = randInt(0, SIZE-1);
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
		j = randDouble(0, SIZE-1);
		std::swap(array[i], array[j]);
	}
}
