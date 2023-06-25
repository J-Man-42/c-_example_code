#include <iostream>
#include <iomanip>
#include "sorting.h"
#include "../math/math.h"
#include "../move_cursor/move_cursor.h"
using namespace std;


// Set static member values.
template <class T>
bool Sorting<T>::sortAscending = true;


// Print the time taken.
template <class T>
void Sorting<T>::showTimeTaken(Time start, Time end) {
	
	// Get the duration in milliseconds
	auto duration = duration_cast<milliseconds>(end - start);

	// Get milliseconds, seconds, and minutes.
	uint milliseconds = duration.count();
	uint seconds = milliseconds / 1000;
	uint minutes = seconds / 60;
	seconds %= 60;
	milliseconds %= 100;

	// Print formatted duration.
	cout << "Time taken:  ";
	cout << setfill('0') << setw(2) << minutes << ":";
	cout << setfill('0') << setw(2) << seconds << ".";
	cout << setfill('0') << setw(3) << milliseconds << endl;
}


// Ascending order:   returns status of left < right.
// Descending order:  returns status of left > right.
template <class T>
bool Sorting<T>::compare(T left, T right) {
	if (sortAscending)
		return left < right;
	return left > right;
}


// Bubble sort the given array.
template <class T>
void Sorting<T>::bubbleSort(T array[], const uint& SIZE) {
	cout << "Performing Bubble Sort..." << endl;

	// Record the timestamp before sorting.
	auto start = high_resolution_clock::now();

	// Sort up to last sorted element.
	bool swapped;
	for (size_t n = SIZE; n > 0; n--) {
		swapped = false;
		for (size_t i = 1; i < n; i++) {

			// Swap elements if needed.
			if (compare(array[i], array[i-1])) {
				swap(array[i], array[i-1]);
				swapped = true;
			}
		}

		// Break loop if no swaps occurred.
		if (!swapped) {
			break;
		}
	}

	// Record the timestamp after sorting.
	auto end = high_resolution_clock::now();

	// Print time taken.
	showTimeTaken(start, end);
}



// Selection sort the given array.
template <class T>
void Sorting<T>::selectionSort(T array[], const uint& SIZE) {
	cout << "Performing Selection Sort..." << endl;

	// Record the timestamp before sorting.
	auto start = high_resolution_clock::now();

	// Indicate the starting index.
	bool isSorted;
	size_t minIndex;
	for (size_t i = 0; i < SIZE-1; i++) {
		minIndex = i;
		isSorted = true;
		for (size_t j = i+1; j < SIZE; j++) {

			// New critical value.
			if (compare(array[j], array[minIndex])) {
				minIndex = j;
			}

			// Update is sorted status.
			if (compare(array[j], array[j-1])) {
				isSorted = false;
			}
		}

		// Only swap if needed.
		if (minIndex != i) {
			swap(array[i], array[minIndex]);
		}

		// Break loop if already sorted.
		if (isSorted) {
			break;
		}
	}

	// Record the timestamp after sorting.
	auto end = high_resolution_clock::now();

	// Print time taken.
	showTimeTaken(start, end);
}



// Insertion sort the given array.
template <class T>
void Sorting<T>::insertionSort(T array[], const uint& SIZE) {
	cout << "Performing Insertion Sort..." << endl;

	// Record the timestamp before sorting.
	auto start = high_resolution_clock::now();

	// Iterate starting from the second element.
	for (size_t i = 1; i < SIZE; i++) {

		// Loop while swapping is needed.
		size_t j = i;
		while (j > 0 && compare(array[j], array[j-1])) {
			swap(array[j], array[j-1]);
			j--;
		}
	}

	// Record the timestamp after sorting.
	auto end = high_resolution_clock::now();

	// Print time taken.
	showTimeTaken(start, end);
}



// Cocktail shaker sort the given array.
template <class T>
void Sorting<T>::cocktailShakerSort(T array[], const uint& SIZE) {
	cout << "Performing Cocktail Shaker Sort..." << endl;

	// Record the timestamp before sorting.
	auto startTime = high_resolution_clock::now();

	// Loop while a swap has occurred.
	size_t start = 0, end = SIZE;
	bool swapped;
	do {

		// Iterate forwards.
		swapped = false;
		for (size_t i = start+1; i < end; i++) {

			// Swap elements if needed.
			if (compare(array[i], array[i-1])) {
				swap(array[i], array[i-1]);
				swapped = true;
			}
		}
		end--;

		// Break if no swap occurred.
		if (!swapped) {
			break;
		}

		// Iterate backwards.
		swapped = false;
		for (size_t i = end-1; i > start; i--) {

			// Swap elements.
			if (compare(array[i], array[i-1])) {
				swap(array[i], array[i-1]);
				swapped = true;
			}
		}
		start++;

	} while (swapped);

	// Record the timestamp after sorting.
	auto endTime = high_resolution_clock::now();

	// Print time taken.
	showTimeTaken(startTime, endTime);
}



// Quick Sort the array.
template <class T>
void Sorting<T>::quickSort(T array[], const uint& SIZE) {
	cout << "Performing Quick Sort..." << endl;

	// Record the timestamp before sorting.
	auto start = high_resolution_clock::now();

	// QuickSort.
	quickSort(array, 0, SIZE-1);

	// Record the timestamp after sorting.
	auto end = high_resolution_clock::now();

	// Print time taken.
	showTimeTaken(start, end);
}


// The hidden recursive Quick Sort function.
template <class T>
void Sorting<T>::quickSort(T array[], int low, int high) {

	// Stopping condition.
	if (low > high || low < 0) {
		return;
	}

	// Partition array and get the pivot index.
	int pivotIndex = partition(array, low, high);

	// Sort the two partitions.
	quickSort(array, low, pivotIndex-1);
	quickSort(array, pivotIndex+1, high);
}


// The partition function for Quick Sort.
template <class T>
int Sorting<T>::partition(T array[], int low, int high) {

	// Pivot is the last element.
	uint pivot = array[high];

	// Temporary pivot index.
	int i = low - 1;

	// Iterate from low to high.
	for (int j = low; j < high; j++) {

		// Swap if needed.
		if (compare(array[j], pivot)) {
			i++;
			swap(array[i], array[j]);
		}
	}

	// Final swap, then return pivot index.
	i++;
	if (array[i] != array[high]) {
	    swap(array[i], array[high]);
	}

	// Delete dynamic memory and return pivot index.
	return i;
}



// Quick Sort the array.
template <class T>
void Sorting<T>::quickSortV2(T array[], const uint& SIZE) {

	// // Display the array before sorting.
	// clearScreen();
	// displayArray(array, SIZE);
	// sleep_for(delay);

	// // QuickSort.
	// quickSortV2(array, SIZE, 0, SIZE-1);

	// // Display the array after sorting.
	// displayArray(array, SIZE);
	// sleep_for(delay);
}


// The hidden recursive Quick Sort function.
template <class T>
void Sorting<T>::quickSortV2(
	T array[], const int& SIZE, int low, int high) {

	// // Stopping condition.
	// if (low >= high || low < 0 || high < 0) {
	// 	return;
	// }

	// // Configure all highlights.
	// Highlights* highlight = new Highlights();
	// highlight->append(Highlight('R', low));
	// highlight->append(Highlight('R'));
	// for (int i = 0; i < low; i++) {
	// 	highlight->append(Highlight('x', i));
	// }
	// for (int i = high+1; i < SIZE; i++) {
	// 	highlight->append(Highlight('x', i));
	// }

	// // Partition array and get the pivot index.
	// int pivotIndex = partitionV2(array, SIZE, low, high, highlight);

	// // Sort the two partitions.
	// quickSortV2(array, SIZE, low, pivotIndex);
	// quickSortV2(array, SIZE, pivotIndex+1, high);

	// // Delete dynamic memory.
	// delete highlight;
}


// The partition function for Quick Sort.
template <class T>
int Sorting<T>::partitionV2(
	T array[], const int& SIZE, int low, int high) {

	// // Pivot is the middle element.
	// uint middle = ((high - low) / 2) + low;
	// uint pivot = array[middle];
	// uint horizontalBar = pivot;

	// // Left index.
	// int i = low - 1;

	// // Right index.
	// int j = high + 1;

	// // Loop until left and right cross.
	// while (true) {

	// 	// Move left index (at least once).
	// 	do {
	// 		if (i >= 0) {
	// 			highlight->append(Highlight('G', i));
	// 		}
	// 		i++;
	// 		highlight->get(0).index = i;
	// 		displayArray(array, SIZE, highlight, horizontalBar);
	// 		sleep_for(delay);
	// 	} while (compare(array[i], pivot) && i < SIZE);

	// 	// Move right index (at least once).
	// 	do {
	// 		if (j <= high) {
	// 			highlight->append(Highlight('G', j));
	// 		}
	// 		j--;
	// 		highlight->get(1).index = j;
	// 		displayArray(array, SIZE, highlight, horizontalBar);
	// 		sleep_for(delay);
	// 	} while (compare(pivot, array[j]) && j >= 0);

	// 	// If the indices crossed, return pivot index.
	// 	if (i >= j) {
	// 		return j;
	// 	}

	// 	// Show array before swapping.
	// 	displayArray(array, SIZE, highlight, horizontalBar);
	// 	sleep_for(delay);

	// 	// Swap left and right.
	// 	swap(array[i], array[j]);

	// 	// Display array after swapping.
	// 	displayArray(array, SIZE, highlight, horizontalBar);
	// 	sleep_for(delay);
	// }
}



// Shell Sort the array.
template <class T>
void Sorting<T>::shellSort(T array[], const uint& SIZE) {
	// Highlights* highlight = new Highlights();
	// highlight->append(Highlight('R'));
	// highlight->append(Highlight('R'));
	// bool swapped;

	// // Display the array before sorting.
	// clearScreen();
	// displayArray(array, SIZE);
	// sleep_for(delay);

	// // Marcin Ciura's gap sequence.
	// uint gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};

	// // Start with largest gap and work down to 1.
	// for (uint gap : gaps) {

	// 	// Iterate from gap to SIZE-1.
	// 	for (size_t i = gap; i < SIZE; i++) {
	// 		swapped = false;

	// 		// Do the gapped insertion sort.
	// 		size_t j = i;
	// 		while (j >= gap && compare(array[j], array[j-gap])) {
	// 			highlight->get(0).index = j-gap;
	// 			highlight->get(1).index = j;
	// 			displayArray(array, SIZE, highlight);
	// 			sleep_for(delay);
	// 			swap(array[j], array[j-gap]);
	// 			displayArray(array, SIZE, highlight);
	// 			sleep_for(delay);
	// 			swapped = true;
	// 			j -= gap;
	// 		}

	// 		// Only print if no swap occurred.
	// 		if (!swapped) {
	// 			highlight->get(0).index = i-gap;
	// 			highlight->get(1).index = i;
	// 			displayArray(array, SIZE, highlight);
	// 			sleep_for(delay);
	// 		}
	// 	}
	// }

	// // Display the array after sorting.
	// displayArray(array, SIZE);
	// sleep_for(delay);

	// // Delete dynamic memory.
	// delete highlight;
}



// Merge Sort the array.
template <class T>
void Sorting<T>::mergeSort(T array[], const uint& SIZE) {

	// // Display the array before sorting.
	// clearScreen();
	// displayArray(array, SIZE);
	// sleep_for(delay);

	// // Temporary array for copying.
	// uint copy[SIZE];

	// // Call the recursive split function.
	// split(array, copy, SIZE, 0, SIZE);

	// // Display the array after sorting.
	// displayArray(array, SIZE);
	// sleep_for(delay);
}


// The function to recursively split the array for Merge Sort.
template <class T>
void Sorting<T>::split(
	T array[], T copy[], const uint& SIZE,
	uint start, uint end) {

	// // Stopping condition.
	// if (end - start <= 1) {
	// 	return;
	// }

	// // Grey out all entries before start and after end.
	// uint middle = (start + end) / 2;
	// Highlights* highlight = new Highlights();
	// for (size_t i = 0; i < start; i++)
	// 	highlight->append(Highlight('x', i));
	// for (size_t i = end; i < SIZE; i++)
	// 	highlight->append(Highlight('x', i));

	// // Display the array portion.
	// displayArray(array, SIZE, highlight);
	// sleep_for(delay);

	// // Split into left and right halves.
	// split(array, copy, SIZE, start, middle);
	// split(array, copy, SIZE, middle, end);

	// // Merge the current array.
	// merge(array, copy, SIZE, start, middle, end, highlight);

	// // Delete dynamic memory.
	// delete highlight;
}


// Merge the array again.
template <class T>
void Sorting<T>::merge(
	T array[], T copy[], const uint& SIZE,
	uint start, uint middle, uint end) {

	// // Configure the moving indices and red highlights.
	// size_t i = start, j = middle;
	// highlight->insert(Highlight('R', j));
	// highlight->insert(Highlight('R', i));

	// // Merge array into copy from start to end.
	// for (size_t k = start; k < end; k++) {

	// 	// Display the comparison.
	// 	displayArray(array, SIZE, highlight);
	// 	sleep_for(delay);
	// 	if (i < middle && (j >= end || compare(array[i], array[j]))) {
	// 		copy[k] = array[i];
	// 		i++;
	// 		highlight->get(0).index++;
	// 	} else {
	// 		copy[k] = array[j];
	// 		j++;
	// 		highlight->get(1).index++;
	// 	}
	// }

	// // Copy back into original array.
	// highlight->removeAt(0);
	// highlight->removeAt(0);
	// for (size_t k = start; k < end; k++) {
	// 	displayArray(array, SIZE, highlight);
	// 	sleep_for(delay);
	// 	array[k] = copy[k];
	// 	highlight->insert(Highlight('G', k));
	// }
	// displayArray(array, SIZE, highlight);
	// sleep_for(delay);
}



// Comb Sort the array.
template <class T>
void Sorting<T>::combSort(T array[], const uint& SIZE) {
	// Highlights* highlight = new Highlights();
	// highlight->append(Highlight('R'));
	// highlight->append(Highlight('R'));
	// uint gap = SIZE;
	// bool sorted = false;

	// // Display the array before sorting.
	// clearScreen();
	// displayArray(array, SIZE);
	// sleep_for(delay);

	// // Loop for all gaps.
	// while (!sorted) {
	// 	gap = int(gap / 1.3);
	// 	if (gap <= 1) {
	// 		gap = 1;
	// 		sorted = true;
	// 	}

	// 	// Bubble Sort with the current gap.
	// 	for (size_t i = 0, j = gap; j < SIZE; i++, j++) {

	// 		// Highlight indices before and after swapping.
	// 		highlight->get(0).index = i;
	// 		highlight->get(1).index = j;
	// 		displayArray(array, SIZE, highlight);
	// 		sleep_for(delay);
	// 		if (compare(array[j], array[i])) {
	// 			swap(array[j], array[i]);
	// 			sorted = false;
	// 			displayArray(array, SIZE, highlight);
	// 			sleep_for(delay);
	// 		}
	// 	}
	// }

	// // Display the array after sorting.
	// displayArray(array, SIZE);
	// sleep_for(delay);

	// // Delete dynamic memory.
	// delete highlight;
}



// Radix Sort the array using the specified base.
template <class T>
void Sorting<T>::radixSort(T array[], const uint& SIZE, const uint BASE) {
	// Highlights* highlight = new Highlights();

	// // Display the array before sorting.
	// clearScreen();
	// displayArray(array, SIZE);
	// sleep_for(delay);

	// // Get the number of digits from the maximum value.
	// uint maxValue = max(array, SIZE);
	// uint numDigits = 1;
	// if (maxValue >= BASE) {
	// 	numDigits += log(BASE, maxValue);
	// }

	// // Create counting array and copy of original array.
	// uint count[BASE];
	// uint copy[SIZE];

	// // Iterate through all digits.
	// for (size_t d, n = 0, digit = 1; n < numDigits; n++, digit *= BASE) {
	// 	highlight->append(Highlight('b'));

	// 	// Reset the counting array.
	// 	for (size_t i = 0; i < BASE; i++) {
	// 		count[i] = 0;
	// 	}

	// 	// Iterate through all elements in the array.
	// 	for (size_t i = 0; i < SIZE; i++) {
	// 		copy[i] = array[i];

	// 		// Show current comparison.
	// 		highlight->getFirst().index = i;
	// 		displayArray(array, SIZE, highlight);
	// 		sleep_for(delay);

	// 		// Determine the current digit.
	// 		d = (array[i] / digit) % BASE;

	// 		// Invert digit if descending order.
	// 		if (!sortAscending) {
	// 			d = BASE - 1 - d;
	// 		}

	// 		// Increment the respective count.
	// 		count[d]++;
	// 	}

	// 	// Display before swapping.
	// 	displayArray(array, SIZE);
	// 	sleep_for(delay);

	// 	// Increment each subsequent count.
	// 	for (size_t i = 1; i < BASE; i++) {
	// 		count[i] += count[i-1];
	// 	}

	// 	// Copy the sorted elements back into the original array.
	// 	highlight->clear();
	// 	for (int i = SIZE-1; i >= 0; i--) {

	// 		// Determine the current digit.
	// 		d = (copy[i] / digit) % BASE;

	// 		// Invert digit if descending order.
	// 		if (!sortAscending) {
	// 			d = BASE - 1 - d;
	// 		}

	// 		// Copy to array.
	// 		count[d]--;
	// 		array[count[d]] = copy[i];

	// 		// Show array after copy.
	// 		highlight->append(Highlight('G', count[d]));
	// 		displayArray(array, SIZE, highlight);
	// 		sleep_for(delay);
	// 	}

	// 	// Display the array after copying all.
	// 	highlight->clear();
	// 	displayArray(array, SIZE);
	// 	sleep_for(delay);
	// }

	// // Delete dynamic memory.
	// delete highlight;
}



// Heap Sort the array.
template <class T>
void Sorting<T>::heapSort(T array[], const uint& SIZE) {
	// Highlights* highlight = new Highlights();
	// highlight->append(Highlight('R'));
	// highlight->append(Highlight('R'));

	// // The colours for various heap heights.
	// char colours[] = {'m', 'y', 'c', 'M', 'C'};
	// uint index;

	// // Display the array before sorting.
	// clearScreen();
	// displayArray(array, SIZE);
	// sleep_for(delay);

	// // Get index of last non-leaf node.
	// int node = SIZE / 2 - 1;

	// // Highlight all entries after node.
	// for (int i = SIZE-1; i > node; i--) {
	// 	index = int(log2(i+1)) % 5;
	// 	highlight->insert(Highlight(colours[index], i));
	// 	displayArray(array, SIZE, highlight);
	// 	sleep_for(delay);
	// }

	// // Heapify the whole array.
	// for (int i = node; i >= 0; i--) {
	// 	heapify(array, SIZE, SIZE, i, highlight);

	// 	// Highlight parents already considered.
	// 	index = int(log2(i+1)) % 5;
	// 	highlight->insert(Highlight(colours[index], i));
	// }

	// // Sort by continuously popping from the heap.
	// for (size_t end = SIZE-1; end > 0; end--) {

	// 	// Show the array before and after swapping.
	// 	highlight->get(-1).index = end;
	// 	highlight->get(-2).index = 0;
	// 	displayArray(array, SIZE, highlight);
	// 	sleep_for(delay);
	// 	swap(array[0], array[end]);
	// 	displayArray(array, SIZE, highlight);
	// 	sleep_for(delay);

	// 	// Call heapify for up to end elements.
	// 	highlight->get(end).colour = 'G';
	// 	heapify(array, SIZE, end, 0, highlight);
	// }

	// // Display the array after sorting.
	// displayArray(array, SIZE);
	// sleep_for(delay);

	// // Delete dynamic memory.
	// delete highlight;
}


// Recursively heapify the array at the given index.
template <class T>
void Sorting<T>::heapify(
	T array[], const uint& SIZE, uint end, uint parentIndex) {

	// // The index of the lowest non-leaf node.
	// uint lowestNoneLeaf = end / 2 - 1;

	// // Iterate for all children.
	// uint left, right, criticalIndex;
	// while (parentIndex <= lowestNoneLeaf) {

	// 	// Depending on sorting order is index of either
	// 	// max or min value.
	// 	criticalIndex = parentIndex;

	// 	// Calculate left and right child indices.
	// 	left = 2*parentIndex + 1;
	// 	right = 2*parentIndex + 2;

	// 	// Check if right must be swapped.
	// 	if (right < end &&
	// 		compare(array[criticalIndex], array[right])) {
	// 		criticalIndex = right;
	// 	}

	// 	// Check if left must be swapped.
	// 	if (left < end &&
	// 		compare(array[criticalIndex], array[left])) {
	// 		criticalIndex = left;
	// 	}

	// 	// Display the array before swapping.
	// 	highlight->get(-1).index = criticalIndex;
	// 	highlight->get(-2).index = parentIndex;
	// 	displayArray(array, SIZE, highlight);
	// 	sleep_for(delay);

	// 	// Only swap and trickle down heap
	// 	// if parent is not the critical value.
	// 	if (criticalIndex != parentIndex) {

	// 		// Display the array after swapping.
	// 		swap(array[criticalIndex], array[parentIndex]);
	// 		displayArray(array, SIZE, highlight);
	// 		sleep_for(delay);

	// 		// Update parent index.
	// 		parentIndex = criticalIndex;
	// 	}

	// 	// Break loop otherwise.
	// 	else break;

	// }
}