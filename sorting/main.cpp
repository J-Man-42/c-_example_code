#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include "sorting.h"
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.


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
	uint milliseconds = 50;

	// Initialise array.
	size_t size = 20;
	uint* array = generateRandomArray(size);

	// Main loop.
	while (true) {

		// Display the array.
		displayArray(array, size);

		// Show the options.
		cout << "==============================" << endl;
		cout << "Array size = " << size << endl;
		cout << "Time delay = " << milliseconds << "ms\n";
		cout << "==============================" << endl;
		cout << "(0)  Randomise Array" << endl;
		cout << "(1)  Resize Array" << endl;
		cout << "(2)  Milliseconds Delay" << endl;
		cout << "(3)  Bubble Sort" << endl;
		cout << "(4)  Selection Sort" << endl;
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

			break;


		// Change the milliseconds delay when sorting.
		case 2:
			cout << "new delay = ";
			cin >> milliseconds;
			break;


		// Run bubble sort the array.
		case 3:
			bubbleSort(array, size, milliseconds);
			break;


		// Run selection sort the array.
		case 4:
			selectionSort(array, size, milliseconds);
			break;
		}
	}

	return 0;
}
