#include <iostream>
#include "sorting.h"
#include "../min_and_max/min_max.h"
using namespace std;


// Generate a random integer between minValue and maxValue.
uint randint(uint minValue, uint maxValue) {

	// Configure the seed.
	static uint long seed = 0;
	if (seed == 0) {
		seed = time(0);
		srand(seed);
	}

	// Generate and return a random integer.
	return rand() % (maxValue - minValue + 1) + minValue;
}



// Displays the array content as pillars.
void displayArray(uint array[], const uint SIZE) {

	// Get the maximum value
	uint maxValue = max(array, SIZE);
	cout << "maxValue = " << maxValue << endl;

	// The top odd number layer.
	if (maxValue % 2 == 1) {
		for (size_t i = 0; i < SIZE; i++) {
			if (array[i] == maxValue) {
				cout << "▄ ";
			} else {
				cout << "  ";
			}
		}
		cout << endl;
		maxValue--;
	}

	// All remaining layers.
	for (size_t i = maxValue; i > 0; i -= 2) {
		for (size_t j = 0; j < SIZE; j++) {
			if (array[j] >= i) {
				cout << "█ ";
			} else if (array[j] == i-1) {
				cout << "▄ ";
			} else {
				cout << "  ";
			}
		}
		cout << endl;
	}
}