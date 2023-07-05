#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>
#include "linked_list.h"
#include "../display_structure/display_structure.h"
#include "../move_cursor/move_cursor.h"
#include "../random/random.h"
using namespace std;
using namespace std::this_thread;	// sleep_for, sleep_until
using namespace std::chrono;		// nanoseconds, system_clock, seconds.



// Main function.
int main() {
	char answer[3];
	unsigned start, end;
	unsigned number;
	unsigned element;
	int index;
	LinkedList<unsigned>* sublist = nullptr;

	// Create the linked list.
	LinkedList<unsigned> list;
	LinkedList<unsigned> temp;

	// Declare the array pointer.
	unsigned size = 0;
	unsigned* array = new unsigned[size];

	// Loop until Q has been entered.
	while (answer[0] != 'Q') {

		// Clear the screen
		clearScreen();

		// Print the linked list.
		cout << "List:" << endl;
		cout << list << endl;

		// Print the array.
		cout << "\nArray:" << endl;
		displayArray(array, size);

		// Print majority of available functions.
		cout << "\n==============================" << endl;
		cout << " (A)  Create List from Array" << endl;
		cout << " (1)  append(element)" << endl;
		cout << " (2)  contains(element)" << endl;
		cout << " (3)  clear()" << endl;
		cout << " (4)  clone()" << endl;
		cout << " (5)  get(index)" << endl;
		cout << " (6)  getFirst()" << endl;
		cout << " (7)  getLast()" << endl;
		cout << " (8)  getNext()" << endl;
		cout << " (9)  indexOf(element)" << endl;
		cout << "(10)  insert(element)" << endl;
		cout << "(11)  insertAt(index, element)" << endl;
		cout << "(12)  isEmpty() / isNotEmpty()" << endl;
		cout << "(13)  remove(element)" << endl;
		cout << "(14)  removeAt(index)" << endl;
		cout << "(15)  removeFirst()" << endl;
		cout << "(16)  removeLast()" << endl;
		cout << "(17)  resetNext()" << endl;
		cout << "(18)  reverse()" << endl;
		cout << "(19)  reversed()" << endl;
		cout << "(20)  set(index, element)" << endl;
		cout << "(21)  setFirst(element)" << endl;
		cout << "(22)  setLast(element)" << endl;
		cout << "(23)  size()" << endl;
		cout << "(24)  subList(start, end)" << endl;
		cout << "(25)  toDynamicArray()" << endl;
		cout << "(26)  toDynamicArray(size)" << endl;
		cout << "(27)  operator=" << endl;
		cout << "(28)  operator[]" << endl;
		cout << "(29)  operator+(element)" << endl;
		cout << "(30)  operator+(list)" << endl;
		cout << "(31)  operator+=(element)" << endl;
		cout << "(32)  operator+=(list)" << endl;
		cout << " (Q)  << QUIT PROGRAM >>" << endl;
		cout << "==============================" << endl;
		cout << "> ";
		cin.getline(answer, 3);
		answer[0] = toupper(answer[0]);


		// Create list from array.
		if (answer[0] == 'A') {
			cout << "Create List from Array" << endl;
			list = LinkedList<unsigned>(array, size);
			continue;
		}


		// Any other character continues the loop.
		if (isalpha(answer[0])) {
			continue;
		}


		// Validate the input.
		number = atoi(answer);
		if (number == 0 || number > 32) {
			continue;
		}

		// Switch statement for answer.
		switch (number) {


		// Append an element to the list.
		case 1:
			cout << "append(element)" << endl;
			cout << "> element = ";
			cin >> element;
			list.append(element);
			break;


		// Check if element is in the list.
		case 2:
			cout << "contains(element)" << endl;
			cout << "> element = ";
			cin >> element;
			cout << "> List contains " << element << ":  ";
			if (list.contains(element)) {
				cout << "true" << endl;
			} else {
				cout << "false" << endl;
			}
			sleep_for(seconds(2));
			break;


		// Clear all elements.
		case 3:
			cout << "clear()" << endl;
			list.clear();
			break;


		// Clones the list.
		case 4:
			cout << "clone()" << endl;
			temp = list.clone();
			cout << "> cloned list:  " << temp.toString() << endl;
			sleep_for(seconds(5));
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


		// Get the first element in the list.
		case 6:
			cout << "getFirst()" << endl;
			try {
				element = list.getFirst();
				cout << "> first element:  " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Get the last element in the list.
		case 7:
			cout << "getLast()" << endl;
			try {
				element = list.getLast();
				cout << "> last element:  " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Get the next element in the list.
		case 8:
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
		case 9:
			cout << "indexOf(element)" << endl;
			cout << "> element = ";
			cin >> element;
			cout << "> Found at index:  " << list.indexOf(element) << endl;
			sleep_for(seconds(2));
			break;


		// Insert an element at the beginning of the list.
		case 10:
			cout << "insert(element)" << endl;
			cout << "> element = ";
			cin >> element;
			list.insert(element);
			break;


		// Insert an element at the given index.
		case 11:
			cout << "insertAt(index, element)" << endl;
			cout << "> index = ";
			cin >> index;
			cout << "> element = ";
			cin >> element;
			list.insertAt(index, element);
			break;


		// Check if empty.
		case 12:
			cout << "isEmpty() / isNotEmpty()" << endl;
			cout << "> List IS empty:      ";
			cout << (list.isEmpty() ? "true\n" : "false\n");
			cout << "> List is NOT empty:  ";
			cout << (list.isNotEmpty() ? "true\n" : "false\n");
			sleep_for(seconds(3));
			break;


		// Remove the specified element.
		case 13:
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
		case 14:
			cout << "removeAt(index)" << endl;
			cout << "> index = ";
			cin >> index;
			try {
				element = list.removeAt(index);
				cout << "removed element " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Remove the first element in the list.
		case 15:
			cout << "removeFirst()" << endl;
			try {
				element = list.removeFirst();
				cout << "removed element " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Remove the last element in the list.
		case 16:
			cout << "removeLast()" << endl;
			try {
				element = list.removeLast();
				cout << "removed element " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Reset the current pointer.
		case 17:
			cout << "resetNext()" << endl;
			list.resetNext();
			break;


		// Reverse the linked list.
		case 18:
			cout << "reverse()" << endl;
			list.reverse();
			break;


		// Return a reversed version of this list.
		case 19:
			cout << "reversed()" << endl;
			temp = list.reversed();
			cout << "Reversed:  " << temp << endl;
			sleep_for(seconds(5));
			break;


		// Set element at given index.
		case 20:
			cout << "set(index, element)" << endl;
			cout << "> index = ";
			cin >> index;
			cout << "> element = ";
			cin >> element;
			list.set(index, element);
			break;


		// Set the first element in the list.
		case 21:
			cout << "setFirst(element)" << endl;
			cout << "> element = ";
			cin >> element;
			list.setFirst(element);
			break;


		// Set the last element in the list.
		case 22:
			cout << "setLast(element)" << endl;
			cout << "> element = ";
			cin >> element;
			list.setLast(element);
			break;


		// Display the number of elements.
		case 23:
			cout << "size()" << endl;
			cout << "List size:  " << list.size() << endl;
			sleep_for(seconds(2));
			break;


		// Creates sub list from start to end.
		case 24:
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
		case 25:
			cout << "toDynamicArray()" << endl;
			delete array;
			try {
				array = list.toDynamicArray();
				size = list.size();
			} catch (char const* e) {
				cout << e << endl;
				size = 0;
				array = new unsigned[size];
				sleep_for(seconds(2));
			}
			break;


		// Convert to a dynamic array of specified size.
		case 26:
			cout << "toDynamicArray(size)" << endl;
			cout << "> size = ";
			cin >> size;
			delete array;
			try {
				array = list.toDynamicArray(size);
			} catch (char const* e) {
				cout << e << endl;
				size = 0;
				array = new unsigned[size];
				sleep_for(seconds(2));
			}
			break;


		// Work with the assignment operator.
		case 27:
			cout << "operator=" << endl;
			cout << "> new size = ";
			cin >> number;
			temp.clear();
			for (unsigned i = 0; i < number; i++) {
				temp.append(randUint(10, 99));
			}
			list = temp;
			break;


		// Work with the subscript operator.
		case 28:
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
		case 29:
			cout << "operator+(element)" << endl;
			cout << "> element = ";
			cin >> element;
			temp = list + element;
			cout << "> new list:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;


		// Work with list + other list.
		case 30:
			cout << "operator+(list)" << endl;
			cout << "> other list size = ";
			cin >> number;
			temp.clear();
			for (unsigned i = 0; i < number; i++) {
				temp.append(randUint(10, 99));
			}
			temp = list + temp;
			cout << "> new list:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;


		// Work with list += element.
		case 31:
			cout << "operator+=(element)" << endl;
			cout << "> element = ";
			cin >> element;
			list += element;
			break;


		// Work with list += other list.
		case 32:
			cout << "operator+=(list)" << endl;
			cout << "> other list size = ";
			cin >> number;
			temp.clear();
			for (unsigned i = 0; i < number; i++) {
				temp.append(randUint(10, 99));
			}
			list += temp;
			break;

		}
	}

	// Clear dynamic memory.
	delete [] array;

	return 0;
}
