#include <iostream>
#include <iomanip>
#include "sorting.h"
#include "../colour_text/colour_text.h"
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
void displayArray(
	uint array[], const uint SIZE, uint* highlight, const uint COUNT) {

	// Get the maximum value
	uint maxValue = max(array, SIZE);

	// Above the bars.
	for (size_t i = 1; i < SIZE; i++) {
		cout << "┴┴┴";
	}
	cout << "┴┴\n";

	// Ensure the top layer is displayed.
	if (maxValue % 2 == 1) {
		maxValue++;
	}

	// All remaining layers.
	string bar;
	size_t colourIndex = 0;
	for (size_t n = maxValue; n > 0; n -= 2) {
		colourIndex = 0;
		for (size_t i = 0; i < SIZE; i++) {

			// Get the bar shape.
			if (array[i] >= n) {
				bar = "██ ";
			} else if (array[i] == n-1) {
				bar = "▄▄ ";
			} else {
				bar = "   ";
			}

			// Get the bar colour.
			if (COUNT > 0 && colourIndex < COUNT && highlight[colourIndex] == i) {
				cout << colourText(bar, 'G');
				colourIndex++;
			} else {
				cout << bar;
			}
		}
		cout << endl;
	}

	// Show the numbers below the bars.
	colourIndex = 0;
	for (size_t i = 0; i < SIZE; i++) {
		if (COUNT > 0 && colourIndex < COUNT && highlight[colourIndex] == i) {
			cout << setw(13) << colourText(to_string(array[i]), 'G');
			colourIndex++;
		} else {
			cout << setw(2) << array[i];
		}
		cout << " ";
	}
	cout << endl;

	// Below the numbers.
	for (size_t i = 1; i < SIZE; i++) {
		cout << "┬┬┬";
	}
	cout << "┬┬\n\n";
}