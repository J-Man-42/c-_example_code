#include <iostream>
#include <iomanip>
#include <cmath>
#include "display_structure.h"
using namespace std;



// Elegantly displays the content of the array.
void displayArray(uint* array, const uint SIZE) {
	uint width;

	// Do not print array of size 0.
	if (SIZE == 0) {
		return;
	}

	// Display the top border.
	cout << "┌─";
	for (size_t i = 0; i < SIZE; i++) {
		width = 1;
		if (array[i] > 0) {
			width += log10(array[i]);
		}
		for (size_t j = 0; j < width; j++) {
			cout << "─";
		}
		if (i < SIZE-1) {
			cout << "─┬─";
		} else {
			cout << "─┐\n";
		}
	}

	// Iterate through all elements.
	for (size_t i = 0; i < SIZE; i++) {
		cout << "│ " << array[i] << " ";
	}
	cout << "│\n";

	// Display the bottom border.
	cout << "└─";
	for (size_t i = 0; i < SIZE; i++) {
		width = 1;
		if (array[i] > 0) {
			width += log10(array[i]);
		}
		for (size_t j = 0; j < width; j++) {
			cout << "─";
		}
		if (i < SIZE-1) {
			cout << "─┴─";
		} else {
			cout << "─┘\n";
		}
	}
}



// Elegantly displays the array as a heap.
void displayHeap(uint* array, const uint SIZE) {
	uint height = 1 + log2(SIZE);

	// Calculate the widths.
	uint width[height];
	width[height-1] = 0;
	uint x = 3;
	for (int n = height-2; n >= 0; n--) {
		width[n] = width[n+1] + x;
		x *= 2;
	}

	// The number of nodes for the current depth.
	uint count = 1;

	// Print heap.
	uint index = 0;
	for (uint i = 0; i < height; i++) {

		// Print top borders.
		for (uint j = 0; j < count; j++) {
			cout << setw(width[i]) << "";
			cout << "┌─" << (i > 0 ? "┴" : "─") << "─┐";
			cout << setw(width[i]+1) << "";
		}
		cout << endl;

		// Print array content.
		for (uint j = 0; j < count; j++) {
			cout << setw(width[i]) << "" << "│";
			cout << setfill('0') << setw(3) << array[index] << "│";
			cout << setfill(' ') << setw(width[i]+1) << "";
			index++;
		}
		cout << endl;

		// Print bottom borders.
		for (uint j = 0; j < count; j++) {
			cout << setw(width[i]) << "";
			cout << "└" << (i < height-1 ? "┬─┬" : "───") << "┘";
			cout << setw(width[i]+1) << "";
		}
		cout << endl;

		// Print connections.
		if (i < height-1) {
			for (uint j = 0; j < count; j++) {
				cout << setw(width[i+1]+2) << "" << "┌";
				for (uint k = 0; k <= width[i+1]; k++) {
					cout << "─";
				}
				cout << "┘ └";
				for (uint k = 0; k <= width[i+1]; k++) {
					cout << "─";
				}
				cout << "┐" << setw(width[i+1]+3) << "";
			}
			cout << endl;
		}

		// Update count.
		count *= 2;
	}
}