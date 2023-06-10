#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "sorting.h"
#include "../colour_text/colour_text.h"
#include "../min_and_max/min_max.h"
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.


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

	// Clear the screen.
	cout << "\033[2J\033[1;1H";

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
			if (colourIndex < COUNT && highlight[colourIndex] == i) {
				cout << colourText(bar, 'C');
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
		if (colourIndex < COUNT && highlight[colourIndex] == i) {
			cout << setw(13) << colourText(to_string(array[i]), 'C');
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



// Bubble sort the given array.
void bubbleSort(uint array[], const uint SIZE) {
	auto delay = 50ms;

	// Display the array before sorting.
	displayArray(array, SIZE);
	sleep_for(delay);

	uint highlight[SIZE];
	for (size_t n = SIZE; n > 0; n--) {
		for (size_t i = 1; i < n; i++) {
			highlight[0] = i-1;
			highlight[1] = i;

			// Display the current comparison.
			displayArray(array, SIZE, highlight, 2);
			sleep_for(delay);
			if (array[i] < array[i-1]) {
				swap(array[i], array[i-1]);

				// Display the swapped elements.
				displayArray(array, SIZE, highlight, 2);
				sleep_for(delay);
			}
		}
	}

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);
}