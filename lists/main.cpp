#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>
#include "linked_list.h"
#include "../move_cursor/move_cursor.h"
#include "../random/random.h"
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
	uint start, end;
	uint number;
	uint element;
	size_t index;
	LinkedList<uint>* sublist = nullptr;

	// Create the linked list.
	LinkedList<uint> list;
	LinkedList<uint> temp;

	// Declare the array pointer.
	uint size = 0;
	uint* array = new uint[size];

	// Loop until Q has been entered.
	while (answer[0] != 'Q') {

		// Clear the screen
		clearScreen();

		// Print the linked list.
		cout << "List:" << endl;
		cout << list.toString() << endl;

		// Print the array.
		cout << "\nArray:" << endl;
		displayArray(array, size);

		// Print majority of available functions.
		cout << "\n==============================" << endl;
		cout << " (A)  Create List from Array" << endl;
		cout << " (1)  add(element)" << endl;
		cout << " (2)  clear()" << endl;
		cout << " (3)  clone()" << endl;
		cout << " (4)  first()" << endl;
		cout << " (5)  get(index)" << endl;
		cout << " (6)  getNext()" << endl;
		cout << " (7)  indexOf(element)" << endl;
		cout << " (8)  insert(index, element)" << endl;
		cout << " (9)  isEmpty()" << endl;
		cout << "(10)  last()" << endl;
		cout << "(11)  remove(element)" << endl;
		cout << "(12)  removeAt(index)" << endl;
		cout << "(13)  resetNext()" << endl;
		cout << "(14)  set(index, element)" << endl;
		cout << "(15)  size()" << endl;
		cout << "(16)  subList(start, end)" << endl;
		cout << "(17)  toDynamicArray()" << endl;
		cout << "(18)  toDynamicArray(size)" << endl;
		cout << "(19)  operator=" << endl;
		cout << "(20)  operator[]" << endl;
		cout << "(21)  operator+(element)" << endl;
		cout << "(22)  operator+(list)" << endl;
		cout << "(23)  operator+=(element)" << endl;
		cout << "(24)  operator+=(list)" << endl;
		cout << " (Q)  << QUIT PROGRAM >>" << endl;
		cout << "==============================" << endl;
		cout << "> ";
		cin.getline(answer, 3);
		answer[0] = toupper(answer[0]);


		// Create list from array.
		if (answer[0] == 'A') {
			cout << "Create List from Array" << endl;
			list = LinkedList(array, size);
			continue;
		}


		// Any other character continues the loop.
		if (isalpha(answer[0])) {
			continue;
		}


		// Validate the input.
		number = atoi(answer);
		if (number == 0 || number > 24) {
			continue;
		}

		// Switch statement for answer.
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


		// Clones the list.
		case 3:
			cout << "clone()" << endl;
			temp = list.clone();
			cout << "> cloned list:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;


		// Get the first element in the list.
		case 4:
			cout << "first()" << endl;
			try {
				element = list.first();
				cout << "> first element:  " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Get element at index.
		case 5:
			cout << "get(index)" << endl;
			cout << "> index = ";
			cin >> index;
			try {
				element = list.get(index);
				cout << "list["<<index<<"] = " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Get the next element in the list.
		case 6:
			cout << "getNext()" << endl;
			try {
				element = list.getNext();
				cout << "> next element:  " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Find the index of the given element.
		case 7:
			cout << "indexOf(element)" << endl;
			cout << "> element = ";
			cin >> element;
			cout << "> Found at index:  " << list.indexOf(element) << endl;
			sleep_for(seconds(2));
			break;


		// Insert an element.
		case 8:
			cout << "insert(index, element)" << endl;
			cout << "> index = ";
			cin >> index;
			cout << "> element = ";
			cin >> element;
			list.insert(index, element);
			break;


		// Check if empty.
		case 9:
			cout << "isEmpty()" << endl;
			if (list.isEmpty()) {
				cout << "The list is empty" << endl;
			} else {
				cout << "The list contains elements" << endl;
			}
			sleep_for(seconds(2));
			break;


		// Get the last element in the list.
		case 10:
			cout << "last()" << endl;
			try {
				element = list.last();
				cout << "> last element:  " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Remove the specified element.
		case 11:
			cout << "remove(element)" << endl;
			cout << "> element = ";
			cin >> element;
			try {
				list.remove(element);
			} catch (string e) {
				cout << e << endl;
				sleep_for(seconds(2));
			}
			break;


		// Remove element at the given index.
		case 12:
			cout << "removeAt(index)" << endl;
			cout << "> index = ";
			cin >> index;
			try {
				list.removeAt(index);
			} catch (char const* e) {
				cout << e << endl;
				sleep_for(seconds(2));
			}
			break;


		// Reset the current pointer.
		case 13:
			cout << "resetNext()" << endl;
			list.resetNext();
			break;


		// Set element at given index.
		case 14:
			cout << "set(index, element)" << endl;
			cout << "> index = ";
			cin >> index;
			cout << "> element = ";
			cin >> element;
			list.set(index, element);
			break;


		// Display the number of elements.
		case 15:
			cout << "size()" << endl;
			cout << "List size:  " << list.size() << endl;
			sleep_for(seconds(2));
			break;


		// Creates sub list from start to end.
		case 16:
			cout << "subList(start, end)" << endl;
			cout << "> start = ";
			cin >> start;
			cout << "> end = ";
			cin >> end;
			try {
				sublist = list.subList(start, end);
				cout << "Sublist:  " << sublist->toString() << endl;
				delete sublist;
				sublist = nullptr;
				sleep_for(seconds(5));
			} catch (char const* e) {
				cout << e << endl;
				sleep_for(seconds(2));
			}
			break;


		// Convert to a dynamic array.
		case 17:
			cout << "toDynamicArray()" << endl;
			delete array;
			try {
				array = list.toDynamicArray();
				size = list.size();
			} catch (char const* e) {
				cout << e << endl;
				size = 0;
				array = new uint[size];
				sleep_for(seconds(2));
			}
			break;


		// Convert to a dynamic array of specified size.
		case 18:
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
				sleep_for(seconds(2));
			}
			break;


		// Work with the assignment operator.
		case 19:
			cout << "operator=" << endl;
			cout << "> new size = ";
			cin >> number;
			temp.clear();
			for (size_t i = 0; i < number; i++) {
				temp.add(randUint(10, 99));
			}
			list = temp;
			break;


		// Work with the subscript operator.
		case 20:
			cout << "operator[]" << endl;
			cout << "> set or get value (s/g):  ";
			cin.getline(answer, 3);
			answer[0] = tolower(answer[0]);
			if (answer[0] == 's') {
				cout << "Setting value" << endl;
				cout << "> index = ";
				cin >> index;
				cout << "> element = ";
				cin >> element;
				try {
					list[index] = element;
				} catch (char const* e) {
					cout << e << endl;
					sleep_for(seconds(2));
				}
			} else if (answer[0] == 'g') {
				cout << "Getting value:" << endl;
				cout << "> index = ";
				cin >> index;
				try {
					element = list[index];
					cout << "list["<<index<<"] = " << element << endl;
				} catch (char const* e) {
					cout << e << endl;
				}
				sleep_for(seconds(2));
			}
			break;


		// Work with list + element.
		case 21:
			cout << "operator+(element)" << endl;
			cout << "> element = ";
			cin >> element;
			temp = list + element;
			cout << "> new list:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;
		

		// Work with list + other list.
		case 22:
			cout << "operator+(list)" << endl;
			cout << "> other list size = ";
			cin >> number;
			temp.clear();
			for (size_t i = 0; i < number; i++) {
				temp.add(randUint(10, 99));
			}
			temp = list + temp;
			cout << "> new list:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;
		

		// Work with list += element.
		case 23:
			cout << "operator+=(element)" << endl;
			cout << "> element = ";
			cin >> element;
			list += element;
			break;
		

		// Work with list += other list.
		case 24:
			cout << "operator+=(list)" << endl;
			cout << "> other list size = ";
			cin >> number;
			temp.clear();
			for (size_t i = 0; i < number; i++) {
				temp.add(randUint(10, 99));
			}
			list += temp;
			break;

		}
	}

	// Clear dynamic memory.
	delete [] array;

	return 0;
}
