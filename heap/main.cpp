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
		// cout << " (4)  contains(element)" << endl;
		// cout << " (5)  insert(element)" << endl;
		// cout << " (7)  remove(element)" << endl;
		// cout << "(11)  operator-(element)" << endl;
		// cout << "(12)  operator-=(element)" << endl;
		cout << " (3)  isEmpty() / isNotEmpty()" << endl;
		cout << " (4)  push(element)" << endl;
		cout << " (5)  pop()" << endl;
		cout << " (6)  operator=" << endl;
		cout << " (7)  operator+(element)" << endl;
		cout << " (8)  operator+=(element)" << endl;
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
			heap.display();
			sleep_for(seconds(5));
			break;


		// // Test if element in the heap.
		// case 4:
		// 	cout << "contains(element)" << endl;
		// 	cout << "> element = ";
		// 	cin >> element;
		// 	cout << "> Tree contains " << element << ":  ";
		// 	if (heap.contains(element)) {
		// 		cout << "true" << endl;
		// 	} else {
		// 		cout << "false" << endl;
		// 	}
		// 	sleep_for(seconds(2));
		// 	break;


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
			break;


		// Work with the assignment operator.
		case 6:
			cout << "operator=" << endl;
			cout << "> number of elements = ";
			cin >> number;
			temp.clear();
			for (unsigned i = 0; i < number; i++) {
				temp.push(randUint(0, 999));
			}
			heap = temp;
			break;


		// Work with heap + element.
		case 7:
			cout << "operator+(element)" << endl;
			cout << "> element = ";
			cin >> element;
			temp = heap + element;
			cout << "> returned heap:" << endl;
			temp.display();
			sleep_for(seconds(5));
			break;


		// Work with heap += element.
		case 8:
			cout << "operator+=(element)" << endl;
			cout << "> element = ";
			cin >> element;
			heap += element;
			break;
		}
	}

	return 0;
}
