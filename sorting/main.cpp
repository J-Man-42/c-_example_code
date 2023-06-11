#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include "sorting.h"
using namespace std;
using namespace std::this_thread;	// sleep_for, sleep_until
using namespace std::chrono;		// nanoseconds, system_clock, seconds.


// Generates a new random array with elements from 1 to 40.
uint* generateRandomArray(const uint SIZE) {
	uint* array = new uint[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		array[i] = randint(1, 40);
	}
	return array;
}


// Main loop function.
int main() {
	uint answer;
	size_t size = 20;
	uint milliseconds = 50;
	bool thinBar = false;

	// Initialise array.
	uint* array = generateRandomArray(size);

	// Clear the screen.
	cout << "\033[2J\033[1;1H";

	// Main loop.
	while (true) {

		// Display the array.
		displayArray(array, size, thinBar);

		// Show the options.
		cout << "==============================" << endl;
		cout << "Array size = " << size << endl;
		cout << "Time delay = " << milliseconds << "ms\n";
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
			array = generateRandomArray(size);
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
					newArray[i] = randint(1, 40);
				}
				delete [] array;
				array = newArray;
				size = newSize;
			}

			clearScreen();
			break;


		// Toggle the width of the vertical bars.
		case 2:
			thinBar = !thinBar;
			clearScreen();
			break;


		// Change the milliseconds delay when sorting.
		case 3:
			cout << "new delay = ";
			cin >> milliseconds;
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
				bubbleSort(array, size, milliseconds, thinBar);
				break;
			case 2:
				selectionSort(array, size, milliseconds, thinBar);
				break;
			case 3:
				insertionSort(array, size, milliseconds, thinBar);
				break;
			case 4:
				cocktailShakerSort(array, size, milliseconds, thinBar);
				break;
			default:
				clearScreen();
			}
			break;
		}
	}

	return 0;
}
