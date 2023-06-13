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
uint Sorting::barWidth = 2;


// Toggles between a width of 1 and a width of 2.
void Sorting::toggleBarWidth() {
	barWidth = barWidth % 2 + 1;
}


// Displays the array content as pillars.
void Sorting::displayArray(
	uint array[], const uint SIZE,
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

	// Move the cursor up N spaces.
	size_t N = (barWidth == 1 ? 23 : 24);
	moveCursorUp(N);

	// Above the bars.
	for (size_t i = 1; i < SIZE; i++) {
		for (size_t j = 0; j <= barWidth; j++) {
			cout << "┴";
		}
	}
	for (size_t i = 0; i < barWidth; i++) {
		cout << "┴";
	}
	cout << endl;

	// Setup single/double bar.
	string singleBar[] = {"█ ", "▄ ", "  "};
	string doubleBar[] = {"██ ", "▄▄ ", "   "};
	string* bars = (barWidth == 1 ? singleBar : doubleBar);
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
	if (barWidth > 1) {
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
		for (size_t j = 0; j <= barWidth; j++) {
			cout << "┬";
		}
	}
	for (size_t i = 0; i < barWidth; i++) {
		cout << "┬";
	}
	cout << "\n\n";
}



// Displays the array content as pillars.
void Sorting::displayArray(
	uint array[], const uint SIZE,
	LinkedList<Highlight>* highlight) {

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

	// Specify the height of the array.
	uint height = 40;

	// Move the cursor up N spaces.
	size_t N = (barWidth == 1 ? 23 : 24);
	moveCursorUp(N);

	// Above the bars.
	for (size_t i = 1; i < SIZE; i++) {
		for (size_t j = 0; j <= barWidth; j++) {
			cout << "┴";
		}
	}
	for (size_t i = 0; i < barWidth; i++) {
		cout << "┴";
	}
	cout << endl;

	// Setup single/double bar.
	string singleBar[] = {"█ ", "▄ ", "  "};
	string doubleBar[] = {"██ ", "▄▄ ", "   "};
	string* bars = (barWidth == 1 ? singleBar : doubleBar);
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
	for (size_t i = 1; i < SIZE; i++) {
		for (size_t j = 0; j <= barWidth; j++) {
			cout << "┬";
		}
	}
	for (size_t i = 0; i < barWidth; i++) {
		cout << "┬";
	}
	cout << "\n\n";
}




// Bubble sort the given array.
void Sorting::bubbleSort(uint array[], const uint SIZE) {
	auto delay = milliseconds(Sorting::delay);
	LinkedList<Highlight>* blank = nullptr;
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('C'));
	highlight->add(Highlight('C'));
	
	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE, blank);
	sleep_for(delay);

	// Indicate update which element to sort.
	bool swapped;
	for (size_t n = SIZE; n > 0; n--) {
		swapped = false;
		if (n < SIZE) {
			highlight->add(Highlight('X', n));
		}
		for (size_t i = 1; i < n; i++) {
			(*highlight)[0].index = i-1;
			(*highlight)[1].index = i;

			// Display the current comparison.
			displayArray(array, SIZE, highlight);
			sleep_for(delay);
			if (array[i] < array[i-1]) {
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
	displayArray(array, SIZE, blank);
	sleep_for(delay);

	// Delete dynamic memory.
	delete highlight;

}



// Selection sort the given array.
void Sorting::selectionSort(uint array[], const uint SIZE) {
	auto delay = milliseconds(Sorting::delay);
	LinkedList<Highlight>* blank = nullptr;
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('C'));
	highlight->add(Highlight('C'));
	highlight->add(Highlight('R'));
	
	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE, blank);
	sleep_for(delay);

	// Indicate the starting index.
	size_t minIndex;
	for (size_t i = 0; i < SIZE-1; i++) {
		(*highlight)[2].index = i;
		minIndex = i;
		for (size_t j = i+1; j < SIZE; j++) {
			(*highlight)[0].index = i;
			(*highlight)[1].index = j;

			// Display the current comparison.
			displayArray(array, SIZE, highlight);
			sleep_for(delay);
			if (array[j] < array[minIndex]) {
				minIndex = j;
				(*highlight)[2].index = minIndex;
			}
		}

		// Alter list for swapping.
		highlight->removeAt(0);
		highlight->set(0, Highlight('R', minIndex));
		(*highlight)[1].index = i;

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
		(*highlight)[0].colour = 'C';
		highlight->insert(0, Highlight('C'));
		highlight->add(Highlight('X', i));
	}

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);
}



// Insertion sort the given array.
void Sorting::insertionSort(uint array[], const uint SIZE) {
	auto delay = milliseconds(Sorting::delay);
	LinkedList<Highlight>* blank = nullptr;
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('C'));
	highlight->add(Highlight('C'));
	bool swapped;
	
	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE, blank);
	sleep_for(delay);

	// Iterate starting from the second element.
	for (size_t i = 1; i < SIZE; i++) {
		swapped = false;

		// Loop while swapping is needed.
		size_t j = i;
		while (j > 0 && array[j] < array[j-1]) {
			(*highlight)[0].index = j-1;
			(*highlight)[1].index = j;
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
			(*highlight)[0].index = i-1;
			(*highlight)[1].index = i;
			displayArray(array, SIZE, highlight);
			sleep_for(delay);
		}
	}

	// Display the array after sorting.
	displayArray(array, SIZE, blank);
	sleep_for(delay);
}



// Cocktail shaker sort the given array.
void Sorting::cocktailShakerSort(uint array[], const uint SIZE) {
	auto delay = milliseconds(Sorting::delay);
	LinkedList<Highlight>* blank = nullptr;
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('C'));
	highlight->add(Highlight('C'));

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE, blank);
	sleep_for(delay);

	// Loop while a swap has occurred.
	size_t start = 0, end = SIZE;
	bool swapped;
	do {

		// Iterate forwards.
		swapped = false;
		for (size_t i = start+1; i < end; i++) {
			(*highlight)[0].index = i-1;
			(*highlight)[1].index = i;

			// Display the current comparison.
			displayArray(array, SIZE, highlight);
			sleep_for(delay);
			if (array[i] < array[i-1]) {
				swap(array[i], array[i-1]);
				swapped = true;

				// Display the swapped elements.
				displayArray(array, SIZE, highlight);
				sleep_for(delay);
			}
		}
		end--;
		highlight->add(Highlight('X', end));

		// Break if no swap occurred.
		if (!swapped) {
			break;
		}

		// Iterate backwards.
		swapped = false;
		for (size_t i = end-1; i > start; i--) {
			(*highlight)[0].index = i-1;
			(*highlight)[1].index = i;

			// Display the current comparison.
			displayArray(array, SIZE, highlight);
			sleep_for(delay);
			if (array[i] < array[i-1]) {
				swap(array[i], array[i-1]);
				swapped = true;

				// Display the swapped elements.
				displayArray(array, SIZE, highlight);
				sleep_for(delay);
			}
		}
		highlight->add(Highlight('X', start));
		start++;

	} while (swapped);

	// Display the array after sorting.
	displayArray(array, SIZE, blank);
	sleep_for(delay);
}
