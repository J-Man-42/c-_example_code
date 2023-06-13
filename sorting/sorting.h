#ifndef SORTING_H
#define SORTING_H


// The static class for various sorting algorithms.
class Sorting
{
public:
	static uint delay;

	static void toggleBarWidth();
	static void displayArray(
		uint array[], const uint SIZE,
		uint* highlight = nullptr, char* colour = nullptr,
		const uint COUNT = 0
	);
	static void bubbleSort(uint array[], const uint SIZE);
	static void selectionSort(uint array[], const uint SIZE);
	static void insertionSort(uint array[], const uint SIZE);
	static void cocktailShakerSort(uint array[], const uint SIZE);

private:
	static uint barWidth;
};


#endif