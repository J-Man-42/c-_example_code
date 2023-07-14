#ifndef SORTING_H
#define SORTING_H

#include <chrono>
using namespace std::chrono;


// Simplify
typedef std::chrono::_V2::system_clock::time_point Time;

// The static class for various sorting algorithms.
template<class T>
class Sorting
{
public:

	// Variables.
	static bool sortAscending;

	// Functions.
	static void showTimeTaken(Time start, Time end);
	static void bubbleSort(T array[], const unsigned& SIZE);
	static void selectionSort(T array[], const unsigned& SIZE);
	static void insertionSort(T array[], const unsigned& SIZE);
	static void cocktailShakerSort(T array[], const unsigned& SIZE);
	static void gnomeSort(T array[], const unsigned& SIZE);
	static void quickSort(T array[], const unsigned& SIZE);
	static void quickSortV2(T array[], const unsigned& SIZE);
	static void shellSort(T array[], const unsigned& SIZE);
	static void mergeSort(T array[], const unsigned& SIZE);
	static void combSort(T array[], const unsigned& SIZE);
	static void radixSort(T array[], const unsigned& SIZE, unsigned base = 10);
	static void heapSort(T array[], const unsigned& SIZE);
	static void bucketSort(T array[], const unsigned& SIZE);
	static void bitonicSort(T array[], const unsigned& SIZE);

private:

	// Functions.
	static bool compare(T left, T right);
	static void quickSort(T array[], int low, int high);
	static int partition(T array[], int low, int high);
	static void quickSortV2(T array[], int low, int high);
	static int partitionV2(T array[], int low, int high);
	static void split(T array[], T copy[], unsigned start, unsigned end);
	static void merge(
		T array[], T copy[], unsigned start, unsigned middle, unsigned end);
	static unsigned updateBase(unsigned array[], unsigned base);
	static unsigned updateBase(char array[], unsigned base);
	static unsigned radixDigits(
		unsigned array[], const unsigned& SIZE, const unsigned& BASE);
	static unsigned radixDigits(
		char array[], const unsigned& SIZE, const unsigned& BASE);
	static unsigned radixHash(unsigned& value, unsigned digit, const unsigned& BASE);
	static unsigned radixHash(char& value, unsigned digit, const unsigned& BASE);
	static void heapify(T array[], unsigned end, unsigned parentIndex);
	static void bitonicSort(
		T array[], unsigned low, unsigned high, bool ascending);
	static void bitonicMerge(
		T array[], unsigned low, unsigned high, bool ascending);
};

#include "sorting.cpp"

#endif
