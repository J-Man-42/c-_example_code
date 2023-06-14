#ifndef SORTING_H
#define SORTING_H


#include "../lists/linked_list.h"


// The class for housing a highlight colour and index.
class Highlight
{
public:
	Highlight() {
		this->colour = '\0';
		this->index = -1;
	}
	Highlight(char colour, int index = -1) {
		this->colour = colour;
		this->index = index;
	}
	Highlight(const Highlight& other) {
		this->colour = other.colour;
		this->index = other.index;
	}
	char colour;
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
		LinkedList<Highlight>* highlight = nullptr
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
	static void quickSort(uint array[], int low, int high);
	static int partition(uint array[], int low, int high);
};


#endif