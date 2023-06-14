#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include "sorting.h"
#include "../min_and_max/min_max.h"
#include "../move_cursor/move_cursor.h"
#include "../random/random.h"
using namespace std;
using namespace std::this_thread;	// sleep_for, sleep_until
using namespace std::chrono;		// nanoseconds, system_clock, seconds.



// Main loop function.
int main() {
	char answer = '0';
	size_t size = 20;
	uint minValue = 1;
	uint maxValue = 40;
	bool mustRefresh = true;

	// Initialise array.
	uint* array = randUintArray(size, minValue, maxValue);

	// Main loop.
	while (answer != 'Q') {

		// Selectively clear the screen.
		if (mustRefresh) {
			clearScreen();
		}

		// Display the array.
		Sorting::displayArray(array, size);

		// Show the options.
		cout << "========================================" << endl;
		cout << "Array contents ~ Z["<<minValue<<", "<<maxValue<<"]" << endl;
		cout << "Array size = " << size << endl;
		cout << "Bar width = " << Sorting::getBarWidth() << endl;
		cout << "Time delay = " << Sorting::delay << "ms\n";
		cout << "Sort ";
		cout << (Sorting::sortAscending ? "Ascending" : "Descending");
		cout << " Order" << endl;
		cout << "========================================" << endl;
		cout << "(0)  Randomise Array" << endl;
		cout << "(1)  Alter Array" << endl;
		cout << "(2)  Update Array Range" << endl;
		cout << "(3)  Toggle Bar Width" << endl;
		cout << "(4)  Change Step Delay" << endl;
		cout << "(5)  Toggle Ascending/Descending" << endl;
		cout << "(6)  Sort Array" << endl;
		cout << "(Q)  << QUIT PROGRAM >>" << endl;
		cout << "========================================" << endl;
		cout << "> ";
		cin >> answer;

		// Format the answer.
		answer = toupper(answer);
		mustRefresh = (answer != '6');


		// Perform the user specified action.
		switch (answer) {


		// Randomise the array.
		case '0':
			delete [] array;
			array  = randUintArray(size, minValue, maxValue);
			break;


		// Alter the array.
		case '1':
			cout << "========================================" << endl;
			cout << "(1)  Change Array Size" << endl;
			cout << "(2)  Reverse Array Order" << endl;
			cout << "(3)  Create Sorted Ascending Array" << endl;
			cout << "(4)  Create Sorted Descending Array" << endl;
			cout << "========================================" << endl;
			cout << "> ";
			cin >> answer;

			// Perform the requested array alteration.
			switch (answer) {

			// Change array size.
			case '1':
				cout << "new size = ";
				size_t newSize;
				cin >> newSize;

				// Shrink array.
				if (newSize < size) {
					uint* newArray = new uint[newSize];
					for (size_t i = 0; i < newSize; i++) {
						newArray[i] = array[i];
					}
					delete [] array;
					array = newArray;
					size = newSize;
				}

				// Grow array.
				else if (newSize > size) {
					uint* newArray = new uint[newSize];
					for (size_t i = 0; i < size; i++) {
						newArray[i] = array[i];
					}
					for (size_t i = size; i < newSize; i++) {
						newArray[i] = randUint(minValue, maxValue);
					}
					delete [] array;
					array = newArray;
					size = newSize;
				}
				break;

			// Reverse the array order.
			case '2':
				for (size_t i = 0, j = size-1; i < j; i++, j--) {
					swap(array[i], array[j]);
				}
				break;

			// Array with ascending elements.
			case '3':
				size = maxValue - minValue + 1;
				delete [] array;
				array = new uint[size];
				for (uint i = 0, n = minValue; i < size; i++, n++) {
					array[i] = n;
				}
				break;

			// Array with descending elements.
			case '4':
				size = maxValue - minValue + 1;
				delete [] array;
				array = new uint[size];
				for (uint i = 0, n = maxValue; i < size; i++, n--) {
					array[i] = n;
				}
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
				array[i] = max(minValue, array[i]);
				array[i] = min(maxValue, array[i]);
			}

			// Update bar height.
			Sorting::setBarHeight(maxValue);

			break;


		// Toggle the width of the vertical bars.
		case '3':
			Sorting::toggleBarWidth();
			break;


		// Change the milliseconds delay when sorting.
		case '4':
			cout << "new delay = ";
			cin >> Sorting::delay;
			break;


		// Toggle sorting in ascending/descending order.
		case '5':
			Sorting::sortAscending = !Sorting::sortAscending;
			break;


		// Run one of the sorting algorithms..
		case '6':
			cout << "==============================" << endl;
			cout << "(1)  Bubble Sort" << endl;
			cout << "(2)  Selection Sort" << endl;
			cout << "(3)  Insertion Sort" << endl;
			cout << "(4)  Cocktail Shaker Sort" << endl;
			cout << "(5)  QuickSort" << endl;
			cout << "(6)  QuickSort V2" << endl;
			cout << "(7)  Shell Sort" << endl;
			cout << "==============================" << endl;
			cout << "> ";
			cin >> answer;

			// Run the requested sorting algorithm.
			switch (answer) {
			case '1':
				Sorting::bubbleSort(array, size);
				break;
			case '2':
				Sorting::selectionSort(array, size);
				break;
			case '3':
				Sorting::insertionSort(array, size);
				break;
			case '4':
				Sorting::cocktailShakerSort(array, size);
				break;
			case '5':
				Sorting::quickSort(array, size);
				break;
			case '6':
				Sorting::quickSortV2(array, size);
				break;
			case '7':
				Sorting::shellSort(array, size);
				break;
			default:
				clearScreen();
			}
		}
	}

	return 0;
}
