#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>
#include "queue.h"
#include "../display_structure/display_structure.h"
#include "../move_cursor/move_cursor.h"
#include "../random/random.h"
using namespace std;
using namespace std::this_thread;	// sleep_for, sleep_until
using namespace std::chrono;		// nanoseconds, system_clock, seconds.



// Main function.
int main() {
	char answer[3];
	uint number;
	uint element;

	// Create the queue.
	Queue<uint> queue;
	Queue<uint> temp;

	// Declare the array pointer.
	uint size = 0;
	uint* array = new uint[size];

	// Loop until Q has been entered.
	while (answer[0] != 'Q') {

		// Clear the screen
		clearScreen();

		// Print the queue.
		cout << "Queue:" << endl;
		cout << queue << endl;

		// Print the array.
		cout << "\nArray:" << endl;
		displayArray(array, size);

		// Print majority of available functions.
		cout << "\n==============================" << endl;
		cout << " (A)  Create Queue from Array" << endl;
		cout << " (1)  back()" << endl;
		cout << " (2)  clear()" << endl;
		cout << " (3)  clone()" << endl;
		cout << " (4)  contains(element)" << endl;
		cout << " (5)  front()" << endl;
		cout << " (6)  isEmpty() / isNotEmpty()" << endl;
		cout << " (7)  pop()" << endl;
		cout << " (8)  push(element)" << endl;
		cout << " (9)  size()" << endl;
		cout << "(10)  toDynamicArray()" << endl;
		cout << "(11)  toDynamicArray(size)" << endl;
		cout << "(12)  operator=" << endl;
		cout << "(13)  operator+(element)" << endl;
		cout << "(14)  operator+(queue)" << endl;
		cout << "(15)  operator+=(element)" << endl;
		cout << "(16)  operator+=(queue)" << endl;
		cout << " (Q)  << QUIT PROGRAM >>" << endl;
		cout << "==============================" << endl;
		cout << "> ";
		cin.getline(answer, 3);
		answer[0] = toupper(answer[0]);


		// Create queue from array.
		if (answer[0] == 'A') {
			cout << "Create Queue from Array" << endl;
			queue = Queue<uint>(array, size);
			continue;
		}


		// Any other character continues the loop.
		if (isalpha(answer[0])) {
			continue;
		}


		// Validate the input.
		number = atoi(answer);
		if (number == 0 || number > 16) {
			continue;
		}

		// Switch statement for answer.
		switch (number) {


		// Get the last element in the queue.
		case 1:
			cout << "back()" << endl;
			try {
				element = queue.back();
				cout << "> last element:  " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Clear all elements.
		case 2:
			cout << "clear()" << endl;
			queue.clear();
			break;


		// Clones the queue.
		case 3:
			cout << "clone()" << endl;
			temp = queue.clone();
			cout << "> cloned queue:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;


		// See if an element is in the queue.
		case 4:
			cout << "contains(element)" << endl;
			cout << "> element = ";
			cin >> element;
			cout << "> " << element << " in queue:  ";
			if (queue.contains(element)) {
				cout << "true" << endl;
			} else {
				cout << "false" << endl;
			}
			sleep_for(seconds(2));
			break;


		// Get the first element in the queue.
		case 5:
			cout << "front()" << endl;
			try {
				element = queue.front();
				cout << "> first element:  " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Check if empty.
		case 6:
			cout << "isEmpty() / isNotEmpty()" << endl;
			cout << "> Queue IS empty:      ";
			cout << (queue.isEmpty() ? "true\n" : "false\n");
			cout << "> Queue is NOT empty:  ";
			cout << (queue.isNotEmpty() ? "true\n" : "false\n");
			sleep_for(seconds(3));
			break;


		// Remove element at the front of the queue.
		case 7:
			cout << "pop()" << endl;
			try {
				element = queue.pop();
				cout << "popped element:  " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Push an element to the back of the queue.
		case 8:
			cout << "push(element)" << endl;
			cout << "> element = ";
			cin >> element;
			queue.push(element);
			break;


		// Display the number of elements.
		case 9:
			cout << "size()" << endl;
			cout << "Queue size:  " << queue.size() << endl;
			sleep_for(seconds(2));
			break;


		// Convert to a dynamic array.
		case 10:
			cout << "toDynamicArray()" << endl;
			delete array;
			try {
				array = queue.toDynamicArray();
				size = queue.size();
			} catch (char const* e) {
				cout << e << endl;
				size = 0;
				array = new uint[size];
				sleep_for(seconds(2));
			}
			break;


		// Convert to a dynamic array of specified size.
		case 11:
			cout << "toDynamicArray(size)" << endl;
			cout << "> size = ";
			cin >> size;
			delete array;
			try {
				array = queue.toDynamicArray(size);
			} catch (char const* e) {
				cout << e << endl;
				size = 0;
				array = new uint[size];
				sleep_for(seconds(2));
			}
			break;


		// Work with the assignment operator.
		case 12:
			cout << "operator=" << endl;
			cout << "> new size = ";
			cin >> number;
			temp.clear();
			for (size_t i = 0; i < number; i++) {
				temp.push(randUint(10, 99));
			}
			queue = temp;
			break;


		// Work with queue + element.
		case 13:
			cout << "operator+(element)" << endl;
			cout << "> element = ";
			cin >> element;
			temp = queue + element;
			cout << "> new queue:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;


		// Work with queue + other queue.
		case 14:
			cout << "operator+(queue)" << endl;
			cout << "> other queue size = ";
			cin >> number;
			temp.clear();
			for (size_t i = 0; i < number; i++) {
				temp.push(randUint(10, 99));
			}
			temp = queue + temp;
			cout << "> new queue:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;


		// Work with queue += element.
		case 15:
			cout << "operator+=(element)" << endl;
			cout << "> element = ";
			cin >> element;
			queue += element;
			break;


		// Work with queue += other queue.
		case 16:
			cout << "operator+=(queue)" << endl;
			cout << "> other queue size = ";
			cin >> number;
			temp.clear();
			for (size_t i = 0; i < number; i++) {
				temp.push(randUint(10, 99));
			}
			queue += temp;
			break;

		}
	}

	// Clear dynamic memory.
	delete [] array;

	return 0;
}
