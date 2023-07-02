#include <iostream>
#include "math.h"
using namespace std;


int main() {

	// Initialise the arrays.
	const uint SIZE = 5;
	uint uintArray[SIZE] = {18, 42, 66, 12, 92};
	char charArray[SIZE] = {'a', 'z', 'q', 'b', 'i'};

	// Print both arrays.
	cout << "uintArray:" << endl;
	for (uint i = 0; i < SIZE; i++) {
		cout << uintArray[i] << " ";
	}
	cout << "\ncharArray:" << endl;
	for (uint i = 0; i < SIZE; i++) {
		cout << "'" << charArray[i] << "' ";
	}
	cout << endl;

	// Print the minimum and maximum value.
	cout << "\nmin(uintArray) = " << min(uintArray, SIZE) << endl;
	cout << "max(uintArray) = " << max(uintArray, SIZE) << endl;
	cout << "min(charArray) = '" << min(charArray, SIZE) << "'\n";
	cout << "max(charArray) = '" << max(charArray, SIZE) << "'\n";

	uint a = 3, b = 5;
	cout << "\nmin("<<a<<", "<<b<<") = " << min(a, b) << endl;
	cout << "max("<<a<<", "<<b<<") = " << max(a, b) << endl;
	char x = 'A', y = 'F';
	cout << "min('"<<x<<"', '"<<y<<"') = '" << min(x, y) << "'\n";
	cout << "max('"<<x<<"', '"<<y<<"') = '" << max(x, y) << "'\n";

	// Log of custom base.
	cout << endl;
	uint base = 3;
	for (uint number = 1; number <= 10; number++) {
		cout << "log("<<base<<", "<<number<<") = ";
		cout << log(base, number) << endl;
	}

	return 0;
}
