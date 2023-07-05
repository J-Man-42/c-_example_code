#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "display_structure.h"
using namespace std;



// Elegantly displays the content of the array.
void displayArray(unsigned* array, const unsigned SIZE) {
	unsigned width;

	// Do not print array of size 0.
	if (SIZE == 0) {
		return;
	}

	// Configure the colour text.
	startColour('w');

	// Display the top border.
	cout << "┌─";
	for (unsigned i = 0; i < SIZE; i++) {
		width = 1;
		if (array[i] > 0) {
			width += log10(array[i]);
		}
		for (unsigned j = 0; j < width; j++) {
			cout << "─";
		}
		if (i < SIZE-1) {
			cout << "─┬─";
		} else {
			cout << "─┐\n";
		}
	}

	// Iterate through all elements.
	for (unsigned i = 0; i < SIZE; i++) {
		cout << "│ " << array[i] << " ";
	}
	cout << "│\n";

	// Display the bottom border.
	cout << "└─";
	for (unsigned i = 0; i < SIZE; i++) {
		width = 1;
		if (array[i] > 0) {
			width += log10(array[i]);
		}
		for (unsigned j = 0; j < width; j++) {
			cout << "─";
		}
		if (i < SIZE-1) {
			cout << "─┴─";
		} else {
			cout << "─┘\n";
		}
	}

	// Reset colour.
	endColour();
}



// Elegantly displays the array as a heap.
void displayHeap(unsigned* array, const unsigned SIZE) {

	// Simply return if no elements in the array.
	if (SIZE == 0)
		return;

	// Configure the colour text.
	startColour('w');

	// Calculate height of heap.
	unsigned height = 1 + log2(SIZE);

	// Calculate the widths.
	unsigned width[height];
	width[height-1] = 0;
	unsigned x = 3;
	for (int n = height-2; n >= 0; n--) {
		width[n] = width[n+1] + x;
		x *= 2;
	}

	// The number of nodes for the current depth.
	unsigned count = 1;

	// The starting point and limit for the number of children.
	unsigned start, limit;

	// The left and right child indices.
	unsigned left, right;

	// Print heap.
	unsigned index = 0;
	for (unsigned i = 0; i < height; i++) {
		limit = min(SIZE, index*2 + 1);
		start = index;

		// Calculate left and right indices.
		left = 2*start + 1;
		right = 2*start + 2;

		// Print top borders.
		for (unsigned j = start; j < limit; j++) {
			cout << setw(width[i]) << "";
			cout << "┌─" << (i > 0 ? "┴" : "─") << "─┐";
			cout << setw(width[i]+1) << "";
		}
		cout << endl;

		// Print array content.
		for (unsigned j = start; j < limit; j++) {
			cout << setw(width[i]) << "" << "│";
			cout << setfill('0') << setw(3) << array[index] << "│";
			cout << setfill(' ') << setw(width[i]+1) << "";
			index++;
		}
		cout << endl;

		// Print bottom borders.
		for (unsigned j = start, l = left, r = right; j < limit; j++) {

			// See if children must be attached.
			cout << setw(width[i]) << "" << "└";
			cout << (l < SIZE ? "┬" : "─") << "─";
			cout << (r < SIZE ? "┬" : "─") << "┘";
			cout << setw(width[i]+1) << "";

			// Update current left and right indices.
			l = r + 1;
			r = l + 1;
		}
		cout << endl;

		// Print connections.
		if (i < height-1) {
			for (unsigned j = start, l = left, r = right; j < limit; j++) {

				// Left branch.
				if (l >= SIZE) {
					break;
				}
				cout << setw(width[i+1]+2) << "" << "┌";
				for (unsigned k = 0; k <= width[i+1]; k++) {
					cout << "─";
				}
				cout << "┘";

				// Right branch.
				if (r >= SIZE) {
					break;
				}
				cout << " └";
				for (unsigned k = 0; k <= width[i+1]; k++) {
					cout << "─";
				}
				cout << "┐" << setw(width[i+1]+3) << "";

				// Update current left and right indices.
				l = r + 1;
				r = l + 1;
			}
			cout << endl;
		}

		// Update count.
		count *= 2;
	}

	// Reset colour.
	endColour();
}
