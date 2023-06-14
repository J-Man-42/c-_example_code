#ifndef SORTING_H
#define SORTING_H

#define MAX_UINT 4294967295

#include "../lists/linked_list.h"


// The class for housing a highlight colour, value, and index.
class Highlight
{
public:
	Highlight() {
		this->colour = '\0';
		this->value = MAX_UINT;
		this->index = -1;
	}
	Highlight(char colour, int index = -1, uint value = MAX_UINT) {
		this->colour = colour;
		this->value = value;
		this->index = index;
	}
	Highlight(const Highlight& other) {
		this->colour = other.colour;
		this->value = other.value;
		this->index = other.index;
	}
	char colour;
	uint value;
	int index;
};


// The static class for various sorting algorithms.
class Sorting
{
public:

	// Variables.
	static uint delay;
	static bool sortAscending;

	// Functions.
	static void toggleBarWidth();
	static void setBarHeight(uint height);
	static uint getBarWidth();
	static void displayArray(
		uint array[], const uint SIZE,
		LinkedList<Highlight>* highlight = nullptr,
		Highlight* horizontalBar = nullptr
	);
	static void bubbleSort(uint array[], const uint SIZE);
	static void selectionSort(uint array[], const uint SIZE);
	static void insertionSort(uint array[], const uint SIZE);
	static void cocktailShakerSort(uint array[], const uint SIZE);
	static void quickSort(uint array[], const uint SIZE);

private:

	// Variables.
	static uint height;
	static uint barWidth;
	static string singleBars[];
	static string doubleBars[];
	static string* bars;

	// Functions.
	static void printBorder(string symbol, const uint SIZE);
	static bool mustSwap(uint left, uint right);
	static void quickSort(
		uint array[], const int SIZE, int low, int high);
	static int partition(
		uint array[], const int SIZE, int low, int high,
		LinkedList<Highlight>* highlight);
};


#endif
