#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include "sorting.h"
// #include "../colour_text/colour_text.h"
// #include "../lists/linked_list.h"
// #include "../min_and_max/min_max.h"
#include "../move_cursor/move_cursor.h"
#include "../random/random.h"
using namespace std;
using namespace std::this_thread;	// sleep_for, sleep_until
using namespace std::chrono;		// nanoseconds, system_clock, seconds.



// Main loop function.
int main() {
	uint answer;
	size_t size = 20;
	uint minValue = 1;
	uint maxValue = 40;

	// Initialise array.
	uint* array = randUintArray(size, minValue, maxValue);

	// Clear the screen.
	clearScreen();

	// Main loop.
	while (true) {

		// Display the array.
		Sorting::displayArray(array, size);

		// Show the options.
		cout << "==============================" << endl;
		cout << "Array size = " << size << endl;
		cout << "Time delay = " << Sorting::delay << "ms\n";
		cout << "==============================" << endl;
		cout << "(0)  Randomise Array" << endl;
		cout << "(1)  Resize Array" << endl;
		cout << "(2)  Toggle Bar Width" << endl;
		cout << "(3)  Milliseconds Delay" << endl;
		cout << "(4)  Sort Array" << endl;
		cout << "==============================" << endl;

		// Get user input.
		do {
			cout << "> ";
			cin >> answer;
		} while (answer > 4);


		// Perform the user specified action.
		switch (answer) {


		// Randomise the array.
		case 0:
			delete [] array;
			array = randUintArray(size, minValue, maxValue);
			clearScreen();
			break;


		// Resize the existing array.
		case 1:
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

			clearScreen();
			break;


		// Toggle the width of the vertical bars.
		case 2:
			Sorting::toggleBarWidth();
			clearScreen();
			break;


		// Change the milliseconds delay when sorting.
		case 3:
			cout << "new delay = ";
			cin >> Sorting::delay;
			clearScreen();
			break;


		// Run one of the sorting algorithms..
		case 4:
			cout << "==============================" << endl;
			cout << "(1)  Bubble Sort" << endl;
			cout << "(2)  Selection Sort" << endl;
			cout << "(3)  Insertion Sort" << endl;
			cout << "(4)  Cocktail Shaker Sort" << endl;
			cout << "==============================" << endl;
			cout << "> ";
			cin >> answer;

			// Run the requested sorting algorithm.
			switch (answer) {
			case 1:
				Sorting::bubbleSort(array, size);
				break;
			case 2:
				Sorting::selectionSort(array, size);
				break;
			case 3:
				Sorting::insertionSort(array, size);
				break;
			case 4:
				Sorting::cocktailShakerSort(array, size);
				break;
			default:
				clearScreen();
			}
			break;
		}
	}

	return 0;
}
