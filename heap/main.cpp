#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>
#include "heap.h"
#include "../move_cursor/move_cursor.h"
#include "../random/random.h"
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

		// Print majority of available functions.
		cout << "\n==============================" << endl;
		cout << " (1)  clear()" << endl;
		cout << " (2)  clone()" << endl;
		cout << " (3)  isEmpty() / isNotEmpty()" << endl;
		cout << " (4)  push(element)" << endl;
		cout << " (5)  pop()" << endl;
		cout << " (6)  toggleMaxMin()" << endl;
		cout << " (7)  operator=" << endl;
		cout << " (8)  operator+(element)" << endl;
		cout << " (9)  operator+=(element)" << endl;
		cout << "(10)  prefix operator--" << endl;
		cout << "(11)  postfix operator--" << endl;
		cout << " (Q)  << QUIT PROGRAM >>" << endl;
		cout << "==============================" << endl;
		cout << "> ";
		cin.getline(answer, 20);
		answer[0] = toupper(answer[0]);


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


		// Check if empty / not empty.
		case 3:
			cout << "isEmpty() / isNotEmpty()" << endl;
			cout << "> Heap IS empty:      ";
			cout << (heap.isEmpty() ? "true\n" : "false\n");
			cout << "> Heap is NOT empty:  ";
			cout << (heap.isNotEmpty() ? "true\n" : "false\n");
			sleep_for(seconds(3));
			break;


		// Push element onto the heap.
		case 4:
			cout << "push(element)" << endl;
			cout << "> element = ";
			cin >> element;
			heap.push(element);
			break;


		// Pop from the heap.
		case 5:
			cout << "pop()" << endl;
			try {
				element = heap.pop();
				cout << "> popped element:  " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Converts the heap from max to min or vice versa.
		case 6:
			cout << "toggleMaxMin()" << endl;
			heap.toggleMaxMin();
			temp.toggleMaxMin();
			break;


		// Work with the assignment operator.
		case 7:
			cout << "operator=" << endl;
			cout << "> number of elements = ";
			cin >> number;
			temp.clear();
			for (unsigned i = 0; i < number; i++) {
				temp.push(randUint(0, 999));
			}
			heap = temp;
			temp.clear();
			break;


		// Work with heap + element.
		case 8:
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
		case 9:
			cout << "operator+=(element)" << endl;
			cout << "> element = ";
			cin >> element;
			heap += element;
			break;


		// Work with --heap;
		case 10:
			cout << "prefix operator--" << endl;
			try {
				--heap;
			} catch (char const* e) {
				cout << e << endl;
				sleep_for(seconds(2));
			}
			break;


		// Work with heap--;
		case 11:
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

	return 0;
}
