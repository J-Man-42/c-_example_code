#include <iostream>
#include "min_max.h"
using namespace std;


// Find the minimum value in the array.
uint min(uint arr[], const uint SIZE) {

	// If array is empty, return 0.
	if (SIZE == 0) {
		return 0;
	}

	// Find and return the minimum value otherwise.
	uint minValue = arr[0];
	for (uint i = 1; i < SIZE; i++) {
		if (arr[i] < minValue) {
			minValue = arr[i];
		}
	}
	return minValue;
}


// Find the minimum value in the array.
uint max(uint arr[], const uint SIZE) {

	// If array is empty, return 0.
	if (SIZE == 0) {
		return 0;
	}

	// Find and return the maximum value otherwise.
	uint maxValue = arr[0];
	for (uint i = 1; i < SIZE; i++) {
		if (arr[i] > maxValue) {
			maxValue = arr[i];
		}
	}
	return maxValue;
}