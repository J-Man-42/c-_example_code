#include <iostream>
#include "sorting.h"
#include "../move_cursor/move_cursor.h"
#include "../random/random.h"
using namespace std;


// Main loop function.
int main() {
	uint number;
	char answer[21];
	size_t size = 100000;
	uint minValue = 1;
	uint maxValue = 100000;
	bool mustRefresh = true;
	bool isUint = true;

	// Initialise the arrays.
	uint* uintArray = randUintArray(size, minValue, maxValue);
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
			cout << (Sorting<uint>::sortAscending ? "Ascending" : "Descending");
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
				size_t newSize;
				cin >> newSize;

				// Shrink array.
				if (newSize < size) {
					uint* newUintArray = new uint[newSize];
					char* newCharArray = new char[newSize];
					for (size_t i = 0; i < newSize; i++) {
						newUintArray[i] = uintArray[i];
						newCharArray[i] = charArray[i];
					}
					delete [] uintArray;
					delete [] charArray;
					uintArray = newUintArray;
					charArray = newCharArray;
					size = newSize;
				}

				// Grow array.
				else if (newSize > size) {
					uint* newUintArray = new uint[newSize];
					char* newCharArray = new char[newSize];
					for (size_t i = 0; i < size; i++) {
						newUintArray[i] = uintArray[i];
						newCharArray[i] = charArray[i];
					}
					for (size_t i = size; i < newSize; i++) {
						newUintArray[i] = randUint(minValue, maxValue);
						newCharArray[i] = randChar();
					}
					delete [] uintArray;
					delete [] charArray;
					uintArray = newUintArray;
					charArray = newCharArray;
					size = newSize;
				}
				break;

			// Reverse the array order.
			case '2':
				for (size_t i = 0, j = size-1; i < j; i++, j--) {
					swap(uintArray[i], uintArray[j]);
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
				delete [] uintArray;
				delete [] charArray;
				uintArray = new uint[size];
				charArray = new char[size];
				for (uint i = 0, n = minValue; i < size; i++, n++) {
					uintArray[i] = n;
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
				delete [] uintArray;
				delete [] charArray;
				uintArray = new uint[size];
				charArray = new char[size];
				for (uint i = 0, n = maxValue; i < size; i++, n--) {
					uintArray[i] = n;
					charArray[i] = n % 128;
				}
				break;

			// Shuffle the current array.
			case '5':
				shuffle(uintArray, size);
				shuffle(charArray, size);
				break;

			// Randomise the array.
			case '6':
				delete [] uintArray;
				delete [] charArray;
				uintArray = randUintArray(size, minValue, maxValue);
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
			for (size_t i = 0; i < size; i++) {
				uintArray[i] = max(minValue, uintArray[i]);
				uintArray[i] = min(maxValue, uintArray[i]);
			}

			break;


		// Toggle sorting in ascending/descending order.
		case '3':
			Sorting<uint>::sortAscending = !Sorting<uint>::sortAscending;
			Sorting<char>::sortAscending = Sorting<uint>::sortAscending;
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
			cout << " (5)  QuickSort" << endl;
			cout << " (6)  QuickSort V2" << endl;
			cout << " (7)  Shell Sort" << endl;
			cout << " (8)  Merge Sort" << endl;
			cout << " (9)  Comb Sort" << endl;
			cout << "(10)  Radix Sort (base 10)" << endl;
			cout << "(11)  Radix Sort (custom base)" << endl;
			cout << "(12)  Heap Sort" << endl;
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
					Sorting<uint>::bubbleSort(uintArray, size);
				} else {
					Sorting<char>::bubbleSort(charArray, size);
				}
				break;
			case 2:
				cout << "Performing Selection Sort..." << endl;
				if (isUint) {
					Sorting<uint>::selectionSort(uintArray, size);
				} else {
					Sorting<char>::selectionSort(charArray, size);
				}
				break;
			case 3:
				cout << "Performing Insertion Sort..." << endl;
				if (isUint) {
					Sorting<uint>::insertionSort(uintArray, size);
				} else {
					Sorting<char>::insertionSort(charArray, size);
				}
				break;
			case 4:
				cout << "Performing Cocktail Shaker Sort..." << endl;
				if (isUint) {
					Sorting<uint>::cocktailShakerSort(uintArray, size);
				} else {
					Sorting<char>::cocktailShakerSort(charArray, size);
				}
				break;
			case 5:
				cout << "Performing Quick Sort..." << endl;
				if (isUint) {
					Sorting<uint>::quickSort(uintArray, size);
				} else {
					Sorting<char>::quickSort(charArray, size);
				}
				break;
			case 6:
				cout << "Performing Quick Sort V2..." << endl;
				if (isUint) {
					Sorting<uint>::quickSortV2(uintArray, size);
				} else {
					Sorting<char>::quickSortV2(charArray, size);
				}
				break;
			case 7:
				cout << "Performing Shell Sort..." << endl;
				if (isUint) {
					Sorting<uint>::shellSort(uintArray, size);
				} else {
					Sorting<char>::shellSort(charArray, size);
				}
				break;
			case 8:
				cout << "Performing Merge Sort..." << endl;
				if (isUint) {
					Sorting<uint>::mergeSort(uintArray, size);
				} else {
					Sorting<char>::mergeSort(charArray, size);
				}
				break;
			case 9:
				cout << "Performing Comb Sort..." << endl;
				if (isUint) {
					Sorting<uint>::combSort(uintArray, size);
				} else {
					Sorting<char>::combSort(charArray, size);
				}
				break;
			case 10:
				cout << "Performing Radix Sort (base 10)..." << endl;
				if (isUint) {
					Sorting<uint>::radixSort(uintArray, size);
				} else {
					Sorting<char>::radixSort(charArray, size);
				}
				break;
			case 11:
				cout << "base = ";
				cin.getline(answer, 20);
				number = atoi(answer);
				clearScreen();
				cout << "Performing Radix Sort (base "<<number<<")..." << endl;
				if (isUint) {
					Sorting<uint>::radixSort(uintArray, size, number);
				} else {
					Sorting<char>::radixSort(charArray, size, number);
				}
				break;
			case 12:
				cout << "Performing Heap Sort..." << endl;
				if (isUint) {
					Sorting<uint>::heapSort(uintArray, size);
				} else {
					Sorting<char>::heapSort(charArray, size);
				}
				break;
			}

			// Record the timestamp after sorting.
			auto end = high_resolution_clock::now();

			// Print time taken.
			Sorting<uint>::showTimeTaken(start, end);
		}
	}

	return 0;
}
