#include <iostream>
#include "display_structure.h"
#include "../random/random.h"
using namespace std;


// Main testing function.
int main() {

	// Create random array.
	const uint SIZE = 10;
	uint* array = randUintArray(SIZE, 1, 999);

	// Display the array.
	displayArray(array, SIZE);

	// Delete dynamic memory.
	delete [] array;
	return 0;
}
