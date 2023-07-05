#include <iostream>
#include <cmath>
#include "math.h"
using namespace std;


// Find the minimum value in the array.
unsigned min(unsigned arr[], const unsigned SIZE) {

	// If array is empty, return 0.
	if (SIZE == 0) {
		return 0;
	}

	// Find and return the minimum value otherwise.
	unsigned minValue = arr[0];
	for (unsigned i = 1; i < SIZE; i++) {
		if (arr[i] < minValue) {
			minValue = arr[i];
		}
	}
	return minValue;
}
int min(int arr[], const unsigned SIZE) {

	// If array is empty, return 0.
	if (SIZE == 0) {
		return 0;
	}

	// Find and return the minimum value otherwise.
	int minValue = arr[0];
	for (unsigned i = 1; i < SIZE; i++) {
		if (arr[i] < minValue) {
			minValue = arr[i];
		}
	}
	return minValue;
}
double min(double arr[], const unsigned SIZE) {

	// If array is empty, return 0.
	if (SIZE == 0) {
		return 0;
	}

	// Find and return the minimum value otherwise.
	double minValue = arr[0];
	for (unsigned i = 1; i < SIZE; i++) {
		if (arr[i] < minValue) {
			minValue = arr[i];
		}
	}
	return minValue;
}
char min(char arr[], const unsigned SIZE) {

	// If array is empty, return 0.
	if (SIZE == 0) {
		return 0;
	}

	// Find and return the minimum value otherwise.
	char minValue = arr[0];
	for (unsigned i = 1; i < SIZE; i++) {
		if (arr[i] < minValue) {
			minValue = arr[i];
		}
	}
	return minValue;
}


// Find the minimum of the two values.
unsigned min(unsigned a, unsigned b) {
	return (a < b ? a : b);
}
int min(int a, int b) {
	return (a < b ? a : b);
}
double min(double a, double b) {
	return (a < b ? a : b);
}
char min(char a, char b) {
	return (a < b ? a : b);
}


// Find the minimum value in the array.
unsigned max(unsigned arr[], const unsigned SIZE) {

	// If array is empty, return 0.
	if (SIZE == 0) {
		return 0;
	}

	// Find and return the maximum value otherwise.
	unsigned maxValue = arr[0];
	for (unsigned i = 1; i < SIZE; i++) {
		if (arr[i] > maxValue) {
			maxValue = arr[i];
		}
	}
	return maxValue;
}
int max(int arr[], const unsigned SIZE) {

	// If array is empty, return 0.
	if (SIZE == 0) {
		return 0;
	}

	// Find and return the maximum value otherwise.
	int maxValue = arr[0];
	for (unsigned i = 1; i < SIZE; i++) {
		if (arr[i] > maxValue) {
			maxValue = arr[i];
		}
	}
	return maxValue;
}
double max(double arr[], const unsigned SIZE) {

	// If array is empty, return 0.
	if (SIZE == 0) {
		return 0;
	}

	// Find and return the maximum value otherwise.
	double maxValue = arr[0];
	for (unsigned i = 1; i < SIZE; i++) {
		if (arr[i] > maxValue) {
			maxValue = arr[i];
		}
	}
	return maxValue;
}
char max(char arr[], const unsigned SIZE) {

	// If array is empty, return 0.
	if (SIZE == 0) {
		return 0;
	}

	// Find and return the maximum value otherwise.
	char maxValue = arr[0];
	for (unsigned i = 1; i < SIZE; i++) {
		if (arr[i] > maxValue) {
			maxValue = arr[i];
		}
	}
	return maxValue;
}


// Find the maximum of the two values.
unsigned max(unsigned a, unsigned b) {
	return (a > b ? a : b);
}
int max(int a, int b) {
	return (a > b ? a : b);
}
double max(double a, double b) {
	return (a > b ? a : b);
}
char max(char a, char b) {
	return (a > b ? a : b);
}


// Log base n of x.
double log(double n, double x) {
	return log2(x) / log2(n);
}
