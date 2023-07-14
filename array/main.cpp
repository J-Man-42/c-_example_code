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

	// Create the array.
	Array<unsigned> array(10);
	Array<unsigned> temp(10);
	
	// Loop until Q has been entered.
	while (answer[0] != 'Q') {

		// Clear the screen
		clearScreen();

		// Print the array.
		cout << "Array:  ";
		cout << array << endl;

		// Print majority of available functions.
		cout << "\n==============================" << endl;
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
		case 1:
			break;
		}
	}

	return 0;
}
