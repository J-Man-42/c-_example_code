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
	unsigned number;
	unsigned element;
	int index;

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
		cout << " (1)  clone()" << endl;
		cout << " (2)  operator=" << endl;
		cout << " (3)  operator[]" << endl;
		cout << " (4)  operator+(element)" << endl;
		cout << " (5)  operator+(array)" << endl;
		cout << " (6)  operator+=(element)" << endl;
		cout << " (7)  operator+=(array)" << endl;
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


		// Clone the array.
		case 1:
			cout << "clone()" << endl;
			temp = array.clone();
			cout << "> cloned array:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;


		// Work with the assignment operator.
		case 2:
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
		case 3:
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
		case 4:
			cout << "operator+(element)" << endl;
			cout << "> element = ";
			cin >> element;
			temp = array + element;
			cout << "> new array:  " << temp.toString() << endl;
			sleep_for(seconds(5));
			break;


		// Work with array + other array.
		case 5:
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
		case 6:
			cout << "operator+=(element)" << endl;
			cout << "> element = ";
			cin >> element;
			array += element;
			break;


		// Work with array += other array.
		case 7:
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
