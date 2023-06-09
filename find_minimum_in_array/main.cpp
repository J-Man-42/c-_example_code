#include <iostream>
#include <limits.h>
using namespace std;


int main() {

	// Initialise the array of values.
	const int SIZE = 5;
	int array[SIZE] = {18, 42, 66, 12, 92};

	// Print array.
	cout << "array:" << endl;
	for (int i = 0; i < SIZE; i++) {
		cout << array[i] << " ";
	}
	cout << endl;

	// Assign minimum value as the first element.
	int minValue = array[0];
	
	// Iterate through all remaining entries.
	for (int i = 1; i < SIZE; i++) {
		if (array[i] < minValue) {
			minValue = array[i];
		}
	}

	// Print the minimum value.
	cout << "\nmin(array) = " << minValue << endl;

	return 0;
}