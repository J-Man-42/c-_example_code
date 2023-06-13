#ifndef SORTING_H
#define SORTING_H


// The static class for various sorting algorithms.
class Sorting
{
public:
	static void displayArray(
		uint array[], const uint SIZE, bool thinBar = false,
		uint* highlight = nullptr, char* colour = nullptr,
		const uint COUNT = 0
	);
	static void bubbleSort(
		uint array[], const uint SIZE, uint ms = 500, bool thinBar = false);
	static void selectionSort(
		uint array[], const uint SIZE, uint ms = 500, bool thinBar = false);
	static void insertionSort(
		uint array[], const uint SIZE, uint ms = 500, bool thinBar = false);
	static void cocktailShakerSort(
		uint array[], const uint SIZE, uint ms = 500, bool thinBar = false);
};


#endif