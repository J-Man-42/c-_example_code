#ifndef SORTING_H
#define SORTING_H

#include "../lists/linked_list.h"


// The class for housing a highlight colour, value, and index.
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
	static bool sortAscending;

	// Functions.
	static void restoreDefault();
	static void toggleBarWidth();
	static uint getBarWidth();
	static void setBarHeight(uint height);
	static void setVerticalScale(uint scale);
	static uint getVerticalScale();
	static void setDelay(uint ms);
	static uint getDelay();
	static void displayArray(
		uint array[], const uint SIZE,
		LinkedList<Highlight>* highlight = nullptr,
		uint horizontalBar = 0
	);
	static void bubbleSort(uint array[], const uint SIZE);
	static void selectionSort(uint array[], const uint SIZE);
	static void insertionSort(uint array[], const uint SIZE);
	static void cocktailShakerSort(uint array[], const uint SIZE);
	static void quickSort(uint array[], const uint SIZE);
	static void quickSortV2(uint array[], const uint SIZE);
	static void shellSort(uint array[], const uint SIZE);
	static void mergeSort(uint array[], const uint SIZE);
	static void combSort(uint array[], const uint SIZE);
	static void radixSort(uint array[], const uint SIZE);

private:

	// Variables.
	static std::chrono::duration<int, std::milli> delay;
	static uint barHeight;
	static uint barWidth;
	static uint verticalScale;
	static uint displayHeight;
	static string singleBars[];
	static string doubleBars[];
	static string* bars;

	// Functions.
	static void calibrateHeightAndScale();
	static uint scaleVertically(uint value);
	static void printBorder(string symbol, const uint SIZE);
	static bool compare(uint left, uint right);
	static void quickSort(
		uint array[], const int SIZE, int low, int high);
	static int partition(
		uint array[], const int SIZE, int low, int high,
		LinkedList<Highlight>* highlight);
	static void quickSortV2(
		uint array[], const int SIZE, int low, int high);
	static int partitionV2(
		uint array[], const int SIZE, int low, int high,
		LinkedList<Highlight>* highlight);
	static void split(
		uint array[], uint copy[], const uint& SIZE,
		uint start, uint end);
	static void merge(
		uint array[], uint copy[], const uint& SIZE,
		uint start, uint middle, uint end,
		LinkedList<Highlight>* highlight);
};


#endif
