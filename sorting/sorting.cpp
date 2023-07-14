#include <iostream>
#include <iomanip>
#include <cmath>
#include "sorting.h"
#include "../math/math.h"
#include "../move_cursor/move_cursor.h"
#include "../priority_queue/priority_queue.h"
using namespace std;


// Set static member values.
template<class T>
bool Sorting<T>::sortAscending = true;


// Print the time taken.
template<class T>
void Sorting<T>::showTimeTaken(Time start, Time end) {

	// Get the duration in milliseconds
	auto duration = duration_cast<milliseconds>(end - start);

	// Get milliseconds, seconds, and minutes.
	unsigned milliseconds = duration.count();
	unsigned seconds = milliseconds / 1000;
	unsigned minutes = seconds / 60;
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
template<class T>
bool Sorting<T>::compare(T left, T right) {
	if (sortAscending)
		return left < right;
	return left > right;
}


// Bubble sort the given array.
template<class T>
void Sorting<T>::bubbleSort(T array[], const unsigned& SIZE) {

	// Sort up to last sorted element.
	bool swapped;
	for (unsigned n = SIZE; n > 0; n--) {
		swapped = false;
		for (unsigned i = 1; i < n; i++) {

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
}



// Selection sort the given array.
template<class T>
void Sorting<T>::selectionSort(T array[], const unsigned& SIZE) {

	// Indicate the starting index.
	bool isSorted;
	unsigned minIndex;
	for (unsigned i = 0; i < SIZE-1; i++) {
		minIndex = i;
		isSorted = true;
		for (unsigned j = i+1; j < SIZE; j++) {

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
}



// Insertion sort the given array.
template<class T>
void Sorting<T>::insertionSort(T array[], const unsigned& SIZE) {

	// Iterate starting from the second element.
	for (unsigned i = 1; i < SIZE; i++) {

		// Loop while swapping is needed.
		unsigned j = i;
		while (j > 0 && compare(array[j], array[j-1])) {
			swap(array[j], array[j-1]);
			j--;
		}
	}
}



// Cocktail shaker sort the given array.
template<class T>
void Sorting<T>::cocktailShakerSort(T array[], const unsigned& SIZE) {

	// Loop while a swap has occurred.
	unsigned start = 0, end = SIZE;
	bool swapped;
	do {

		// Iterate forwards.
		swapped = false;
		for (unsigned i = start+1; i < end; i++) {

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
		for (unsigned i = end-1; i > start; i--) {

			// Swap elements.
			if (compare(array[i], array[i-1])) {
				swap(array[i], array[i-1]);
				swapped = true;
			}
		}
		start++;

	} while (swapped);
}



// Gnome Sort the array.
template<class T>
void Sorting<T>::gnomeSort(T array[], const unsigned& SIZE) {

	// Sort while index < SIZE.
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
}



// Quick Sort the array.
template<class T>
void Sorting<T>::quickSort(T array[], const unsigned& SIZE) {
	quickSort(array, 0, SIZE-1);
}


// The hidden recursive Quick Sort function.
template<class T>
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
template<class T>
int Sorting<T>::partition(T array[], int low, int high) {

	// Pivot is the last element.
	T pivot = array[high];

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
template<class T>
void Sorting<T>::quickSortV2(T array[], const unsigned& SIZE) {
	quickSortV2(array, 0, SIZE-1);
}


// The hidden recursive Quick Sort function.
template<class T>
void Sorting<T>::quickSortV2(T array[], int low, int high) {

	// Stopping condition.
	if (low >= high || low < 0 || high < 0) {
		return;
	}

	// Partition array and get the pivot index.
	int pivotIndex = partitionV2(array, low, high);

	// Sort the two partitions.
	quickSortV2(array, low, pivotIndex);
	quickSortV2(array, pivotIndex+1, high);
}


// The partition function for Quick Sort.
template<class T>
int Sorting<T>::partitionV2(T array[], int low, int high) {

	// Pivot is the middle element.
	unsigned middle = ((high - low) / 2) + low;
	T pivot = array[middle];

	// Left and right index.
	int i = low - 1;
	int j = high + 1;

	// Loop until left and right cross.
	while (true) {

		// Move left index (at least once).
		for (++i; i < high && compare(array[i], pivot); i++);

		// Move right index (at least once).
		for (--j; j >= 0 && compare(pivot, array[j]); j--);

		// If the indices crossed, return pivot index.
		if (i >= j) {
			return j;
		}

		// Swap left and right.
		swap(array[i], array[j]);
	}
}



// Shell Sort the array.
template<class T>
void Sorting<T>::shellSort(T array[], const unsigned& SIZE) {
	bool sorted = false;

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

			// Do the gapped insertion sort.
			unsigned j = i;
			while (j >= gap && compare(array[j], array[j-gap])) {
				swap(array[j], array[j-gap]);
				j -= gap;
			}
		}
	}
}



// Merge Sort the array.
template<class T>
void Sorting<T>::mergeSort(T array[], const unsigned& SIZE) {

	// Temporary array for copying.
	T copy[SIZE];

	// Call the recursive split function.
	split(array, copy, 0, SIZE);
}


// The function to recursively split the array for Merge Sort.
template<class T>
void Sorting<T>::split(T array[], T copy[], unsigned start, unsigned end) {

	// Stopping condition.
	if (end - start <= 1) {
		return;
	}

	// Get midpoint of start and end.
	unsigned middle = (start + end) / 2;

	// Split into left and right halves.
	split(array, copy, start, middle);
	split(array, copy, middle, end);

	// Merge the current array.
	merge(array, copy, start, middle, end);
}


// Merge the array again.
template<class T>
void Sorting<T>::merge(
	T array[], T copy[], unsigned start, unsigned middle, unsigned end) {

	// Configure the moving indices.
	unsigned i = start, j = middle;

	// Merge array into copy from start to end.
	for (unsigned k = start; k < end; k++) {
		if (i < middle && (j >= end || compare(array[i], array[j]))) {
			copy[k] = array[i];
			i++;
		} else {
			copy[k] = array[j];
			j++;
		}
	}

	// Copy back into original array.
	for (unsigned k = start; k < end; k++) {
		array[k] = copy[k];
	}
}



// Comb Sort the array.
template<class T>
void Sorting<T>::combSort(T array[], const unsigned& SIZE) {
	bool sorted = false;
	unsigned gap = SIZE;

	// Loop for all gaps.
	while (!sorted) {
		gap = int(gap / 1.3);
		if (gap <= 1) {
			gap = 1;
			sorted = true;
		}

		// Bubble Sort with the current gap.
		for (unsigned i = 0, j = gap; j < SIZE; i++, j++) {
			if (compare(array[j], array[i])) {
				swap(array[j], array[i]);
			}
		}
	}
}



// Radix Sort the array using the specified base.
// Note: Only works for unsigned integers, chars, and strings.
template<class T>
void Sorting<T>::radixSort(T array[], const unsigned& SIZE, unsigned base) {

	// Update base for type T.
	base = updateBase(array, base);

	// Get the number of digits from the maximum value.
	unsigned numDigits = radixDigits(array, SIZE, base);

	// Create counting array and copy of original array.
	int count[base];
	unsigned copy[SIZE];

	// Iterate through all digits.
	for (unsigned d, digit = 0; digit < numDigits; digit++) {

		// Reset the counting array.
		for (unsigned i = 0; i < base; i++) {
			count[i] = 0;
		}

		// Iterate through all elements in the array.
		for (unsigned i = 0; i < SIZE; i++) {
			copy[i] = array[i];

			// Determine the current digit.
			d = radixHash(array[i], digit, base);

			// Invert digit if descending order.
			if (!sortAscending) {
				d = base - 1 - d;
			}

			// Increment the respective count.
			count[d]++;
		}

		// Increment each subsequent count.
		for (unsigned i = 1; i < base; i++) {
			count[i] += count[i-1];
		}

		// Copy the sorted elements back into the original array.
		for (int i = SIZE-1; i >= 0; i--) {

			// Determine the current digit.
			d = radixHash(copy[i], digit, base);

			// Invert digit if descending order.
			if (!sortAscending) {
				d = base - 1 - d;
			}

			// Copy to array.
			count[d]--;
			array[count[d]] = copy[i];
		}
	}
}


// Update the base for type unsigned integer.
template<class T>
unsigned Sorting<T>::updateBase(unsigned array[], unsigned base) {
	return base;
}


// Update the base for type char.
template<class T>
unsigned Sorting<T>::updateBase(char array[], unsigned base) {
	return 128;
}


// Get the number of digits (unsigned integer) for Radix Sort.
template<class T>
unsigned Sorting<T>::radixDigits(
	unsigned array[], const unsigned& SIZE, const unsigned& BASE) {

	// The number of digits is based on the maximum value.
	unsigned maxValue = max(array, SIZE);
	unsigned numDigits = 1;
	if (maxValue >= BASE) {
		numDigits += log(BASE, maxValue);
	}
	return numDigits;
}


// Get the number of digits (char) for Radix Sort.
template<class T>
unsigned Sorting<T>::radixDigits(
	char array[], const unsigned& SIZE, const unsigned& BASE) {

	// The number of char digits is always 1.
	return 1;
}


// Hash function to get the unsigned integer radix digit.
template<class T>
unsigned Sorting<T>::radixHash(unsigned& value, unsigned digit, const unsigned& BASE) {
	digit = pow(BASE, digit);
	return (value / digit) % BASE;
}


// Hash function to get the char radix digit.
template<class T>
unsigned Sorting<T>::radixHash(char& value, unsigned digit, const unsigned& BASE) {
	return unsigned(value);
}



// Heap Sort the array.
template<class T>
void Sorting<T>::heapSort(T array[], const unsigned& SIZE) {

	// Get index of last non-leaf node.
	int node = SIZE / 2 - 1;

	// Heapify the whole array.
	for (int i = node; i >= 0; i--) {
		heapify(array, SIZE, i);
	}

	// Sort by continuously popping from the heap.
	for (unsigned end = SIZE-1; end > 0; end--) {
		swap(array[0], array[end]);
		heapify(array, end, 0);
	}
}


// Recursively heapify the array at the given index.
template<class T>
void Sorting<T>::heapify(T array[], unsigned end, unsigned parentIndex) {

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

		// Only swap and trickle down heap
		// if parent is not the critical value.
		if (criticalIndex != parentIndex) {
			swap(array[criticalIndex], array[parentIndex]);
			parentIndex = criticalIndex;
		}

		// Break loop otherwise.
		else break;

	}
}



// Bucket Sort the array.
// Note: only works for unsigned integer and char arrays.
template<class T>
void Sorting<T>::bucketSort(T array[], const unsigned& SIZE) {

	// Get the maximum value in the array plus 1.
	unsigned maxValue = 1 + max(array, SIZE);

	// Get the index ratio.
	double ratio = double(SIZE) / maxValue;

	// Create priority queue array.
	PriorityQueue<T> bucket[SIZE];

	// Iterate through array and push elements to bucket.
	for (unsigned j, i = 0; i < SIZE; i++) {
		j = array[i] * ratio;
		bucket[j].push(array[i]);
	}

	// Get array starting index based on sorting order.
	int j = (sortAscending ? SIZE-1 : 0);

	// Iterate through bucket and sort array.
	for (int i = SIZE-1; i >= 0; i--) {
		while (!bucket[i].isEmpty()) {
			array[j] = bucket[i].pop();

			// Update array index.
			j += (sortAscending ? -1 : 1);
		}
	}
}



// Bitonic Sort the array.
template<class T>
void Sorting<T>::bitonicSort(T array[], const unsigned& SIZE) {
	bitonicSort(array, 0, SIZE, sortAscending);
}


// Recursive part of Bitonic Sort.
template<class T>
void Sorting<T>::bitonicSort(
	T array[], unsigned low, unsigned high, bool ascending) {

	// Stopping condition.
	if (high <= 1) {
		return;
	}

	// Get the middle.
	unsigned middle = high / 2;

	// Split and sort in both ascending and descending order.
	bitonicSort(array, low, middle, sortAscending);
	bitonicSort(array, low+middle, middle, !sortAscending);

	// Merge and sort in specified order.
	bitonicMerge(array, low, high, ascending);
}


// Where the bitonic sorting actually happens.
template<class T>
void Sorting<T>::bitonicMerge(
	T array[], unsigned low, unsigned high, bool ascending) {

	// Stopping condition.
	if (high <= 1) {
		return;
	}

	// Get the middle and lower limit.
	unsigned middle = high / 2;
	unsigned limit = low + middle;

	// Iterate through all entries from low to limit.
	for (unsigned i=low, j = limit; i < limit; i++, j++) {
		if (ascending == (array[j] < array[i])) {
			swap(array[i], array[j]);
		}
	}

	// Sort the lower and middle halves.
	bitonicMerge(array, low, middle, ascending);
	bitonicMerge(array, limit, middle, ascending);
}
