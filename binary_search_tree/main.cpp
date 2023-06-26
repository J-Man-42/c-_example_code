#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>
#include "binary_search_tree.h"
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

	// Create the binary search tree.
	BinarySearchTree<int> tree;
	BinarySearchTree<int> temp;

	// Loop until Q has been entered.
	while (answer[0] != 'Q') {

		// Clear the screen
		clearScreen();

		// Traverse the tree using both Depth First and Breadth First.
		cout << "Tree DFT:";
		tree.dft();
		cout << "Tree BFT:";
		tree.bft();

		// Print majority of available functions.
		cout << "\n==============================" << endl;
		cout << " (1)  insert(element)" << endl;
		cout << " (Q)  << QUIT PROGRAM >>" << endl;
		cout << "==============================" << endl;
		cout << "> ";
		cin.getline(answer, 3);
		answer[0] = toupper(answer[0]);


		// Any other character continues the loop.
		if (isalpha(answer[0])) {
			continue;
		}


		// Switch statement for answer.
		number = atoi(answer);
		switch (number) {


		// Insert an element in the tree.
		case 1:
			cout << "insert(element)" << endl;
			cout << "> element = ";
			cin >> element;
			tree.insert(element);
			break;
		}
	}

	return 0;
}
