#include <iostream>
#include <cstdlib>
#include <ctime>
#include "sorting.h"
using namespace std;


// Generates a new random array with elements from 1 to 40.
uint* generateRandomArray(const uint SIZE) {
	uint* array = new uint[SIZE];
	for (size_t i = 0; i < SIZE; i++) {
		array[i] = randint(1, 40);
	}
	return array;
}


int main() {
	
	// Initialise array.
	uint size = 30;
	uint* array = generateRandomArray(size);

	// Test Bubble sort.
	bubbleSort(array, size);

	// Delete the array.
	delete [] array;

	return 0;
}