#ifndef SORTING_H
#define SORTING_H

#include <chrono>
using namespace std::chrono;


// Simplify
typedef time_point<
	_V2::system_clock, duration<long int, std::ratio<1, 1000000000> >
> Time;

// The static class for various sorting algorithms.
template <class T>
class Sorting
{
public:

	// Variables.
	static bool sortAscending;

	// Functions.
	static void showTimeTaken(Time start, Time end);
	static void bubbleSort(T array[], const uint& SIZE);
	static void selectionSort(T array[], const uint& SIZE);
	static void insertionSort(T array[], const uint& SIZE);
	static void cocktailShakerSort(T array[], const uint& SIZE);
	static void quickSort(T array[], const uint& SIZE);
	static void quickSortV2(T array[], const uint& SIZE);
	static void shellSort(T array[], const uint& SIZE);
	static void mergeSort(T array[], const uint& SIZE);
	static void combSort(T array[], const uint& SIZE);
	static void radixSort(
		T array[], const uint& SIZE, const uint BASE = 10);
	static void heapSort(T array[], const uint& SIZE);

private:

	// Functions.
	static bool compare(T left, T right);
	static void quickSort(T array[], int low, int high);
	static int partition(T array[], int low, int high);
	static void quickSortV2(T array[], int low, int high);
	static int partitionV2(T array[], int low, int high);
	static void split(T array[], T copy[], uint start, uint end);
	static void merge(
		T array[], T copy[], uint start, uint middle, uint end);
	static void heapify(T array[], uint end, uint parentIndex);
};

#include "sorting.cpp"

#endif
