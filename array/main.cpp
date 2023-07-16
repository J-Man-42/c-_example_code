#include <iostream>
#include <chrono>
#include <thread>
#include "array.h"
#include "../move_cursor/move_cursor.h"
#include "../random/random.h"
using namespace std;
using namespace std::this_thread;	// sleep_for, sleep_until
using namespace std::chrono;		// nanoseconds, system_clock, seconds.


// Main function.
int main() {
	char answer[20];
	unsigned start, end;
	unsigned number;
	unsigned element;
	int index;
	Array<unsigned>* subArray = nullptr;

	// Create the array.
	Array<unsigned> array(10);
	Array<unsigned> temp(10);

	// Loop until Q has been entered.
	while (answer[0] != 'Q') {

		// Clear the screen
		clearScreen();

		// Print the array size.
		cout << "Size:   ";
		cout << array.size() << endl;

		// Print the array.
		cout << "Array:  ";
		cout << array << endl;

		// Print majority of available functions.
		cout << "\n==============================" << endl;
		cout << " (Q)  << QUIT PROGRAM >>" << endl;
		cout << " (1)  append(element)" << endl;
		cout << " (2)  contains(element)" << endl;
		cout << " (3)  clone()" << endl;
		cout << " (4)  get(index)" << endl;
		cout << " (5)  indexOf(element)" << endl;
		cout << " (6)  insert(element)" << endl;
		cout << " (7)  insertAt(index, element)" << endl;
		cout << " (8)  reverse()" << endl;
		cout << " (9)  reversed()" << endl;
		cout << "(10)  set(index, element)" << endl;
		cout << "(11)  subArray(start, end)" << endl;
		cout << "(12)  operator=" << endl;
		cout << "(13)  operator[]" << endl;
		cout << "(14)  operator+(element)" << endl;
		cout << "(15)  operator+(array)" << endl;
		cout << "(16)  operator+=(element)" << endl;
		cout << "(17)  operator+=(array)" << endl;
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


		// Append an element to the array.
		case 1:
			cout << "append(element)" << endl;
			cout << "> element = ";
			cin >> element;
			array.append(element);
			break;


		// Check if element is in the array.
		case 2:
			cout << "contains(element)" << endl;
			cout << "> element = ";
			cin >> element;
			cout << "> array contains " << element << ":  ";
			if (array.contains(element)) {
				cout << "true" << endl;
			} else {
				cout << "false" << endl;
			}
			sleep_for(seconds(2));
			break;


		// Clone the array.
		case 3:
			cout << "clone()" << endl;
			temp = array.clone();
			cout << "> cloned array:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;


		// Get element at index.
		case 4:
			cout << "get(index)" << endl;
			cout << "> index = ";
			cin >> index;
			try {
				element = array.get(index);
				cout << "array["<<index<<"] = " << element << endl;
			} catch (char const* e) {
				cout << e << endl;
			}
			sleep_for(seconds(2));
			break;


		// Find the index of the given element.
		case 5:
			cout << "indexOf(element)" << endl;
			cout << "> element = ";
			cin >> element;
			cout << "> index of " << element << ":  ";
			cout << array.indexOf(element) << endl;
			sleep_for(seconds(2));
			break;


		// Insert an element at the beginning of the array.
		case 6:
			cout << "insert(element)" << endl;
			cout << "> element = ";
			cin >> element;
			array.insert(element);
			break;


		// Insert an element at the given index.
		case 7:
			cout << "insertAt(index, element)" << endl;
			cout << "> index = ";
			cin >> index;
			cout << "> element = ";
			cin >> element;
			try {
				array.insertAt(index, element);
			} catch (char const* e) {
				cout << e << endl;
				sleep_for(seconds(2));
			}
			break;


		// Reverse the array.
		case 8:
			cout << "reverse()" << endl;
			array.reverse();
			break;


		// Return a reversed version of this array.
		case 9:
			cout << "reversed()" << endl;
			temp = array.reversed();
			cout << "> Reversed:  " << temp << endl;
			sleep_for(seconds(5));
			break;


		// Set element at given index.
		case 10:
			cout << "set(index, element)" << endl;
			cout << "> index = ";
			cin >> index;
			cout << "> element = ";
			cin >> element;
			try {
				array.set(index, element);
			} catch (char const* e) {
				cout << e << endl;
				sleep_for(seconds(2));
			}
			break;


		// Creates sub array from start to end.
		case 11:
			cout << "subArray(start, end)" << endl;
			cout << "> start = ";
			cin >> start;
			cout << "> end = ";
			cin >> end;
			try {
				subArray = array.subArray(start, end);
				cout << "> subArray:  " << subArray->toString() << endl;
				delete subArray;
				subArray = nullptr;
				sleep_for(seconds(5));
			} catch (char const* e) {
				cout << e << endl;
				sleep_for(seconds(2));
			}
			break;


		// Work with the assignment operator.
		case 12:
			cout << "operator=" << endl;
			cout << "> new size = ";
			cin >> number;
			temp = Array<unsigned>(number);
			for (unsigned i = 0; i < number; i++) {
				temp[i] = randUint(10, 99);
			}
			array = temp;
			break;


		// Work with the subscript operator.
		case 13:
			cout << "operator[]" << endl;
			cout << "> index = ";
			cin >> index;
			cout << "> element = ";
			cin >> element;
			try {
				array[index] = element;
			} catch (char const* e) {
				cout << e << endl;
				sleep_for(seconds(2));
			}
			break;


		// Work with array + element.
		case 14:
			cout << "operator+(element)" << endl;
			cout << "> element = ";
			cin >> element;
			temp = array + element;
			cout << "> new array:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;


		// Work with array + other array.
		case 15:
			cout << "operator+(array)" << endl;
			cout << "> other array size = ";
			cin >> number;
			temp = Array<unsigned>(number);
			for (unsigned i = 0; i < number; i++) {
				temp[i] = randUint(10, 99);
			}
			temp = array + temp;
			cout << "> new array:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;


		// Work with array += element.
		case 16:
			cout << "operator+=(element)" << endl;
			cout << "> element = ";
			cin >> element;
			array += element;
			break;


		// Work with array += other array.
		case 17:
			cout << "operator+=(array)" << endl;
			cout << "> other array size = ";
			cin >> number;
			temp = Array<unsigned>(number);
			for (unsigned i = 0; i < number; i++) {
				temp[i] = randUint(10, 99);
			}
			array += temp;
			break;

		}
	}

	return 0;
}
