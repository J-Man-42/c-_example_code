#include <iostream>
#include "math.h"
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

	uint a = 3, b = 5;
	cout << "\nmin("<<a<<", "<<b<<") = " << min(a, b) << endl;
	cout << "max("<<a<<", "<<b<<") = " << max(a, b) << endl;

	// Log of custom base.
	cout << endl;
	uint base = 3;
	for (uint number = 1; number <= 10; number++) {
		cout << "log("<<base<<", "<<number<<") = ";
		cout << log(base, number) << endl;
	}

	return 0;
}
