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

		// Print the tree height.
		cout << "Tree height:  " << tree.height() << endl;

		// Traverse the tree.
		cout << "Tree DFT:";
		tree.dft();
		cout << "Tree BFT:";
		tree.bft();

		// Print majority of available functions.
		cout << "\n==============================" << endl;
		cout << " (1)  clear()" << endl;
		cout << " (2)  clone()" << endl;
		cout << " (3)  contains(element)" << endl;
		cout << " (4)  insert(element)" << endl;
		cout << " (5)  isEmpty()" << endl;
		cout << " (6)  remove(element)" << endl;
		cout << " (7)  operator=" << endl;
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


		// Clear all elements in the tree.
		case 1:
			cout << "clear()" << endl;
			tree.clear();
			break;


		// Clone the tree.
		case 2:
			cout << "clone()" << endl;
			temp = tree.clone();
			cout << "> cloned tree DFT:";
			temp.dft();
			cout << "> cloned tree BFT:";
			temp.bft();
			sleep_for(seconds(5));
			break;


		// Test if element in the tree.
		case 3:
			cout << "contains(element)" << endl;
			cout << "> element = ";
			cin >> element;
			cout << "> Tree contains " << element << ":  ";
			if (tree.contains(element)) {
				cout << "true" << endl;
			} else {
				cout << "false" << endl;
			}
			sleep_for(seconds(2));
			break;


		// Insert an element in the tree.
		case 4:
			cout << "insert(element)" << endl;
			cout << "> element = ";
			cin >> element;
			tree.insert(element);
			break;


		// Check if empty.
		case 5:
			cout << "isEmpty()" << endl;
			cout << "> Tree is empty:  ";
			if (tree.isEmpty()) {
				cout << "true" << endl;
			} else {
				cout << "false" << endl;
			}
			sleep_for(seconds(2));
			break;


		// Remove an element from the tree.
		case 6:
			cout << "remove(element)" << endl;
			cout << "> element = ";
			cin >> element;
			try {
				tree.remove(element);
			} catch (string e) {
				cout << e << endl;
				sleep_for(seconds(2));
			}
			break;


		// Work with the assignment operator.
		case 7:
			cout << "operator=" << endl;
			cout << "> number of elements = ";
			cin >> number;
			temp.clear();
			for (size_t i = 0; i < number; i++) {
				temp.insert(randUint(10, 99));
			}
			tree = temp;
			break;
		}
	}

	return 0;
}
