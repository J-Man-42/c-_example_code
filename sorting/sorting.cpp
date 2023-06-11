#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "sorting.h"
#include "../colour_text/colour_text.h"
#include "../min_and_max/min_max.h"
using namespace std;
using namespace std::this_thread;	// sleep_for, sleep_until
using namespace std::chrono;		// nanoseconds, system_clock, seconds.


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
	uint array[], const uint SIZE, bool thinBar,
	uint* highlight, char* colour, const uint COUNT) {

	// Configure the highlight colours.
	size_t index = 0;
	char* colours = new char[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		colours[i] = '\0';
	}
	for (size_t i = 0; i < COUNT; i++) {
		for (size_t j = 0; j < SIZE; j++) {
			if (highlight[i] == j) {
				colours[j] = colour[index];
				index++;
			}
		}
	}

	// Specify the height of the array.
	uint height = 40;

	// Configure the bar width.
	size_t width = (thinBar ? 1 : 2);

	// Clear the screen.
	cout << "\033[2J\033[1;1H";

	// Above the bars.
	for (size_t i = 1; i < SIZE; i++) {
		for (size_t j = 0; j <= width; j++) {
			cout << "┴";
		}
	}
	for (size_t i = 0; i < width; i++) {
		cout << "┴";
	}
	cout << endl;

	// Setup single/double bar.
	string singleBar[] = {"█ ", "▄ ", "  "};
	string doubleBar[] = {"██ ", "▄▄ ", "   "};
	string* bars = (thinBar ? singleBar : doubleBar);
	string bar;

	// Iterate through all layers.
	for (size_t n = height; n > 0; n -= 2) {
		index = 0;
		for (size_t i = 0; i < SIZE; i++) {

			// Get the bar shape.
			if (array[i] >= n) {
				bar = bars[0];
			} else if (array[i] == n-1) {
				bar = bars[1];
			} else {
				bar = bars[2];
			}

			// Print text in the appropriate colour.
			cout << colourText(bar, colours[i]);
		}
		cout << endl;
	}

	// Show the numbers below the bars.
	if (!thinBar) {
		index = 0;
		for (size_t i = 0; i < SIZE; i++) {
			if (colours[i] == '\0') {
				cout << setw(2) << array[i];
			} else {
				cout << setw(13) << colourText(to_string(array[i]), colours[i]);
			}
			cout << " ";
		}
		cout << endl;
	}

	// Below the numbers.
	for (size_t i = 1; i < SIZE; i++) {
		for (size_t j = 0; j <= width; j++) {
			cout << "┬";
		}
	}
	for (size_t i = 0; i < width; i++) {
		cout << "┬";
	}
	cout << "\n\n";

	// Delete dynamic memory.
	delete [] colours;
}



// Bubble sort the given array.
void bubbleSort(uint array[], const uint SIZE, uint ms, bool thinBar) {
	auto delay = milliseconds(ms);
	uint highlight[2];
	char colour[2] = {'C', 'C'};

	// Display the array before sorting.
	displayArray(array, SIZE, thinBar);
	sleep_for(delay);

	// Indicate update which element to sort.
	bool swapped;
	for (size_t n = SIZE; n > 0; n--) {
		swapped = false;
		for (size_t i = 1; i < n; i++) {
			highlight[0] = i-1;
			highlight[1] = i;

			// Display the current comparison.
			displayArray(array, SIZE, thinBar, highlight, colour, 2);
			sleep_for(delay);
			if (array[i] < array[i-1]) {
				swap(array[i], array[i-1]);
				swapped = true;

				// Display the swapped elements.
				displayArray(array, SIZE, thinBar, highlight, colour, 2);
				sleep_for(delay);
			}
		}

		// Break loop if no swaps occurred.
		if (!swapped) {
			break;
		}
	}

	// Display the array after sorting.
	displayArray(array, SIZE, thinBar);
	sleep_for(delay);
}



// Selection sort the given array.
void selectionSort(uint array[], const uint SIZE, uint ms, bool thinBar) {
	auto delay = milliseconds(ms);
	uint highlight[3];
	char compareColour[3] = {'C', 'C', 'R'};
	char swapColour[2] = {'R', 'R'};

	// Display the array before sorting.
	displayArray(array, SIZE, thinBar);
	sleep_for(delay);

	// Indicate the starting index.
	bool swapped;
	size_t minIndex;
	for (size_t i = 0; i < SIZE; i++) {
		swapped = false;
		minIndex = i;
		highlight[2] = minIndex;
		for (size_t j = i+1; j < SIZE; j++) {
			highlight[0] = i;
			highlight[1] = j;

			// Display the current comparison.
			displayArray(array, SIZE, thinBar, highlight, compareColour, 3);
			sleep_for(delay);
			if (array[j] < array[minIndex]) {
				minIndex = j;
				highlight[2] = minIndex;
			}
		}

		// Display the array before and after swapping.
		swapped = (minIndex != i);
		if (swapped) {
			highlight[0] = minIndex;
			highlight[1] = i;
			displayArray(array, SIZE, thinBar, highlight, swapColour, 2);
			sleep_for(delay);
			swap(array[i], array[minIndex]);
			displayArray(array, SIZE, thinBar, highlight, swapColour, 2);
			sleep_for(delay);
		} else {
			break;
		}
	}

	// Display the array after sorting.
	displayArray(array, SIZE, thinBar);
	sleep_for(delay);
}



// Insertion sort the given array.
void insertionSort(uint array[], const uint SIZE, uint ms, bool thinBar) {
	auto delay = milliseconds(ms);
	uint highlight[2];
	char colour[2] = {'C', 'C'};

	// Display the array before sorting.
	displayArray(array, SIZE, thinBar);
	sleep_for(delay);

	// Iterate starting from the second element.
	for (size_t i = 1; i < SIZE; i++) {
		highlight[0] = i;
		displayArray(array, SIZE, thinBar, highlight, colour, 1);
		sleep_for(delay);

		size_t j = i;
		while (j > 0 && array[j] < array[j-1]) {
			highlight[0] = j;
			highlight[1] = j-1;
			displayArray(array, SIZE, thinBar, highlight, colour, 2);
			sleep_for(delay);
			swap(array[j], array[j-1]);
			j--;
			displayArray(array, SIZE, thinBar, highlight, colour, 2);
			sleep_for(delay);
		}
	}

	// Display the array after sorting.
	displayArray(array, SIZE, thinBar);
	sleep_for(delay);
}



// Cocktail shaker sort the given array.
void cocktailShakerSort(uint array[], const uint SIZE, uint ms, bool thinBar) {
	auto delay = milliseconds(ms);
	uint highlight[2];
	char colour[2] = {'C', 'C'};

	// Display the array before sorting.
	displayArray(array, SIZE, thinBar);
	sleep_for(delay);

	// Loop while a swap has occurred.
	size_t start = 0, end = SIZE;
	bool swapped;
	do {

		// Iterate in ascending order.
		swapped = false;
		for (size_t i = start+1; i < end; i++) {
			highlight[0] = i-1;
			highlight[1] = i;

			// Display the current comparison.
			displayArray(array, SIZE, thinBar, highlight, colour, 2);
			sleep_for(delay);
			if (array[i] < array[i-1]) {
				swap(array[i], array[i-1]);
				swapped = true;

				// Display the swapped elements.
				displayArray(array, SIZE, thinBar, highlight, colour, 2);
				sleep_for(delay);
			}
		}
		end--;

		// Break if no swap occurred
		if (!swapped) {
			break;
		}

		// Iterate in descending order.
		swapped = false;
		for (size_t i = end-1; i > start; i--) {
			highlight[0] = i-1;
			highlight[1] = i;

			// Display the current comparison.
			displayArray(array, SIZE, thinBar, highlight, colour, 2);
			sleep_for(delay);
			if (array[i] < array[i-1]) {
				swap(array[i], array[i-1]);
				swapped = true;

				// Display the swapped elements.
				displayArray(array, SIZE, thinBar, highlight, colour, 2);
				sleep_for(delay);
			}
		}
		start++;

	} while (swapped);

	// Display the array after sorting.
	displayArray(array, SIZE, thinBar);
	sleep_for(delay);
}
