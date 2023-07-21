#ifndef SORTING_H
#define SORTING_H

#include <thread>
#include <ctime>
#include "../linked_list/linked_list.h"
using namespace std::this_thread;	// sleep_for, sleep_until
using namespace std::chrono;		// nanoseconds, system_clock, seconds.


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

// Simplify multiple types.
typedef LinkedList<Highlight> Highlights;
typedef std::chrono::duration<int, std::milli> Duration;


// The static class for various sorting algorithms.
class Sorting
{
public:

	// Variables.
	static bool sortAscending;

	// Functions.
	static void restoreDefault();
	static void toggleWideBar();
	static void setBarWidth(unsigned maxValue);
	static void setBarHeight(unsigned height);
	static void setVerticalScale(unsigned scale);
	static void setDelay(unsigned ms);
	static unsigned getBarWidth();
	static unsigned getVerticalScale();
	static unsigned getDelay();
	static void displayArray(
		unsigned array[], const unsigned& SIZE,
		Highlights* highlight = nullptr,
		unsigned horizontalBar = 0);
	static void bubbleSort(unsigned array[], const unsigned& SIZE);
	static void selectionSort(unsigned array[], const unsigned& SIZE);
	static void insertionSort(unsigned array[], const unsigned& SIZE);
	static void cocktailShakerSort(unsigned array[], const unsigned& SIZE);
	static void gnomeSort(unsigned array[], const unsigned& SIZE);
	static void quickSort(unsigned array[], const unsigned& SIZE);
	static void quickSortV2(unsigned array[], const unsigned& SIZE);
	static void shellSort(unsigned array[], const unsigned& SIZE);
	static void mergeSort(unsigned array[], const unsigned& SIZE);
	static void combSort(unsigned array[], const unsigned& SIZE);
	static void radixSort(
		unsigned array[], const unsigned& SIZE, const unsigned BASE = 10);
	static void heapSort(unsigned array[], const unsigned& SIZE);
	static void bucketSort(unsigned array[], const unsigned& SIZE);
	static void bitonicSort(unsigned array[], const unsigned& SIZE);

private:

	// Variables.
	static bool isSorting;
	static bool interrupted;
	static Duration delay;
	static unsigned barHeight;
	static unsigned barWidth;
	static unsigned wideBarWidth;
	static unsigned verticalScale;
	static unsigned displayHeight;
	static string bars[];

	// Functions.
	static void generateBars();
	static void calibrateHeightAndScale();
	static unsigned scaleVertically(unsigned value);
	static void printBorder(string symbol, const unsigned& SIZE);
	static bool compare(unsigned left, unsigned right);
	static void handleCtrlC(int signum);
	static bool wasInterrupted(Highlights* highlight);
	static bool quickSort(
		unsigned array[], const int& SIZE, int low, int high);
	static int partition(
		unsigned array[], const int& SIZE, int low, int high,
		Highlights* highlight);
	static bool quickSortV2(
		unsigned array[], const int& SIZE, int low, int high);
	static int partitionV2(
		unsigned array[], const int& SIZE, int low, int high,
		Highlights* highlight);
	static void split(
		unsigned array[], unsigned copy[], const unsigned& SIZE,
		unsigned start, unsigned end);
	static void merge(
		unsigned array[], unsigned copy[], const unsigned& SIZE,
		unsigned start, unsigned middle, unsigned end,
		Highlights* highlight);
	static void heapify(
		unsigned array[], const unsigned& SIZE, unsigned end,
		unsigned parentIndex, Highlights* highlight);
	static void bitonicSort(
		unsigned array[], const unsigned& SIZE, unsigned low,
		unsigned high, bool ascending);
	static void bitonicMerge(
		unsigned array[], const unsigned& SIZE, unsigned low,
		unsigned high, bool ascending);
};


#endif
