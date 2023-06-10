#ifndef SORTING_H
#define SORTING_H

// All function prototypes.
uint randint(uint minvalue, uint maxValue);
void displayArray(
	uint array[], const uint SIZE, bool thinBar = false,
	uint* highlight = nullptr, char* colour = nullptr,
	const uint COUNT = 0
);
void bubbleSort(
	uint array[], const uint SIZE, uint ms = 500, bool thinBar = false);
void selectionSort(
	uint array[], const uint SIZE, uint ms = 500, bool thinBar = false);

#endif