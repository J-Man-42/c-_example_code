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


// Clears the terminal screen.
void clearScreen() {
	cout << "\033[2J\033[1;1H";
}


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
	char colours[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		colours[i] = '\0';
	}
	for (size_t i = 0; i < COUNT; i++) {
		if (highlight[i] < SIZE) {
			colours[highlight[i]] = colour[i];
		}
	}

	// Specify the height of the array.
	uint height = 40;

	// Configure the bar width.
	size_t width = (thinBar ? 1 : 2);

	// Move the cursor up N spaces.
	size_t N = (thinBar ? 23 : 24);
	cout << "\033["<<N<<"A\r";

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
}



// Bubble sort the given array.
void bubbleSort(uint array[], const uint SIZE, uint ms, bool thinBar) {
	auto delay = milliseconds(ms);
	const size_t COUNT = 3;
	uint highlight[COUNT];
	char colour[COUNT] = {'C', 'C', 'X'};

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE, thinBar);
	sleep_for(delay);

	// Indicate update which element to sort.
	bool swapped;
	for (size_t n = SIZE; n > 0; n--) {
		highlight[2] = n;
		swapped = false;
		for (size_t i = 1; i < n; i++) {
			highlight[0] = i-1;
			highlight[1] = i;

			// Display the current comparison.
			displayArray(array, SIZE, thinBar, highlight, colour, COUNT);
			sleep_for(delay);
			if (array[i] < array[i-1]) {
				swap(array[i], array[i-1]);
				swapped = true;

				// Display the swapped elements.
				displayArray(array, SIZE, thinBar, highlight, colour, COUNT);
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
	const size_t COUNT = 4;
	uint highlight[COUNT];
	char compareColour[COUNT] = {'X', 'C', 'C', 'R'};
	char swapColour[COUNT-1] = {'X', 'R', 'R'};

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE, thinBar);
	sleep_for(delay);

	// Indicate the starting index.
	size_t minIndex;
	for (uint i = 0; i < SIZE; i++) {
		highlight[0] = i-1;
		minIndex = i;
		highlight[3] = minIndex;
		for (size_t j = i+1; j < SIZE; j++) {
			highlight[1] = i;
			highlight[2] = j;

			// Display the current comparison.
			displayArray(array, SIZE, thinBar, highlight, compareColour, COUNT);
			sleep_for(delay);
			if (array[j] < array[minIndex]) {
				minIndex = j;
				highlight[3] = minIndex;
			}
		}

		// Display the array before and after swapping.
		highlight[1] = minIndex;
		highlight[2] = i;
		displayArray(array, SIZE, thinBar, highlight, swapColour, COUNT-1);
		sleep_for(delay);

		// Only swap if needed.
		if (minIndex != i) {
			swap(array[i], array[minIndex]);
			displayArray(array, SIZE, thinBar, highlight, swapColour, COUNT-1);
			sleep_for(delay);
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
	clearScreen();
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
	clearScreen();
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
