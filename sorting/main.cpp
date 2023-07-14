#include <iostream>
#include "sorting.h"
#include "../move_cursor/move_cursor.h"
#include "../random/random.h"
using namespace std;


// Main loop function.
int main() {
	unsigned number;
	char answer[21];
	unsigned size = 100000;
	unsigned minValue = 1;
	unsigned maxValue = 100000;
	bool mustRefresh = true;
	bool isUint = true;

	// Initialise the arrays.
	unsigned* unsignedArray = randUintArray(size, minValue, maxValue);
	char* charArray = randCharArray(size);

	// Main loop.
	while (answer[0] != 'Q') {

		// Only refresh screen if needed.
		if (mustRefresh) {
			clearScreen();
		}

		// Show the options.
		cout << "========================================" << endl;
		if (isUint) {
			cout << "Unsigned Integer Array" << endl;
			cout << "Array contents ~ Z["<<minValue<<", "<<maxValue<<"]" << endl;
		} else {
			cout << "Char Array" << endl;
		}
		cout << "Array size = " << size << endl;
		cout << "Sort ";
		if (isUint) {
			cout << (Sorting<unsigned>::sortAscending ? "Ascending" : "Descending");
		} else {
			cout << (Sorting<char>::sortAscending ? "Ascending" : "Descending");
		}
		cout << " Order" << endl;
		cout << "========================================" << endl;
		cout << "(1)  Alter Array" << endl;
		cout << "(2)  Update Array Range" << endl;
		cout << "(3)  Toggle Ascending/Descending" << endl;
		cout << "(4)  Toggle Data Type" << endl;
		cout << "(5)  Sort Array" << endl;
		cout << "(Q)  << QUIT PROGRAM >>" << endl;
		cout << "========================================" << endl;
		cout << "> ";
		cin.getline(answer, 20);

		// Format the answer.
		answer[0] = toupper(answer[0]);
		mustRefresh = (answer[0] != '5');

		// Safety for number higher than 5.
		if (isdigit(answer[0]) && atoi(answer) > 5) {
			continue;
		}


		// Perform the user specified action.
		switch (answer[0]) {


		// Alter the arrays.
		case '1':
			cout << "========================================" << endl;
			cout << "(1)  Change Array Size" << endl;
			cout << "(2)  Reverse Array Order" << endl;
			cout << "(3)  Create Sorted Ascending Array" << endl;
			cout << "(4)  Create Sorted Descending Array" << endl;
			cout << "(5)  Shuffle Current Array" << endl;
			cout << "(6)  Randomise Array" << endl;
			cout << "========================================" << endl;
			cout << "> ";
			cin.getline(answer, 20);

			// Perform the requested array alteration.
			switch (answer[0]) {

			// Change array size.
			case '1':
				cout << "new size = ";
				unsigned newSize;
				cin >> newSize;

				// Shrink array.
				if (newSize < size) {
					unsigned* newUintArray = new unsigned[newSize];
					char* newCharArray = new char[newSize];
					for (unsigned i = 0; i < newSize; i++) {
						newUintArray[i] = unsignedArray[i];
						newCharArray[i] = charArray[i];
					}
					delete [] unsignedArray;
					delete [] charArray;
					unsignedArray = newUintArray;
					charArray = newCharArray;
					size = newSize;
				}

				// Grow array.
				else if (newSize > size) {
					unsigned* newUintArray = new unsigned[newSize];
					char* newCharArray = new char[newSize];
					for (unsigned i = 0; i < size; i++) {
						newUintArray[i] = unsignedArray[i];
						newCharArray[i] = charArray[i];
					}
					for (unsigned i = size; i < newSize; i++) {
						newUintArray[i] = randUint(minValue, maxValue);
						newCharArray[i] = randChar();
					}
					delete [] unsignedArray;
					delete [] charArray;
					unsignedArray = newUintArray;
					charArray = newCharArray;
					size = newSize;
				}
				break;

			// Reverse the array order.
			case '2':
				for (unsigned i = 0, j = size-1; i < j; i++, j--) {
					swap(unsignedArray[i], unsignedArray[j]);
					swap(charArray[i], charArray[j]);
				}
				break;

			// Array with ascending elements.
			case '3':
				if (!isUint) {
					minValue = 32;
					maxValue = 127;
				}
				size = maxValue - minValue + 1;
				delete [] unsignedArray;
				delete [] charArray;
				unsignedArray = new unsigned[size];
				charArray = new char[size];
				for (unsigned i = 0, n = minValue; i < size; i++, n++) {
					unsignedArray[i] = n;
					charArray[i] = n;
				}
				break;

			// Array with descending elements.
			case '4':
				if (!isUint) {
					minValue = 32;
					maxValue = 127;
				}
				size = maxValue - minValue + 1;
				delete [] unsignedArray;
				delete [] charArray;
				unsignedArray = new unsigned[size];
				charArray = new char[size];
				for (unsigned i = 0, n = maxValue; i < size; i++, n--) {
					unsignedArray[i] = n;
					charArray[i] = n % 128;
				}
				break;

			// Shuffle the current array.
			case '5':
				shuffle(unsignedArray, size);
				shuffle(charArray, size);
				break;

			// Randomise the array.
			case '6':
				delete [] unsignedArray;
				delete [] charArray;
				unsignedArray = randUintArray(size, minValue, maxValue);
				charArray = randCharArray(size);
				break;

			}
			break;


		// Update the minimum and maximum values.
		case '2':
			cout << "minimum value = ";
			cin >> minValue;
			cout << "maximum value = ";
			cin >> maxValue;

			// Ensure maxValue >= minValue.
			if (minValue > maxValue) {
				swap(minValue, maxValue);
			}

			// Modify the array to meet this criteria.
			for (unsigned i = 0; i < size; i++) {
				unsignedArray[i] = max(minValue, unsignedArray[i]);
				unsignedArray[i] = min(maxValue, unsignedArray[i]);
			}

			break;


		// Toggle sorting in ascending/descending order.
		case '3':
			Sorting<unsigned>::sortAscending = !Sorting<unsigned>::sortAscending;
			Sorting<char>::sortAscending = Sorting<unsigned>::sortAscending;
			break;


		// Toggle between unsigned integer and char arrays.
		case '4':
			isUint = !isUint;
			break;


		// Run one of the sorting algorithms..
		case '5':
			cout << "==============================" << endl;
			cout << " (1)  Bubble Sort" << endl;
			cout << " (2)  Selection Sort" << endl;
			cout << " (3)  Insertion Sort" << endl;
			cout << " (4)  Cocktail Shaker Sort" << endl;
			cout << " (5)  Gnome Sort" << endl;
			cout << " (6)  QuickSort" << endl;
			cout << " (7)  QuickSort V2" << endl;
			cout << " (8)  Shell Sort" << endl;
			cout << " (9)  Merge Sort" << endl;
			cout << "(10)  Comb Sort" << endl;
			cout << "(11)  Radix Sort (base 10)" << endl;
			cout << "(12)  Radix Sort (custom base)" << endl;
			cout << "(13)  Heap Sort" << endl;
			cout << "(14)  Bucket Sort" << endl;
			cout << "(15)  Bitonic Sort" << endl;
			cout << "==============================" << endl;
			cout << "> ";
			cin.getline(answer, 20);

			// Continue if not a number.
			if (!isdigit(answer[0])) {
				clearScreen();
				continue;
			}

			// Record the timestamp before sorting.
			auto start = high_resolution_clock::now();

			// Run the requested sorting algorithm.
			number = atoi(answer);

			// Only clear screen if not Radix Sort with custom base.
			if (number != 11) {
				clearScreen();
			}

			switch (number) {
			case 1:
				cout << "Performing Bubble Sort..." << endl;
				if (isUint) {
					Sorting<unsigned>::bubbleSort(unsignedArray, size);
				} else {
					Sorting<char>::bubbleSort(charArray, size);
				}
				break;
			case 2:
				cout << "Performing Selection Sort..." << endl;
				if (isUint) {
					Sorting<unsigned>::selectionSort(unsignedArray, size);
				} else {
					Sorting<char>::selectionSort(charArray, size);
				}
				break;
			case 3:
				cout << "Performing Insertion Sort..." << endl;
				if (isUint) {
					Sorting<unsigned>::insertionSort(unsignedArray, size);
				} else {
					Sorting<char>::insertionSort(charArray, size);
				}
				break;
			case 4:
				cout << "Performing Cocktail Shaker Sort..." << endl;
				if (isUint) {
					Sorting<unsigned>::cocktailShakerSort(unsignedArray, size);
				} else {
					Sorting<char>::cocktailShakerSort(charArray, size);
				}
				break;
			case 5:
				cout << "Performing Gnome Sort..." << endl;
				if (isUint) {
					Sorting<unsigned>::gnomeSort(unsignedArray, size);
				} else {
					Sorting<char>::gnomeSort(charArray, size);
				}
				break;
			case 6:
				cout << "Performing Quick Sort..." << endl;
				if (isUint) {
					Sorting<unsigned>::quickSort(unsignedArray, size);
				} else {
					Sorting<char>::quickSort(charArray, size);
				}
				break;
			case 7:
				cout << "Performing Quick Sort V2..." << endl;
				if (isUint) {
					Sorting<unsigned>::quickSortV2(unsignedArray, size);
				} else {
					Sorting<char>::quickSortV2(charArray, size);
				}
				break;
			case 8:
				cout << "Performing Shell Sort..." << endl;
				if (isUint) {
					Sorting<unsigned>::shellSort(unsignedArray, size);
				} else {
					Sorting<char>::shellSort(charArray, size);
				}
				break;
			case 9:
				cout << "Performing Merge Sort..." << endl;
				if (isUint) {
					Sorting<unsigned>::mergeSort(unsignedArray, size);
				} else {
					Sorting<char>::mergeSort(charArray, size);
				}
				break;
			case 10:
				cout << "Performing Comb Sort..." << endl;
				if (isUint) {
					Sorting<unsigned>::combSort(unsignedArray, size);
				} else {
					Sorting<char>::combSort(charArray, size);
				}
				break;
			case 11:
				cout << "Performing Radix Sort (base 10)..." << endl;
				if (isUint) {
					Sorting<unsigned>::radixSort(unsignedArray, size);
				} else {
					Sorting<char>::radixSort(charArray, size);
				}
				break;
			case 12:
				cout << "base = ";
				cin.getline(answer, 20);
				number = atoi(answer);
				clearScreen();
				cout << "Performing Radix Sort (base "<<number<<")..." << endl;
				if (isUint) {
					Sorting<unsigned>::radixSort(unsignedArray, size, number);
				} else {
					Sorting<char>::radixSort(charArray, size, number);
				}
				break;
			case 13:
				cout << "Performing Heap Sort..." << endl;
				if (isUint) {
					Sorting<unsigned>::heapSort(unsignedArray, size);
				} else {
					Sorting<char>::heapSort(charArray, size);
				}
				break;
			case 14:
				cout << "Performing Bucket Sort..." << endl;
				if (isUint) {
					Sorting<unsigned>::bucketSort(unsignedArray, size);
				} else {
					Sorting<char>::bucketSort(charArray, size);
				}
				break;
			case 15:
				cout << "Performing Bitonic Sort..." << endl;
				if (isUint) {
					Sorting<unsigned>::bitonicSort(unsignedArray, size);
				} else {
					Sorting<char>::bitonicSort(charArray, size);
				}
				break;
			}

			// Record the timestamp after sorting.
			auto end = high_resolution_clock::now();

			// Print time taken.
			Sorting<unsigned>::showTimeTaken(start, end);
		}
	}

	return 0;
}
