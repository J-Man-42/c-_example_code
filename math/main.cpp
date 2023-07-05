#include <iostream>
#include "math.h"
using namespace std;


int main() {

	// Initialise the arrays.
	const unsigned SIZE = 5;
	unsigned unsignedArray[SIZE] = {18, 42, 66, 12, 92};
	char charArray[SIZE] = {'a', 'z', 'q', 'b', 'i'};

	// Print both arrays.
	cout << "unsignedArray:" << endl;
	for (unsigned i = 0; i < SIZE; i++) {
		cout << unsignedArray[i] << " ";
	}
	cout << "\ncharArray:" << endl;
	for (unsigned i = 0; i < SIZE; i++) {
		cout << "'" << charArray[i] << "' ";
	}
	cout << endl;

	// Print the minimum and maximum value.
	cout << "\nmin(unsignedArray) = " << min(unsignedArray, SIZE) << endl;
	cout << "max(unsignedArray) = " << max(unsignedArray, SIZE) << endl;
	cout << "min(charArray) = '" << min(charArray, SIZE) << "'\n";
	cout << "max(charArray) = '" << max(charArray, SIZE) << "'\n";

	unsigned a = 3, b = 5;
	cout << "\nmin("<<a<<", "<<b<<") = " << min(a, b) << endl;
	cout << "max("<<a<<", "<<b<<") = " << max(a, b) << endl;
	char x = 'A', y = 'F';
	cout << "min('"<<x<<"', '"<<y<<"') = '" << min(x, y) << "'\n";
	cout << "max('"<<x<<"', '"<<y<<"') = '" << max(x, y) << "'\n";

	// Log of custom base.
	cout << endl;
	unsigned base = 3;
	for (unsigned number = 1; number <= 10; number++) {
		cout << "log("<<base<<", "<<number<<") = ";
		cout << log(base, number) << endl;
	}

	return 0;
}
