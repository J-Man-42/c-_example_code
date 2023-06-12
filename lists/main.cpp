#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "linked_list.h"
using namespace std;


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
	uint answer;

	// Create the linked list.
	LinkedList<uint> list;

	// Declare the array pointer.
	uint size = 1;
	uint* array = new uint[size];

	// Loop forever.
	while (true) {

		cout << "List:" << endl;
		list.print();

		cout << "\nArray:" << endl;
		displayArray(array, size);

		cout << "==============================" << endl;
		cout << "(1)  add(element)" << endl;
		cout << "(2)  clear()" << endl;
		cout << "(3)  insert(index, element)" << endl;
		cout << "(4)  print()" << endl;
		cout << "(5)  remove(element)" << endl;
		cout << "(6)  removeAt(index)" << endl;
		cout << "(7)  size()" << endl;
		cout << "(8)  toDynamicArray()" << endl;
		cout << "(9)  toDynamicArray(size)" << endl;
		cout << "==============================" << endl;
		cout << "> ";
		cin >> answer;
	}
	return 0;
}
