#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <cmath>
#include "sorting.h"
#include "../colour_text/colour_text.h"
#include "../move_cursor/move_cursor.h"
using namespace std;
using namespace std::this_thread;	// sleep_for, sleep_until
using namespace std::chrono;		// nanoseconds, system_clock, seconds.


// Set static member values.
bool Sorting::sortAscending = true;
duration<int, milli> Sorting::delay = milliseconds(50);
uint Sorting::barHeight = 40;
uint Sorting::barWidth = 2;
uint Sorting::verticalScale = 1;
uint Sorting::displayHeight = 40;
string Sorting::singleBars[] = {"█ ", "▄ ", "  "};
string Sorting::doubleBars[] = {"██ ", "▄▄ ", "   "};
string* Sorting::bars = doubleBars;


// Toggles between a width of 1 and a width of 2.
void Sorting::toggleBarWidth() {
	barWidth = barWidth % 2 + 1;
	if (barWidth == 1) {
		bars = singleBars;
	} else {
		bars = doubleBars;
	}
}


// Returns the current bar width.
uint Sorting::getBarWidth() {
	return barWidth;
}


// Update the display bar height.
void Sorting::setBarHeight(uint height) {
	barHeight = height;
	calibrateHeightAndScale();
}


// Sets the vertical display scale.
void Sorting::setVerticalScale(uint scale) {
	verticalScale = scale;
	calibrateHeightAndScale();
}


// Calibrates the bar height and vertical scale.
void Sorting::calibrateHeightAndScale() {
	displayHeight = ceil(barHeight / (verticalScale*2.0));
	barHeight = displayHeight * verticalScale * 2;
	barHeight += (barHeight % verticalScale);
}


// Returns the vertical display scale.
uint Sorting::getVerticalScale() {
	return verticalScale;
}


// Sets the delay in milliseconds.
void Sorting::setDelay(uint ms) {
	delay = milliseconds(ms);
}


// Returns the delay in milliseconds.
uint Sorting::getDelay() {
	return delay.count();
}


// Prints either the top or bottom border.
void Sorting::printBorder(string symbol, const uint SIZE) {
	for (size_t i = 0; i < SIZE; i++) {
		for (size_t j = 0; j <= barWidth; j++) {
			cout << symbol;
		}
	}
	cout << "\b " << endl;
}


// Displays the array content as pillars.
void Sorting::displayArray(
	uint array[], const uint SIZE,
	LinkedList<Highlight>* highlight,
	uint horizontalBar) {

	// Update horizontal bar for display.
	if (horizontalBar > 0) {
		horizontalBar = ceil(double(horizontalBar) / verticalScale);
		horizontalBar *= verticalScale;
		horizontalBar += (horizontalBar % verticalScale);
	}

	// Make all entries bright white.
	char colour[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		colour[i] = 'w';
	}

	// Configure the provided highlight colours.
	if (highlight) {
		Highlight entry;
		highlight->resetNext();
		for (size_t i = 0; i < highlight->size(); i++) {
			entry = highlight->getNext();
			colour[entry.index] = entry.colour;
		}
	}

	// Move the cursor up N spaces.
	size_t N = displayHeight + barWidth + 2;
	moveCursorUp(N);

	// Above the bars.
	printBorder("┴", SIZE);

	// Configure the horizontal bar shape.
	string vBar, hBar;
	N = ceil(horizontalBar / double(verticalScale));
	hBar = (N % 2 == 0 ? "▀" : "▄");

	// Iterate through all layers.
	N = verticalScale*2;
	uint value = 0;
	for (size_t n = barHeight; n > 0; n -= N) {
		for (size_t i = 0; i < SIZE; i++) {

			// Modify value for display.
			value = ceil(double(array[i]) / verticalScale) * verticalScale;
    		value += (value % verticalScale);

			// Get the bar shape.
			if (value >= n) {
				vBar = bars[0];
			} else if (value == n-verticalScale) {
				vBar = bars[1];
			} else {
				vBar = bars[2];
			}

			// Print text in the appropriate colour.
			cout << colourText(vBar, colour[i]);

			// Print the horizontal bar in between.
			if (n == horizontalBar || n == horizontalBar+verticalScale) {
				if (value < horizontalBar) {
					moveCursorLeft(barWidth+1);
					for (size_t j = 0; j <= barWidth; j++) {
						cout << colourText(hBar, 'M');
					}
				} else {
					cout << "\b" << colourText(hBar, 'M');
				}
			}
		}
		cout << "\b " << endl;
	}

	// Show the numbers below the bars.
	if (barWidth > 1) {
		string text;
		for (size_t i = 0; i < SIZE; i++) {
			text = colourText(to_string(array[i]), colour[i]);
			cout << setw(13) << text << " ";
		}
		cout << endl;
	}

	// Below the numbers.
	printBorder("┬", SIZE);
	cout << endl;
}


// Returns true if correct conditions
// for swapping left and right.
bool Sorting::compare(uint left, uint right) {
	if (sortAscending)
		return left < right;
	return left > right;
}



// Bubble sort the given array.
void Sorting::bubbleSort(uint array[], const uint SIZE) {
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('b'));
	highlight->add(Highlight('b'));

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
			if (compare(array[i], array[i-1])) {
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
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('b'));
	highlight->add(Highlight('b'));
	highlight->add(Highlight('R'));

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Indicate the starting index.
	size_t minIndex;
	for (size_t i = 0; i < SIZE-1; i++) {
		highlight->get(2).index = i;
		minIndex = i;
		for (size_t j = i+1; j < SIZE; j++) {
			highlight->get(0).index = i;
			highlight->get(1).index = j;

			// Display the current comparison.
			displayArray(array, SIZE, highlight);
			sleep_for(delay);

			// New critical value.
			if (compare(array[j], array[minIndex])) {
				minIndex = j;
				highlight->get(2).index = minIndex;
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
		highlight->get(0).colour = 'b';
		highlight->insert(0, Highlight('b'));
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
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('b'));
	highlight->add(Highlight('b'));
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
		while (j > 0 && compare(array[j], array[j-1])) {
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
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('b'));
	highlight->add(Highlight('b'));

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
			if (compare(array[i], array[i-1])) {
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
			if (compare(array[i], array[i-1])) {
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
	highlight->add(Highlight('b', low));
	highlight->add(Highlight('b'));
	highlight->add(Highlight('R', high));
	for (int i = 0; i < low; i++) {
		highlight->add(Highlight('x', i));
	}
	for (int i = high+1; i < SIZE; i++) {
		highlight->add(Highlight('x', i));
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

	// Pivot is the last element.
	uint pivot = array[high];
	uint horizontalBar = pivot;
	highlight->get(2).index = high;

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
		if (compare(array[j], pivot)) {
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
    return i;
}



// Quick Sort the array.
void Sorting::quickSortV2(uint array[], const uint SIZE) {

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// QuickSort.
	quickSortV2(array, SIZE, 0, SIZE-1);

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);
}


// The hidden recursive Quick Sort function.
void Sorting::quickSortV2(
	uint array[], const int SIZE, int low, int high) {

	// Stopping condition.
	if (low >= high || low < 0 || high < 0) {
		return;
	}

	// Configure all highlights.
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('b', low));
	highlight->add(Highlight('b'));
	highlight->add(Highlight('R', high));
	for (int i = 0; i < low; i++) {
		highlight->add(Highlight('x', i));
	}
	for (int i = high+1; i < SIZE; i++) {
		highlight->add(Highlight('x', i));
	}

	// Partition array and get the pivot index.
	int pivotIndex = partitionV2(array, SIZE, low, high, highlight);

	// Sort the two partitions.
	quickSortV2(array, SIZE, low, pivotIndex);
	quickSortV2(array, SIZE, pivotIndex+1, high);

	// Delete dynamic memory.
	delete highlight;
}


// The partition function for Quick Sort.
int Sorting::partitionV2(
	uint array[], const int SIZE, int low, int high,
	LinkedList<Highlight>* highlight) {

	// Pivot is the middle element.
	uint middle = ((high - low) / 2) + low;
	uint pivot = array[middle];
	uint horizontalBar = pivot;
	highlight->get(2).index = middle;

	// Left index.
	int i = low - 1;

	// Right index.
	int j = high + 1;

	// Loop until left and right cross.
	while (true) {

		// Move left index (at least once).
		do {
			i++;
			highlight->get(0).index = i;
			displayArray(array, SIZE, highlight, horizontalBar);
			sleep_for(delay);
		} while (compare(array[i], pivot) && i < SIZE);

		// Move right index (at least once).
		do {
			j--;
			highlight->get(1).index = j;
			displayArray(array, SIZE, highlight, horizontalBar);
			sleep_for(delay);
		} while (compare(pivot, array[j]) && j >= 0);

		// If the indices crossed, return pivot index.
		if (i >= j) {
			return j;
		}

		// Show array before swapping.
		displayArray(array, SIZE, highlight, horizontalBar);
		sleep_for(delay);

		// Swap left and right.
		swap(array[i], array[j]);

		// If pivot was swapped, update highlight index.
		if (highlight->get(2).index == i) {
			highlight->get(2).index = j;
		} else if (highlight->get(2).index == j) {
			highlight->get(2).index = i;
		}

		// Display array after swapping.
		displayArray(array, SIZE, highlight, horizontalBar);
		sleep_for(delay);
	}
}



// Shell Sort the array.
void Sorting::shellSort(uint array[], const uint SIZE) {
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('R'));
	highlight->add(Highlight('R'));
	bool swapped;

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Marcin Ciura's gap sequence.
	uint gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};

	// Start with largest gap and work down to 1.
	for (uint gap : gaps) {

		// Iterate from gap to SIZE-1.
		for (size_t i = gap; i < SIZE; i++) {
			swapped = false;

			// Do the gapped insertion sort.
			size_t j = i;
			while (j >= gap && compare(array[j], array[j-gap])) {
				highlight->get(0).index = j-gap;
				highlight->get(1).index = j;
				displayArray(array, SIZE, highlight);
				sleep_for(delay);
				swap(array[j], array[j-gap]);
				displayArray(array, SIZE, highlight);
				sleep_for(delay);
				swapped = true;
				j -= gap;
			}

			// Only print if no swap occurred.
			if (!swapped) {
				highlight->get(0).index = i-gap;
				highlight->get(1).index = i;
				displayArray(array, SIZE, highlight);
				sleep_for(delay);
			}
		}
	}

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);

	// Delete dynamic memory.
	delete highlight;
}



// Merge Sort the array.
void Sorting::mergeSort(uint array[], const uint SIZE) {

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Temporary array for copying.
	uint copy[SIZE];

	// Call the recursive split function.
	split(array, copy, SIZE, 0, SIZE);

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);
}


// The function to recursively split the array for Merge Sort.
void Sorting::split(
	uint array[], uint copy[], const uint& SIZE,
	uint start, uint end) {

	// Stopping condition.
	if (end - start <= 1) {
		return;
	}

	// Grey out all entries before start and after end.
	uint middle = (start + end) / 2;
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	for (size_t i = 0; i < start; i++)
		highlight->add(Highlight('x', i));
	for (size_t i = end; i < SIZE; i++)
		highlight->add(Highlight('x', i));

	// Display the array portion.
	displayArray(array, SIZE, highlight);
	sleep_for(delay);

	// Split into left and right halves.
	split(array, copy, SIZE, start, middle);
	split(array, copy, SIZE, middle, end);

	// Merge the current array.
	merge(array, copy, SIZE, start, middle, end, highlight);

	// Delete dynamic memory.
	delete highlight;
}


// Merge the array again.
void Sorting::merge(
	uint array[], uint copy[], const uint& SIZE,
	uint start, uint middle, uint end,
	LinkedList<Highlight>* highlight) {

	// Configure the moving indices and red highlights.
	size_t i = start, j = middle;
	highlight->insert(0, Highlight('R', j));
	highlight->insert(0, Highlight('R', i));

	// Merge array into copy from start to end.
	for (size_t k = start; k < end; k++) {

		// Display the comparison.
		displayArray(array, SIZE, highlight);
		sleep_for(delay);
		if (i < middle && (j >= end || compare(array[i], array[j]))) {
			copy[k] = array[i];
			i++;
			highlight->get(0).index++;
		} else {
			copy[k] = array[j];
			j++;
			highlight->get(1).index++;
		}
	}

	// Copy back into original array.
	highlight->removeAt(0);
	highlight->removeAt(0);
	for (size_t k = start; k < end; k++) {
		displayArray(array, SIZE, highlight);
		sleep_for(delay);
		array[k] = copy[k];
		highlight->insert(0, Highlight('G', k));
	}
	displayArray(array, SIZE, highlight);
	sleep_for(delay);
}



// Comb Sort the array.
void Sorting::combSort(uint array[], const uint SIZE) {
	LinkedList<Highlight>* highlight = new LinkedList<Highlight>();
	highlight->add(Highlight('R'));
	highlight->add(Highlight('R'));
	uint gap = SIZE;
	bool sorted = false;

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Loop for all gaps.
	while (!sorted) {
		gap = int(gap / 1.3);
		if (gap <= 1) {
			gap = 1;
			sorted = true;
		}

		// Bubble Sort with the current gap.
		for (size_t i = 0, j = gap; j < SIZE; i++, j++) {

			// Highlight indices before and after swapping.
			highlight->get(0).index = i;
			highlight->get(1).index = j;
			displayArray(array, SIZE, highlight);
			sleep_for(delay);
			if (compare(array[j], array[i])) {
				swap(array[j], array[i]);
				sorted = false;
				displayArray(array, SIZE, highlight);
				sleep_for(delay);
			}
		}
	}

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);

	// Delete dynamic memory.
	delete highlight;
}
