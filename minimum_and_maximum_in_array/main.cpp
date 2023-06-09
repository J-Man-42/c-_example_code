#include <iostream>
#include "min_max.h"
using namespace std;


int main() {

	// Initialise the array of values.
	const uint SIZE = 5;
	uint array[SIZE] = {18, 42, 66, 12, 92};

	// Print array.
	cout << "array:" << endl;
	for (uint i = 0; i < SIZE; i++) {
		cout << array[i] << " ";
	}
	cout << endl;

	// Print the minimum and maximum value.
	cout << "\nmin(array) = " << min(array, SIZE) << endl;
	cout << "max(array) = " << max(array, SIZE) << endl;

	return 0;
}
