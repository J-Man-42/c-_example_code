#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include <cmath>
#include "linked_list.h"
using namespace std;
using namespace std::this_thread;	// sleep_for, sleep_until
using namespace std::chrono;		// nanoseconds, system_clock, seconds.


// Clears the terminal screen.
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}


// Generate a random integer between minValue and maxValue.
uint randint(uint minValue, uint maxValue) {

    // Configure the seed.
    static uint long seed = 0;
    if (seed == 0) {
        seed = time(0);
        srand(seed);
    }

    // Generate and return a random integer.
    return rand() % (maxValue - minValue + 1) + minValue;
}


// Generates a new random array with elements from 1 to 40.
uint* generateRandomArray(const uint SIZE) {
    uint* array = new uint[SIZE];
    for (size_t i = 0; i < SIZE; i++) {
        array[i] = randint(1, 40);
    }
    return array;
}


// Elegantly displays the content of the array.
void displayArray(uint* array, const uint SIZE) {
	uint width;

	// Do not print array of size 0.
	if (SIZE == 0) {
		return;
	}

	// Display the top border.
	cout << "┌─";
	for (size_t i = 0; i < SIZE; i++) {
		width = 1;
		if (array[i] > 0) {
			width += log10(array[i]);
		}
		for (size_t j = 0; j < width; j++) {
			cout << "─";
		}
		if (i < SIZE-1) {
			cout << "─┬─";
		} else {
			cout << "─┐\n";
		}
	}

	// Iterate through all elements.
	for (size_t i = 0; i < SIZE; i++) {
		cout << "│ " << array[i] << " ";
	}
	cout << "│\n";

	// Display the bottom border.
	cout << "└─";
	for (size_t i = 0; i < SIZE; i++) {
		width = 1;
		if (array[i] > 0) {
			width += log10(array[i]);
		}
		for (size_t j = 0; j < width; j++) {
			cout << "─";
		}
		if (i < SIZE-1) {
			cout << "─┴─";
		} else {
			cout << "─┘\n";
		}
	}
}



// Main function.
int main() {
	char answer;
	uint element;
	size_t index;

	// Create the linked list.
	LinkedList<uint> list;

	// Declare the array pointer.
	uint size = 0;
	uint* array = new uint[size];

	// Loop forever.
	while (true) {

		// Clear the screen
		clearScreen();

		// Print the linked list.
		cout << "List:" << endl;
		list.print();

		// Print the array.
		cout << "\nArray:" << endl;
		displayArray(array, size);

		// Print majority of available functions.
		cout << "\n==============================" << endl;
		cout << "(0)  << QUIT PROGRAM >>" << endl;
		cout << "(1)  add(element)" << endl;
		cout << "(2)  clear()" << endl;
		cout << "(3)  insert(index, element)" << endl;
		cout << "(4)  remove(element)" << endl;
		cout << "(5)  removeAt(index)" << endl;
		cout << "(6)  size()" << endl;
		cout << "(7)  toDynamicArray()" << endl;
		cout << "(8)  toDynamicArray(size)" << endl;
		cout << "==============================" << endl;
		cout << "> ";
		cin >> answer;


		// Switch statement for answer.
		switch (answer) {


		// Quit.
		case '0':
			return 0;


		// Add an element.
		case '1':
			cout << "add(element)" << endl;
			cout << "> element = ";
			cin >> element;
			list.add(element);
			break;


		// Clear all elements.
		case '2':
			cout << "clear()" << endl;
			list.clear();
			break;


		// Insert an element.
		case '3':
			cout << "insert(index, element)" << endl;
			cout << "> index = ";
			cin >> index;
			cout << "> element = ";
			cin >> element;
			list.insert(index, element);
			break;


		// Remove the specified element.
		case '4':
			cout << "remove(element)" << endl;
			cout << "> element = ";
			cin >> element;
			try {
				list.remove(element);
			} catch (string e) {
				cout << e << endl;
				sleep_for(seconds(1));
			}
			break;


		// Remove element at the given index.
		case '5':
			cout << "removeAt(index)" << endl;
			cout << "> index = ";
			cin >> index;
			try {
				list.removeAt(index);
			} catch (string e) {
				cout << e << endl;
				sleep_for(seconds(1));
			}
			break;


		// Display the number of elements.
		case '6':
			cout << "size()" << endl;
			cout << "List size:  " << list.size() << endl;
			sleep_for(seconds(1));
			break;


		// Convert to a dynamic array.
		case '7':
			cout << "toDynamicArray()" << endl;
			delete array;
			try {
				array = list.toDynamicArray();
				size = list.size();
			} catch (string e) {
				cout << e << endl;
				size = 1;
				array = new uint[size];
				sleep_for(seconds(1));
			}
			break;


		// Convert to a dynamic array of specified size.
		case '8':
			cout << "toDynamicArray(size)" << endl;
			cout << "> size = ";
			cin >> size;
			delete array;
			array = list.toDynamicArray(size);
			break;
		}
	}

	// Clear dynamic memory.
	delete [] array;

	return 0;
}
