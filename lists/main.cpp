#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>
#include "linked_list.h"
#include "../move_cursor/move_cursor.h"
using namespace std;
using namespace std::this_thread;	// sleep_for, sleep_until
using namespace std::chrono;		// nanoseconds, system_clock, seconds.


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
	char answer[3];
	uint number;
	uint element;
	size_t index;

	// Create the linked list.
	LinkedList<uint> list;

	// Declare the array pointer.
	uint size = 0;
	uint* array = new uint[size];

	// Loop until Q has been entered.
	while (answer[0] != 'Q') {

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
		cout << " (0)  operator[]" << endl;
		cout << " (1)  add(element)" << endl;
		cout << " (2)  clear()" << endl;
		cout << " (3)  get(index)" << endl;
		cout << " (4)  insert(index, element)" << endl;
		cout << " (5)  remove(element)" << endl;
		cout << " (6)  removeAt(index)" << endl;
		cout << " (7)  set(index, element)" << endl;
		cout << " (8)  size()" << endl;
		cout << " (9)  toDynamicArray()" << endl;
		cout << "(10)  toDynamicArray(size)" << endl;
		cout << " (Q)  << QUIT PROGRAM >>" << endl;
		cout << "==============================" << endl;
		cout << "> ";
		cin.getline(answer, 3);
		answer[0] = toupper(answer[0]);

		// Simply continue when a string is entered.
		if (isalpha(answer[0])) {
			continue;
		}


		// Switch statement for answer.
		number = atoi(answer);
		switch (number) {


		// Add an element.
		case 1:
			cout << "add(element)" << endl;
			cout << "> element = ";
			cin >> element;
			list.add(element);
			break;


		// Clear all elements.
		case 2:
			cout << "clear()" << endl;
			list.clear();
			break;


		// Insert an element.
		case 4:
			cout << "insert(index, element)" << endl;
			cout << "> index = ";
			cin >> index;
			cout << "> element = ";
			cin >> element;
			list.insert(index, element);
			break;


		// Remove the specified element.
		case 5:
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
		case 6:
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
		case 8:
			cout << "size()" << endl;
			cout << "List size:  " << list.size() << endl;
			sleep_for(seconds(1));
			break;


		// Convert to a dynamic array.
		case 9:
			cout << "toDynamicArray()" << endl;
			delete array;
			try {
				array = list.toDynamicArray();
				size = list.size();
			} catch (char const* e) {
				cout << e << endl;
				size = 0;
				array = new uint[size];
				sleep_for(seconds(1));
			}
			break;


		// Convert to a dynamic array of specified size.
		case 10:
			cout << "toDynamicArray(size)" << endl;
			cout << "> size = ";
			cin >> size;
			delete array;
			try {
				array = list.toDynamicArray(size);
			} catch (char const* e) {
				cout << e << endl;
				size = 0;
				array = new uint[size];
				sleep_for(seconds(1));
			}
			break;
		}
	}

	// Clear dynamic memory.
	delete [] array;

	return 0;
}
