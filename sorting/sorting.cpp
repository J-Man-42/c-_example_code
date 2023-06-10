#include <iostream>
#include <iomanip>
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

	// Above the bars.
	for (size_t i = 0; i < SIZE-1; i++) {
		cout << "┴┴┴";
	}
	cout << "┴┴\n";

	// The top odd number layer.
	if (maxValue % 2 == 1) {
		for (size_t i = 0; i < SIZE; i++) {
			if (array[i] == maxValue) {
				cout << "▄▄ ";
			} else {
				cout << "   ";
			}
		}
		cout << endl;
		maxValue--;
	}

	// All remaining layers.
	for (size_t n = maxValue; n > 0; n -= 2) {
		for (size_t i = 0; i < SIZE; i++) {
			if (array[i] >= n) {
				cout << "██ ";
			} else if (array[i] == n-1) {
				cout << "▄▄ ";
			} else {
				cout << "   ";
			}
		}
		cout << endl;
	}

	// Show the numbers below the bars.
	for (size_t i = 0; i < SIZE; i++) {
		cout << setw(2) << array[i] << " ";
	}
	cout << endl;

	// Below the numbers.
	for (size_t i = 0; i < SIZE-1; i++) {
		cout << "┬┬┬";
	}
	cout << "┬┬\n";
}