#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "sorting.h"
#include "../colour_text/colour_text.h"
#include "../math/math.h"
#include "../move_cursor/move_cursor.h"
#include "../priority_queue/priority_queue.h"
using namespace std;


// Set static member values.
bool Sorting::sortAscending = true;
Duration Sorting::delay = milliseconds(50);
unsigned Sorting::barHeight = 40;
unsigned Sorting::barWidth = 2;
unsigned Sorting::wideBarWidth = 2;
unsigned Sorting::verticalScale = 1;
unsigned Sorting::displayHeight = 40;
string Sorting::bars[] = {"██ ", "▄▄ ", "   "};


// Resets sorting and display configuration back to default.
void Sorting::restoreDefault() {
	sortAscending = true;
	delay = milliseconds(50);
	barHeight = 40;
	barWidth = 2;
	wideBarWidth = 2;
	verticalScale = 1;
	displayHeight = 40;
	bars[0] = "██ ";
	bars[1] = "▄▄ ";
	bars[2] = "   ";
}


// Generates the vertical bars with correct widths.
void Sorting::generateBars() {
	bars[0] = " ";
	bars[1] = " ";
	bars[2] = " ";
	for (unsigned i = 0; i < barWidth; i++) {
		bars[0] = "█" + bars[0];
		bars[1] = "▄" + bars[1];
		bars[2] = " " + bars[2];
	}
}


// Toggles between a width of 1 and a width of 2.
void Sorting::toggleWideBar() {
	barWidth = (barWidth == 1 ? wideBarWidth : 1);
	generateBars();
}


// Calibrates the bar height and vertical scale.
void Sorting::calibrateHeightAndScale() {
	displayHeight = ceil(barHeight / (verticalScale*2.0));
	barHeight = displayHeight * verticalScale * 2;
	barHeight += (barHeight % verticalScale);
}


// Updates the current bar width.
void Sorting::setBarWidth(unsigned maxValue) {
	wideBarWidth = 1;
	if (maxValue >= 10) {
		wideBarWidth += log10(maxValue);
	}
	if (barWidth > 1) {
		barWidth = wideBarWidth;
		generateBars();
	}
}


// Update the display bar height.
void Sorting::setBarHeight(unsigned height) {
	barHeight = height;
	calibrateHeightAndScale();
}


// Sets the vertical display scale.
void Sorting::setVerticalScale(unsigned scale) {
	verticalScale = scale;
	calibrateHeightAndScale();
}


// Sets the delay in milliseconds.
void Sorting::setDelay(unsigned ms) {
	delay = milliseconds(ms);
}


// Returns the current bar width.
unsigned Sorting::getBarWidth() {
	return barWidth;
}


// Returns the vertical display scale.
unsigned Sorting::getVerticalScale() {
	return verticalScale;
}


// Returns the delay in milliseconds.
unsigned Sorting::getDelay() {
	return delay.count();
}


// Prints either the top or bottom border.
void Sorting::printBorder(string symbol, const unsigned& SIZE) {
	for (unsigned i = 1; i < SIZE; i++) {
		for (unsigned j = 0; j <= barWidth; j++) {
			cout << symbol;
		}
	}
	for (unsigned i = 0; i < barWidth; i++) {
		cout << symbol;
	}
	cout << endl;
}


// Update the given value according to the vertical scale.
unsigned Sorting::scaleVertically(unsigned value) {
	value = ceil(double(value) / verticalScale);
	value *= verticalScale;
	return value + (value % verticalScale);
}


// Displays the array content as pillars.
void Sorting::displayArray(
	unsigned array[], const unsigned& SIZE,
	Highlights* highlight,
	unsigned horizontalBar) {

	// Update horizontal bar for display.
	if (horizontalBar > 0) {
		horizontalBar = scaleVertically(horizontalBar);
	}

	// Make all entries bright white.
	char colour[SIZE];
	for (unsigned i = 0; i < SIZE; i++) {
		colour[i] = 'w';
	}

	// Configure the provided highlight colours.
	if (highlight) {
		Highlight entry;
		highlight->resetNext();
		for (unsigned i = 0; i < highlight->size(); i++) {
			entry = highlight->getNext();
			colour[entry.index] = entry.colour;
		}
	}

	// Move the cursor back to top left.
	positionCursor(0, 0);

	// Above the bars.
	printBorder("┴", SIZE);

	// Configure the horizontal bar shape.
	string vBar, hBar;
	unsigned N = ceil(horizontalBar / double(verticalScale));
	hBar = (N % 2 == 0 ? "▀" : "▄");

	// Iterate through all layers.
	N = verticalScale*2;
	unsigned value = 0;
	for (unsigned n = barHeight; n > 0; n -= N) {
		for (unsigned i = 0; i < SIZE; i++) {

			// Modify value for display.
			value = scaleVertically(array[i]);

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
					for (unsigned j = 0; j <= barWidth; j++) {
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
		stringstream number;
		for (unsigned i = 0; i < SIZE; i++) {
			number.str("");
			number << setfill('0') << setw(barWidth) << array[i];
			text = colourText(number.str(), colour[i]);
			cout << setw(11+barWidth) << text << " ";
		}
		cout << endl;
	}

	// Below the numbers.
	printBorder("┬", SIZE);
	cout << endl;
}



// Ascending order:   returns status of left < right.
// Descending order:  returns status of left > right.
bool Sorting::compare(unsigned left, unsigned right) {
	if (sortAscending)
		return left < right;
	return left > right;
}



// Bubble sort the given array.
void Sorting::bubbleSort(unsigned array[], const unsigned& SIZE) {
	Highlights* highlight = new Highlights();
	highlight->append(Highlight('b'));
	highlight->append(Highlight('b'));

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Indicate update which element to sort.
	bool swapped;
	for (unsigned n = SIZE; n > 0; n--) {
		swapped = false;
		if (n < SIZE) {
			highlight->append(Highlight('G', n));
		}
		for (unsigned i = 1; i < n; i++) {
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
void Sorting::selectionSort(unsigned array[], const unsigned& SIZE) {
	Highlights* highlight = new Highlights();
	highlight->append(Highlight('b'));
	highlight->append(Highlight('b'));
	highlight->append(Highlight('R'));

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Indicate the starting index.
	bool isSorted;
	unsigned minIndex;
	for (unsigned i = 0; i < SIZE-1; i++) {
		highlight->get(2).index = i;
		minIndex = i;
		isSorted = true;
		for (unsigned j = i+1; j < SIZE; j++) {
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

			// Update is sorted status.
			if (compare(array[j], array[j-1])) {
				isSorted = false;
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

		// Break loop if already sorted.
		if (isSorted) {
			break;
		}

		// Alter list for next comparison.
		highlight->get(0).colour = 'b';
		highlight->insert(Highlight('b'));
		highlight->append(Highlight('G', i));
	}

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);

	// Delete dynamic memory.
	delete highlight;
}



// Insertion sort the given array.
void Sorting::insertionSort(unsigned array[], const unsigned& SIZE) {
	Highlights* highlight = new Highlights();
	highlight->append(Highlight('b'));
	highlight->append(Highlight('b'));
	bool swapped;

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Iterate starting from the second element.
	for (unsigned i = 1; i < SIZE; i++) {
		swapped = false;

		// Loop while swapping is needed.
		unsigned j = i;
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
void Sorting::cocktailShakerSort(unsigned array[], const unsigned& SIZE) {
	Highlights* highlight = new Highlights();
	highlight->append(Highlight('b'));
	highlight->append(Highlight('b'));

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Loop while a swap has occurred.
	unsigned start = 0, end = SIZE;
	bool swapped;
	do {

		// Iterate forwards.
		swapped = false;
		for (unsigned i = start+1; i < end; i++) {
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
		highlight->append(Highlight('G', end));

		// Break if no swap occurred.
		if (!swapped) {
			break;
		}

		// Iterate backwards.
		swapped = false;
		for (unsigned i = end-1; i > start; i--) {
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
		highlight->append(Highlight('G', start));
		start++;

	} while (swapped);

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);

	// Delete dynamic memory.
	delete highlight;
}



// Gnome Sort the array.
void Sorting::gnomeSort(unsigned array[], const unsigned& SIZE) {

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Start sorting.
	unsigned index = 1;
	while (index < SIZE) {

		// Move forwards.
		if (index == 0 || !compare(array[index], array[index-1])) {
			index++;
		}

		// Move backwards and swap.
		else {
			swap(array[index], array[index-1]);
			index--;
		}
	}

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);
}



// Quick Sort the array.
void Sorting::quickSort(unsigned array[], const unsigned& SIZE) {

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
	unsigned array[], const int& SIZE, int low, int high) {

	// Stopping condition.
	if (low > high || low < 0) {
		return;
	}

	// Configure all highlights.
	Highlights* highlight = new Highlights();
	highlight->append(Highlight('b', low));
	highlight->append(Highlight('b'));
	highlight->append(Highlight('R', high));
	for (int i = 0; i < low; i++) {
		highlight->append(Highlight('x', i));
	}
	for (int i = high+1; i < SIZE; i++) {
		highlight->append(Highlight('x', i));
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
	unsigned array[], const int& SIZE, int low, int high,
	Highlights* highlight) {

	// Pivot is the last element.
	unsigned pivot = array[high];
	unsigned horizontalBar = pivot;
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
			highlight->append(Highlight('G', i));
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
void Sorting::quickSortV2(unsigned array[], const unsigned& SIZE) {

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
	unsigned array[], const int& SIZE, int low, int high) {

	// Stopping condition.
	if (low >= high || low < 0 || high < 0) {
		return;
	}

	// Configure all highlights.
	Highlights* highlight = new Highlights();
	highlight->append(Highlight('b', low));
	highlight->append(Highlight('b'));
	for (int i = 0; i < low; i++) {
		highlight->append(Highlight('x', i));
	}
	for (int i = high+1; i < SIZE; i++) {
		highlight->append(Highlight('x', i));
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
	unsigned array[], const int& SIZE, int low, int high,
	Highlights* highlight) {

	// Pivot is the middle element.
	unsigned middle = ((high - low) / 2) + low;
	unsigned pivot = array[middle];
	unsigned horizontalBar = pivot;
	highlight->append(Highlight('R', middle));

	// Left index.
	int i = low - 1;

	// Right index.
	int j = high + 1;

	// Loop until left and right cross.
	while (true) {

		// Move left index (at least once).
		do {
			if (i >= 0) {
				highlight->append(Highlight('G', i));
			}
			i++;
			highlight->get(0).index = i;
			displayArray(array, SIZE, highlight, horizontalBar);
			sleep_for(delay);
		} while (compare(array[i], pivot) && i < SIZE);

		// Move right index (at least once).
		do {
			if (j <= high) {
				highlight->append(Highlight('G', j));
			}
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

		// Display array after swapping.
		displayArray(array, SIZE, highlight, horizontalBar);
		sleep_for(delay);
	}
}



// Shell Sort the array.
void Sorting::shellSort(unsigned array[], const unsigned& SIZE) {
	Highlights* highlight = new Highlights();
	highlight->append(Highlight('R'));
	highlight->append(Highlight('R'));
	bool sorted = false;
	bool swapped;

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Start with largest gap and work down to 1.
	unsigned gap = SIZE;
	while (!sorted) {
		gap /= 2.3;
		if (gap <= 1) {
			gap = 1;
			sorted = true;
		}

		// Iterate from gap to SIZE-1.
		for (unsigned i = gap; i < SIZE; i++) {
			swapped = false;

			// Do the gapped insertion sort.
			unsigned j = i;
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
void Sorting::mergeSort(unsigned array[], const unsigned& SIZE) {

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Temporary array for copying.
	unsigned copy[SIZE];

	// Call the recursive split function.
	split(array, copy, SIZE, 0, SIZE);

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);
}


// The function to recursively split the array for Merge Sort.
void Sorting::split(
	unsigned array[], unsigned copy[], const unsigned& SIZE,
	unsigned start, unsigned end) {

	// Stopping condition.
	if (end - start <= 1) {
		return;
	}

	// Grey out all entries before start and after end.
	unsigned middle = (start + end) / 2;
	Highlights* highlight = new Highlights();
	for (unsigned i = 0; i < start; i++)
		highlight->append(Highlight('x', i));
	for (unsigned i = end; i < SIZE; i++)
		highlight->append(Highlight('x', i));

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
	unsigned array[], unsigned copy[], const unsigned& SIZE,
	unsigned start, unsigned middle, unsigned end,
	Highlights* highlight) {

	// Configure the moving indices and red highlights.
	unsigned i = start, j = middle;
	highlight->insert(Highlight('R', j));
	highlight->insert(Highlight('R', i));

	// Merge array into copy from start to end.
	for (unsigned k = start; k < end; k++) {

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
	for (unsigned k = start; k < end; k++) {
		displayArray(array, SIZE, highlight);
		sleep_for(delay);
		array[k] = copy[k];
		highlight->insert(Highlight('G', k));
	}
	displayArray(array, SIZE, highlight);
	sleep_for(delay);
}



// Comb Sort the array.
void Sorting::combSort(unsigned array[], const unsigned& SIZE) {
	Highlights* highlight = new Highlights();
	highlight->append(Highlight('R'));
	highlight->append(Highlight('R'));
	bool sorted = false;

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Loop for all gaps.
	unsigned gap = SIZE;
	while (!sorted) {
		gap = int(gap / 1.3);
		if (gap <= 1) {
			gap = 1;
			sorted = true;
		}

		// Bubble Sort with the current gap.
		for (unsigned i = 0, j = gap; j < SIZE; i++, j++) {

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



// Radix Sort the array using the specified base.
void Sorting::radixSort(unsigned array[], const unsigned& SIZE, const unsigned BASE) {
	Highlights* highlight = new Highlights();

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Get the number of digits from the maximum value.
	unsigned maxValue = max(array, SIZE);
	unsigned numDigits = 1;
	if (maxValue >= BASE) {
		numDigits += log(BASE, maxValue);
	}

	// Create counting array and copy of original array.
	unsigned count[BASE];
	unsigned copy[SIZE];

	// Iterate through all digits.
	for (unsigned d, n = 0, digit = 1; n < numDigits; n++, digit *= BASE) {
		highlight->append(Highlight('b'));

		// Reset the counting array.
		for (unsigned i = 0; i < BASE; i++) {
			count[i] = 0;
		}

		// Iterate through all elements in the array.
		for (unsigned i = 0; i < SIZE; i++) {
			copy[i] = array[i];

			// Show current comparison.
			highlight->getFirst().index = i;
			displayArray(array, SIZE, highlight);
			sleep_for(delay);

			// Determine the current digit.
			d = (array[i] / digit) % BASE;

			// Invert digit if descending order.
			if (!sortAscending) {
				d = BASE - 1 - d;
			}

			// Increment the respective count.
			count[d]++;
		}

		// Display before swapping.
		displayArray(array, SIZE);
		sleep_for(delay);

		// Increment each subsequent count.
		for (unsigned i = 1; i < BASE; i++) {
			count[i] += count[i-1];
		}

		// Copy the sorted elements back into the original array.
		highlight->clear();
		for (int i = SIZE-1; i >= 0; i--) {

			// Determine the current digit.
			d = (copy[i] / digit) % BASE;

			// Invert digit if descending order.
			if (!sortAscending) {
				d = BASE - 1 - d;
			}

			// Copy to array.
			count[d]--;
			array[count[d]] = copy[i];

			// Show array after copy.
			highlight->append(Highlight('G', count[d]));
			displayArray(array, SIZE, highlight);
			sleep_for(delay);
		}

		// Display the array after copying all.
		highlight->clear();
		displayArray(array, SIZE);
		sleep_for(delay);
	}

	// Delete dynamic memory.
	delete highlight;
}



// Heap Sort the array.
void Sorting::heapSort(unsigned array[], const unsigned& SIZE) {
	Highlights* highlight = new Highlights();
	highlight->append(Highlight('R'));
	highlight->append(Highlight('R'));

	// The colours for various heap heights.
	char colours[] = {'m', 'y', 'c', 'M', 'C'};
	unsigned index;

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Get index of last non-leaf node.
	int node = SIZE / 2 - 1;

	// Highlight all entries after node.
	for (int i = SIZE-1; i > node; i--) {
		index = int(log2(i+1)) % 5;
		highlight->insert(Highlight(colours[index], i));
		displayArray(array, SIZE, highlight);
		sleep_for(delay);
	}

	// Heapify the whole array.
	for (int i = node; i >= 0; i--) {
		heapify(array, SIZE, SIZE, i, highlight);

		// Highlight parents already considered.
		index = int(log2(i+1)) % 5;
		highlight->insert(Highlight(colours[index], i));
	}

	// Sort by continuously popping from the heap.
	for (unsigned end = SIZE-1; end > 0; end--) {

		// Show the array before and after swapping.
		highlight->get(-1).index = end;
		highlight->get(-2).index = 0;
		displayArray(array, SIZE, highlight);
		sleep_for(delay);
		swap(array[0], array[end]);
		displayArray(array, SIZE, highlight);
		sleep_for(delay);

		// Call heapify for up to end elements.
		highlight->get(end).colour = 'G';
		heapify(array, SIZE, end, 0, highlight);
	}

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);

	// Delete dynamic memory.
	delete highlight;
}


// Recursively heapify the array at the given index.
void Sorting::heapify(
	unsigned array[], const unsigned& SIZE, unsigned end,
	unsigned parentIndex, Highlights* highlight) {

	// The index of the lowest non-leaf node.
	unsigned lowestNoneLeaf = end / 2 - 1;

	// Iterate for all children.
	unsigned left, right, criticalIndex;
	while (parentIndex <= lowestNoneLeaf) {

		// Depending on sorting order is index of either
		// max or min value.
		criticalIndex = parentIndex;

		// Calculate left and right child indices.
		left = 2*parentIndex + 1;
		right = 2*parentIndex + 2;

		// Check if right must be swapped.
		if (right < end &&
			compare(array[criticalIndex], array[right])) {
			criticalIndex = right;
		}

		// Check if left must be swapped.
		if (left < end &&
			compare(array[criticalIndex], array[left])) {
			criticalIndex = left;
		}

		// Display the array before swapping.
		highlight->get(-1).index = criticalIndex;
		highlight->get(-2).index = parentIndex;
		displayArray(array, SIZE, highlight);
		sleep_for(delay);

		// Only swap and trickle down heap
		// if parent is not the critical value.
		if (criticalIndex != parentIndex) {

			// Display the array after swapping.
			swap(array[criticalIndex], array[parentIndex]);
			displayArray(array, SIZE, highlight);
			sleep_for(delay);

			// Update parent index.
			parentIndex = criticalIndex;
		}

		// Break loop otherwise.
		else break;

	}
}



// Bucket Sort the array.
void Sorting::bucketSort(unsigned array[], const unsigned& SIZE) {
	Highlights* highlight = new Highlights();
	highlight->append(Highlight('b'));

	// Display the array before sorting.
	clearScreen();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Get the maximum value in the array plus 1.
	unsigned maxValue = 1 + max(array, SIZE);

	// Get the index ratio.
	double ratio = double(SIZE) / maxValue;

	// Create priority queue array.
	PriorityQueue<unsigned> bucket[SIZE];

	// Iterate through array and push elements to bucket.
	for (unsigned j, i = 0; i < SIZE; i++) {
		j = array[i] * ratio;
		bucket[j].push(array[i]);

		// Show current item.
		highlight->getFirst().index = i;
		displayArray(array, SIZE, highlight);
		sleep_for(delay);
	}

	// Display the array after filling bucket.
	highlight->clear();
	displayArray(array, SIZE);
	sleep_for(delay);

	// Get array starting index based on sorting order.
	int j = (sortAscending ? SIZE-1 : 0);

	// Iterate through bucket and sort array.
	for (int i = SIZE-1; i >= 0; i--) {
		while (!bucket[i].isEmpty()) {
			array[j] = bucket[i].pop();

			// Display update.
			highlight->append(Highlight('G', j));
			displayArray(array, SIZE, highlight);
			sleep_for(delay);

			// Update array index.
			j += (sortAscending ? -1 : 1);
		}
	}

	// Display the array after sorting.
	displayArray(array, SIZE);
	sleep_for(delay);

	// Delete dynamic memory.
	delete highlight;
}
