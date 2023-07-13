#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>
#include "heap.h"
#include "../../move_cursor/move_cursor.h"
#include "../../random/random.h"
using namespace std;
using namespace std::this_thread;	// sleep_for, sleep_until
using namespace std::chrono;		// nanoseconds, system_clock, seconds.


// Main function.
int main() {
	char answer[20];
	unsigned number;
	unsigned element;

	// Create the heap.
	Heap<unsigned> heap;
	Heap<unsigned> temp;

	// Initialise the array pointer.
	unsigned size = 0;
	unsigned* array = new unsigned[size];

	// Loop until Q has been entered.
	while (answer[0] != 'Q') {

		// Clear the screen
		clearScreen();

		// Print max/min heap status.
		cout << (heap.isMaxHeap() ? "MAX Heap\n" : "MIN Heap\n");

		// Traverse the heap.
		cout << "DFT:";
		heap.dft();
		cout << "BFT:";
		heap.bft();

		// Print the heap height and size.
		cout << "Height:  " << heap.height() << endl;
		cout << "Size:    " << heap.size() << endl;

		// Display the heap.
		heap.display();

		// Print the array.
		cout << "\nArray:" << endl;
		displayArray(array, size);

		// Print majority of available functions.
		cout << "\n==============================" << endl;
		cout << " (A)  Create Heap from Array" << endl;
		cout << " (1)  clear()" << endl;
		cout << " (2)  clone()" << endl;
		cout << " (3)  contains(element)" << endl;
		cout << " (4)  isEmpty() / isNotEmpty()" << endl;
		cout << " (5)  push(element)" << endl;
		cout << " (6)  pop()" << endl;
		cout << " (7)  toDynamicArray()" << endl;
		cout << " (8)  toDynamicArray(size)" << endl;
		cout << " (9)  toggleMaxMin()" << endl;
		cout << "(10)  operator=" << endl;
		cout << "(11)  operator+(element)" << endl;
		cout << "(12)  operator+=(element)" << endl;
		cout << "(13)  prefix operator--" << endl;
		cout << "(14)  postfix operator--" << endl;
		cout << " (Q)  << QUIT PROGRAM >>" << endl;
		cout << "==============================" << endl;
		cout << "> ";
		cin.getline(answer, 20);
		answer[0] = toupper(answer[0]);


		// Create heap from array.
		if (answer[0] == 'A') {
			cout << "Create Heap from Array" << endl;
			heap = Heap<unsigned>(array, size);
			continue;
		}


		// Any other character continues the loop.
		if (!isdigit(answer[0])) {
			continue;
		}


		// Switch statement for answer.
		number = atoi(answer);
		switch (number) {


		// Clear all elements in the heap.
		case 1:
			cout << "clear()" << endl;
			heap.clear();
			break;


		// Clone the heap.
		case 2:
			cout << "clone()" << endl;
			temp = heap.clone();
			cout << "> cloned heap:" << endl;
			temp.display();
			temp.clear();
			sleep_for(seconds(5));
			break;


		// Check if element is in the heap.
		case 3:
			cout << "contains(element)" << endl;
			cout << "> element = ";
			cin >> element;
			cout << "> '" << element << "' in heap:  ";
			cout << (heap.contains(element) ? "true\n" : "false\n");
			sleep_for(seconds(2));
			break;


		// Check if empty / not empty.
		case 4:
			cout << "isEmpty() / isNotEmpty()" << endl;
			cout << "> Heap IS empty:      ";
			cout << (heap.isEmpty() ? "true\n" : "false\n");
			cout << "> Heap is NOT empty:  ";
			cout << (heap.isNotEmpty() ? "true\n" : "false\n");
			sleep_for(seconds(3));
			break;


		// Push element onto the heap.
		case 5:
			cout << "push(element)" << endl;
			cout << "> element = ";
			cin >> element;
			heap.push(element);
			break;


		// Pop from the heap.
		case 6:
			cout << "pop()" << endl;
			try {
				element = heap.pop();
				cout << "> popped element:  " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Convert to a dynamic array.
		case 7:
			cout << "toDynamicArray()" << endl;
			delete array;
			try {
				array = heap.toDynamicArray();
				size = heap.size();
			} catch (char const* e) {
				cout << e << endl;
				size = 0;
				array = new unsigned[size];
				sleep_for(seconds(2));
			}
			break;


		// Convert to a dynamic array of specified size.
		case 8:
			cout << "toDynamicArray(size)" << endl;
			cout << "> size = ";
			cin >> size;
			delete array;
			try {
				array = heap.toDynamicArray(size);
			} catch (char const* e) {
				cout << e << endl;
				size = 0;
				array = new unsigned[size];
				sleep_for(seconds(2));
			}
			break;


		// Converts the heap from max to min or vice versa.
		case 9:
			cout << "toggleMaxMin()" << endl;
			heap.toggleMaxMin();
			temp.toggleMaxMin();
			break;


		// Work with the assignment operator.
		case 10:
			cout << "operator=" << endl;
			cout << "> number of elements = ";
			cin >> number;
			temp.clear();
			for (unsigned i = 0; i < number; i++) {
				temp.push(randUint(1, 999));
			}
			heap = temp;
			temp.clear();
			break;


		// Work with heap + element.
		case 11:
			cout << "operator+(element)" << endl;
			cout << "> element = ";
			cin >> element;
			temp = heap + element;
			cout << "> returned heap:" << endl;
			temp.display();
			temp.clear();
			sleep_for(seconds(5));
			break;


		// Work with heap += element.
		case 12:
			cout << "operator+=(element)" << endl;
			cout << "> element = ";
			cin >> element;
			heap += element;
			break;


		// Work with --heap;
		case 13:
			cout << "prefix operator--" << endl;
			try {
				--heap;
			} catch (char const* e) {
				cout << e << endl;
				sleep_for(seconds(2));
			}
			break;


		// Work with heap--;
		case 14:
			cout << "postfix operator--" << endl;
			try {
				temp = heap--;
				cout << "> returned heap:" << endl;
				temp.display();
				temp.clear();
				sleep_for(seconds(5));
			} catch (char const* e) {
				cout << e << endl;
				sleep_for(seconds(2));
			}
			break;
		}
	}

	// Clear dynamic memory.
	delete [] array;

	return 0;
}
