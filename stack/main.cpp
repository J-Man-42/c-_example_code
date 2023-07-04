#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>
#include "stack.h"
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

	// Create the stack.
	Stack<uint> stack;
	Stack<uint> temp;

	// Declare the array pointer.
	uint size = 0;
	uint* array = new uint[size];

	// Loop until Q has been entered.
	while (answer[0] != 'Q') {

		// Clear the screen
		clearScreen();

		// Print the stack.
		cout << "Stack:" << endl;
		cout << stack << endl;

		// Print the array.
		cout << "\nArray:" << endl;
		displayArray(array, size);

		// Print majority of available functions.
		cout << "\n==============================" << endl;
		cout << " (A)  Create Stack from Array" << endl;
		cout << " (1)  clear()" << endl;
		cout << " (2)  clone()" << endl;
		cout << " (3)  contains(element)" << endl;
		cout << " (4)  isEmpty() / isNotEmpty()" << endl;
		cout << " (5)  pop()" << endl;
		cout << " (6)  push(element)" << endl;
		cout << " (7)  size()" << endl;
		cout << " (8)  top()" << endl;
		cout << " (9)  toDynamicArray()" << endl;
		cout << "(10)  toDynamicArray(size)" << endl;
		cout << "(11)  operator=" << endl;
		cout << "(12)  operator+(element)" << endl;
		cout << "(13)  operator+(stack)" << endl;
		cout << "(14)  operator+=(element)" << endl;
		cout << "(15)  operator+=(stack)" << endl;
		cout << " (Q)  << QUIT PROGRAM >>" << endl;
		cout << "==============================" << endl;
		cout << "> ";
		cin.getline(answer, 3);
		answer[0] = toupper(answer[0]);


		// Create stack from array.
		if (answer[0] == 'A') {
			cout << "Create Stack from Array" << endl;
			stack = Stack<uint>(array, size);
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


		// Clear all elements.
		case 1:
			cout << "clear()" << endl;
			stack.clear();
			break;


		// Clones the stack.
		case 2:
			cout << "clone()" << endl;
			temp = stack.clone();
			cout << "> cloned stack:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;


		// See if an element is in the stack.
		case 3:
			cout << "contains(element)" << endl;
			cout << "> element = ";
			cin >> element;
			cout << "> " << element << " in stack:  ";
			if (stack.contains(element)) {
				cout << "true" << endl;
			} else {
				cout << "false" << endl;
			}
			sleep_for(seconds(2));
			break;


		// Check if empty.
		case 4:
			cout << "isEmpty() / isNotEmpty()" << endl;
			cout << "> Stack IS empty:      ";
			cout << (stack.isEmpty() ? "true\n" : "false\n");
			cout << "> Stack is NOT empty:  ";
			cout << (stack.isNotEmpty() ? "true\n" : "false\n");
			sleep_for(seconds(3));
			break;


		// Remove element at the front of the stack.
		case 5:
			cout << "pop()" << endl;
			try {
				element = stack.pop();
				cout << "popped element:  " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Push an element to the back of the stack.
		case 6:
			cout << "push(element)" << endl;
			cout << "> element = ";
			cin >> element;
			stack.push(element);
			break;


		// Display the number of elements.
		case 7:
			cout << "size()" << endl;
			cout << "Stack size:  " << stack.size() << endl;
			sleep_for(seconds(2));
			break;


		// Get the element at the top of the stack.
		case 8:
			cout << "top()" << endl;
			try {
				element = stack.top();
				cout << "> top of stack:  " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Convert to a dynamic array.
		case 9:
			cout << "toDynamicArray()" << endl;
			delete array;
			try {
				array = stack.toDynamicArray();
				size = stack.size();
			} catch (char const* e) {
				cout << e << endl;
				size = 0;
				array = new uint[size];
				sleep_for(seconds(2));
			}
			break;


		// Convert to a dynamic array of specified size.
		case 10:
			cout << "toDynamicArray(size)" << endl;
			cout << "> size = ";
			cin >> size;
			delete array;
			try {
				array = stack.toDynamicArray(size);
			} catch (char const* e) {
				cout << e << endl;
				size = 0;
				array = new uint[size];
				sleep_for(seconds(2));
			}
			break;


		// Work with the assignment operator.
		case 11:
			cout << "operator=" << endl;
			cout << "> new size = ";
			cin >> number;
			temp.clear();
			for (size_t i = 0; i < number; i++) {
				temp.push(randUint(10, 99));
			}
			stack = temp;
			break;


		// Work with stack + element.
		case 12:
			cout << "operator+(element)" << endl;
			cout << "> element = ";
			cin >> element;
			temp = stack + element;
			cout << "> new stack:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;


		// Work with stack + other stack.
		case 13:
			cout << "operator+(stack)" << endl;
			cout << "> other stack size = ";
			cin >> number;
			temp.clear();
			for (size_t i = 0; i < number; i++) {
				temp.push(randUint(10, 99));
			}
			temp = stack + temp;
			cout << "> new stack:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;


		// Work with stack += element.
		case 14:
			cout << "operator+=(element)" << endl;
			cout << "> element = ";
			cin >> element;
			stack += element;
			break;


		// Work with stack += other stack.
		case 15:
			cout << "operator+=(stack)" << endl;
			cout << "> other stack size = ";
			cin >> number;
			temp.clear();
			for (size_t i = 0; i < number; i++) {
				temp.push(randUint(10, 99));
			}
			stack += temp;
			break;

		}
	}

	// Clear dynamic memory.
	delete [] array;

	return 0;
}
