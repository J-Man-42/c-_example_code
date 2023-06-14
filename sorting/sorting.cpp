#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "sorting.h"
#include "../colour_text/colour_text.h"
#include "../move_cursor/move_cursor.h"
using namespace std;
using namespace std::this_thread;	// sleep_for, sleep_until
using namespace std::chrono;		// nanoseconds, system_clock, seconds.


// Set static member values.
uint Sorting::delay = 50;
uint Sorting::height = 40;
uint Sorting::barWidth = 2;
string Sorting::singleBars[] = {"█ ", "▄ ", "  "};
string Sorting::doubleBars[] = {"██ ", "▄▄ ", "   "};
string* Sorting::bars = doubleBars;
bool Sorting::sortAscending = true;


// Toggles between a width of 1 and a width of 2.
void Sorting::toggleBarWidth() {
	barWidth = barWidth % 2 + 1;
	if (barWidth == 1) {
		bars = singleBars;
	} else {
		bars = doubleBars;
	}
}


// Update the display bar height.
void Sorting::setBarHeight(uint height) {
	Sorting::height = height;
	if (height % 2 == 1) {
		Sorting::height++;
	}
}


// Returns the current bar width.
uint Sorting::getBarWidth() {
	return barWidth;
}


// Prints either the top or bottom border.
void Sorting::printBorder(string symbol, const uint SIZE) {
	for (size_t i = 1; i < SIZE; i++) {
		for (size_t j = 0; j <= barWidth; j++) {
			cout << symbol;
		}
	}
	for (size_t i = 0; i < barWidth; i++) {
		cout << symbol;
	}
	cout << endl;
}


// Displays the array content as pillars.
void Sorting::displayArray(
	uint array[], const uint SIZE,
	LinkedList<Highlight>* highlight,
	Highlight* horizontalBar) {

	// Configure the highlight colours.
	char colour[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		colour[i] = '\0';
	}
	if (highlight) {
		for (size_t i = 0; i < highlight->size(); i++) {
			colour[highlight->get(i).index] = highlight->get(i).colour;
		}
	}

	// Move the cursor up N spaces.
	size_t N = (height / 2) + (barWidth == 1 ? 3 : 4);
	moveCursorUp(N);

	// Above the bars.
	printBorder("┴", SIZE);

	// Iterate through all layers.
	string bar;
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
			cout << colourText(bar, colour[i]);
		}
		cout << endl;
	}

	// Show the numbers below the bars.
	if (barWidth > 1) {
		for (size_t i = 0; i < SIZE; i++) {
			if (colour[i] == '\0') {
				cout << setw(2) << array[i];
			} else {
				cout << setw(13) << colourText(to_string(array[i]), colour[i]);
			}
			cout << " ";
		}
		cout << endl;
	}

	// Below the numbers.
	printBorder("┬", SIZE);
	cout << endl;

	// Display the horizontal bar.
	if (horizontalBar && horizontalBar->value <= height) {

		// Move the cursor to the correct position.
		size_t M = (horizontalBar->value / 2) + barWidth;
		M += (horizontalBar->value % 2 == 1) + 1;
		moveCursorUp(M);

		// Configure the bar shape.
		bar = (horizontalBar->value % 2 == 0 ? "▀" : "▄");

		// Write horizontal bar for all elements in the array.
		for (size_t i = 0; i < SIZE; i++) {

			// Do not overwrite existing vertical bars.
			if (array[i] < horizontalBar->value) {
				for (size_t j = 0; j <= barWidth; j++) {
					cout << colourText(bar, 'M');
				}
			} else {
				moveCursorRight(barWidth);
				cout << colourText(bar, 'M');
			}
		}

		// Mover the cursor back down.
		cout << "\b \n";
		moveCursorDown(M-1);
	}
}


// Returns true if correct conditions
// for swapping left and right.
bool Sorting::mustSwap(uint left, uint right) {
	if (sortAscending)
		return left < right;
	return left > right;
}



// Bubble sort the given array.
void Sorting::bubbleSort(uint array[], const uint SIZE) {
	auto delay = milliseconds(Sorting::delay);
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('C'));
	highlight->add(Highlight('C'));

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Indicate update which element to sort.
	bool swapped;
	for (size_t n = SIZE; n > 0; n--) {
		swapped = false;
		if (n < SIZE) {
			highlight->add(Highlight('G', n));
		}
		for (size_t i = 1; i < n; i++) {
			highlight->get(0).index = i-1;
			highlight->get(1).index = i;

			// Display the current comparison.
			displayArray(array, SIZE, highlight);
			sleep_for(delay);

			// Swap elements if needed.
			if (mustSwap(array[i], array[i-1])) {
				swap(array[i], array[i-1]);
				swapped = true;

				// Display the swapped elements.
				displayArray(array, SIZE, highlight);
				sleep_for(delay);
			}
		}

		// Break loop if no swaps occurred.
		if (!swapped) {
			break;
		}
	}

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);

	// Delete dynamic memory.
	delete highlight;

}



// Selection sort the given array.
void Sorting::selectionSort(uint array[], const uint SIZE) {
	auto delay = milliseconds(Sorting::delay);
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('C'));
	highlight->add(Highlight('C'));
	highlight->add(Highlight('R'));

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Indicate the starting index.
	size_t minIndex;
	for (size_t i = 0; i < SIZE-1; i++) {
		(*highlight)[2].index = i;
		minIndex = i;
		for (size_t j = i+1; j < SIZE; j++) {
			highlight->get(0).index = i;
			highlight->get(1).index = j;

			// Display the current comparison.
			displayArray(array, SIZE, highlight);
			sleep_for(delay);

			// New critical value.
			if (mustSwap(array[j], array[minIndex])) {
				minIndex = j;
				(*highlight)[2].index = minIndex;
			}
		}

		// Alter list for swapping.
		highlight->removeAt(0);
		highlight->set(0, Highlight('R', minIndex));
		highlight->get(1).index = i;

		// Display the array before and after swapping.
		displayArray(array, SIZE, highlight);
		sleep_for(delay);

		// Only swap if needed.
		if (minIndex != i) {
			swap(array[i], array[minIndex]);
			displayArray(array, SIZE, highlight);
			sleep_for(delay);
		}

		// Alter list for next comparison.
		highlight->get(0).colour = 'C';
		highlight->insert(0, Highlight('C'));
		highlight->add(Highlight('G', i));
	}

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);

	// Delete dynamic memory.
	delete highlight;
}



// Insertion sort the given array.
void Sorting::insertionSort(uint array[], const uint SIZE) {
	auto delay = milliseconds(Sorting::delay);
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('C'));
	highlight->add(Highlight('C'));
	bool swapped;

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Iterate starting from the second element.
	for (size_t i = 1; i < SIZE; i++) {
		swapped = false;

		// Loop while swapping is needed.
		size_t j = i;
		while (j > 0 && mustSwap(array[j], array[j-1])) {
			highlight->get(0).index = j-1;
			highlight->get(1).index = j;
			displayArray(array, SIZE, highlight);
			sleep_for(delay);
			swap(array[j], array[j-1]);
			displayArray(array, SIZE, highlight);
			sleep_for(delay);
			swapped = true;
			j--;
		}

		// Only print if no swap occurred.
		if (!swapped) {
			highlight->get(0).index = i-1;
			highlight->get(1).index = i;
			displayArray(array, SIZE, highlight);
			sleep_for(delay);
		}
	}

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);

	// Delete dynamic memory.
	delete highlight;
}



// Cocktail shaker sort the given array.
void Sorting::cocktailShakerSort(uint array[], const uint SIZE) {
	auto delay = milliseconds(Sorting::delay);
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('C'));
	highlight->add(Highlight('C'));

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Loop while a swap has occurred.
	size_t start = 0, end = SIZE;
	bool swapped;
	do {

		// Iterate forwards.
		swapped = false;
		for (size_t i = start+1; i < end; i++) {
			highlight->get(0).index = i-1;
			highlight->get(1).index = i;

			// Display the current comparison.
			displayArray(array, SIZE, highlight);
			sleep_for(delay);

			// Swap elements if needed.
			if (mustSwap(array[i], array[i-1])) {
				swap(array[i], array[i-1]);
				swapped = true;

				// Display the swapped elements.
				displayArray(array, SIZE, highlight);
				sleep_for(delay);
			}
		}
		end--;
		highlight->add(Highlight('G', end));

		// Break if no swap occurred.
		if (!swapped) {
			break;
		}

		// Iterate backwards.
		swapped = false;
		for (size_t i = end-1; i > start; i--) {
			highlight->get(0).index = i-1;
			highlight->get(1).index = i;

			// Display the current comparison.
			displayArray(array, SIZE, highlight);
			sleep_for(delay);

			// Swap elements.
			if (mustSwap(array[i], array[i-1])) {
				swap(array[i], array[i-1]);
				swapped = true;

				// Display the swapped elements.
				displayArray(array, SIZE, highlight);
				sleep_for(delay);
			}
		}
		highlight->add(Highlight('G', start));
		start++;

	} while (swapped);

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);

	// Delete dynamic memory.
	delete highlight;
}


// Quick Sort the array.
void Sorting::quickSort(uint array[], const uint SIZE) {
	auto delay = milliseconds(Sorting::delay);

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// QuickSort.
	quickSort(array, SIZE, 0, SIZE-1);

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);
}


// The hidden recursive Quick Sort function.
void Sorting::quickSort(
	uint array[], const int SIZE, int low, int high) {

	// Stopping condition.
	if (low > high || low < 0) {
		return;
	}

	// Configure all highlights.
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('C', low));
	highlight->add(Highlight('C'));
	highlight->add(Highlight('R', high));
	for (int i = 0; i < low; i++) {
		highlight->add(Highlight('X', i));
	}
	for (int i = high+1; i < SIZE; i++) {
		highlight->add(Highlight('X', i));
	}

	// Partition array and get the pivot index.
	int pivotIndex = partition(array, SIZE, low, high, highlight);

	// Sort the two partitions.
	quickSort(array, SIZE, low, pivotIndex-1);
	quickSort(array, SIZE, pivotIndex+1, high);

	// Delete dynamic memory.
	delete highlight;
}


// The partition function for Quick Sort.
int Sorting::partition(
	uint array[], const int SIZE, int low, int high,
	LinkedList<Highlight>* highlight) {

	// Setup the delay.
	auto delay = milliseconds(Sorting::delay);

	// Pivot is the last element.
	uint pivot = array[high];
	highlight->get(2).index = high;
	Highlight* horizontalBar = new Highlight('M', MAX_UINT, pivot);

	// Temporary pivot index.
	int i = low - 1;
	highlight->get(0).index = i;

	// Iterate from low to high.
	for (int j = low; j < high; j++) {

		// Display the array.
		highlight->get(1).index = j;
		displayArray(array, SIZE, highlight, horizontalBar);
		sleep_for(delay);

		// Swap if needed.
		if (mustSwap(array[j], pivot)) {
			highlight->add(Highlight('G', i));
			i++;
			swap(array[i], array[j]);

			// Display array after swapping.
			highlight->get(0).index = i;
			displayArray(array, SIZE, highlight, horizontalBar);
			sleep_for(delay);
		}
	}

	// Final swap, then return pivot index.
	i++;
	if (array[i] != array[high]) {

		// Show array before swapping.
		highlight->removeAt(0);
		highlight->set(0, Highlight('R', i));
		highlight->get(1).index = high;
		displayArray(array, SIZE, highlight, horizontalBar);
		sleep_for(delay);

		// Swap.
	    swap(array[i], array[high]);

	    // Show array after swapping.
		highlight->get(0).index = i;
		displayArray(array, SIZE, highlight, horizontalBar);
		sleep_for(delay);
	}

	// Delete dynamic memory and return pivot index.
	delete horizontalBar;
    return i;
}
