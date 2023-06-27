#include <iostream>
#include "display_structure.h"
#include "../random/random.h"
using namespace std;


// Main testing function.
int main() {

	// Create the array.
	uint SIZE = 63;
	uint array[SIZE] = {
		50,
		25, 75,
		15, 35, 65, 85,
		10, 20, 30, 40, 60, 70, 80, 90,
		8, 12, 18, 22, 28, 32, 38, 42, 58, 62, 68, 72, 78, 82, 88, 92,
		7, 9, 11, 13, 17, 19, 21, 23, 27, 29, 31, 33, 37, 39, 41, 43,
		57, 59, 61, 63, 67, 69, 71, 73, 77, 79, 81, 83, 87, 89, 91, 93
	};
	SIZE = 25;

	// Display the array.
	displayArray(array, SIZE);

	// Display as a heap.
	displayHeap(array, SIZE);

	return 0;
}
