#include <iostream>
#include <cstdlib>
#include <ctime>
#include "sorting.h"
using namespace std;


int main() {
	
	// Initialise array.
	const uint SIZE = 30;
	uint arr[SIZE];
	for (uint i = 0; i < SIZE; i++) {
		arr[i] = randint(1, 40);
	}

	// Display the array.
	displayArray(arr, SIZE);

	// Display array with highlighting.
	uint highlight[3] = {3, 6, 9};
	displayArray(arr, SIZE, highlight, 3);

	return 0;
}