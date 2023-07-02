#ifndef DISPLAY_STRUCTURE_H
#define DISPLAY_STRUCTURE_H

#include <iostream>
#include <iomanip>
#include "../queue/queue.h"
using namespace std;

// Function prototypes.
void displayArray(uint* array, const uint SIZE);
void displayHeap(uint* array, const uint SIZE);


// Elegantly displays the tree structure.
template<class Node>
void displayTree(Node* root) {

	// Simply return if no elements in the tree.
	if (!root) {
		return;
	}

	// Get the height from root.
	uint height = root->height;

	// Calculate the widths.
	uint width[height];
	width[height-1] = 0;
	uint x = 3;
	for (int n = height-2; n >= 0; n--) {
		width[n] = width[n+1] + x;
		x *= 2;
	}

	// The two queues.
	Queue<Node*>* topQueue = new Queue<Node*>();
	Queue<Node*>* bottomQueue = new Queue<Node*>();

	// The display queues.
	Queue<Node*>* topDisplayQueue = new Queue<Node*>();
	Queue<Node*>* bottomDisplayQueue = new Queue<Node*>();

	// The node and current depth variables.
	Node* nodePtr;
	uint d = 0;

	// Loop for all heights.
	topQueue->push(root);
	while (d < height) {
		nodePtr = topQueue->pop();
		topDisplayQueue->push(nodePtr);

		// If node is not null, add its children to queue.
		if (nodePtr) {
			bottomQueue->push(nodePtr->left);
			bottomQueue->push(nodePtr->right);
		}

		// Add null otherwise.
		else {
			bottomQueue->push(nullptr);
			bottomQueue->push(nullptr);
		}

		// When the top queue is empty, display the row.
		if (topQueue->isEmpty()) {

			// Print top border.
			while (!topDisplayQueue->isEmpty()) {
				nodePtr = topDisplayQueue->pop();
				bottomDisplayQueue->push(nodePtr);
				cout << setw(width[d]) << "";
				if (nodePtr) {
					cout << "┌─" << (d > 0 ? "┴" : "─") << "─┐";
				} else {
					cout << setw(5) << "";
				}
				cout << setw(width[d]+1) << "";
			}
			cout << endl;

			// Print row of elements.
			while (!bottomDisplayQueue->isEmpty()) {
				nodePtr = bottomDisplayQueue->pop();
				topDisplayQueue->push(nodePtr);
				cout << setw(width[d]) << "";
				if (nodePtr) {
					cout << "│" << setfill('0') << setw(3);
					cout << nodePtr->data << "│";
				} else {
					cout << setw(5) << "";
				}
				cout << setfill(' ') << setw(width[d]+1) << "";
			}
			cout << endl;

			// Print bottom borders.
			while (!topDisplayQueue->isEmpty()) {
				nodePtr = topDisplayQueue->pop();
				bottomDisplayQueue->push(nodePtr);
				cout << setw(width[d]) << "";
				if (nodePtr) {
					cout << "└" << (nodePtr->left ? "┬" : "─") << "─";
					cout << (nodePtr->right ? "┬" : "─") << "┘";
				} else {
					cout << setw(5) << "";
				}
				cout << setw(width[d]+1) << "";
			}
			cout << endl;

			// Clear display queue if last row.
			if (d >= height-1) {
				bottomDisplayQueue->clear();
			}

			// Print connections otherwise.
			else {
				while (!bottomDisplayQueue->isEmpty()) {
					nodePtr = bottomDisplayQueue->pop();

					// Left branch.
					cout << setw(width[d+1]+2) << "";
					if (nodePtr && nodePtr->left) {
						cout << "┌";
						for (uint k = 0; k <= width[d+1]; k++) {
							cout << "─";
						}
						cout << "┘";
					} else {
						cout << setw(width[d+1]+3) << "";
					}

					// Right branch.
					if (nodePtr && nodePtr->right) {
						cout << " └";
						for (uint k = 0; k <= width[d+1]; k++) {
							cout << "─";
						}
						cout << "┐" << setw(width[d+1]+3) << "";
					} else {
						cout << setw(width[d]+4) << "";
					}
				}
				cout << endl;
			}

			// Swap queues and increment depth.
			swap(topQueue, bottomQueue);
			d++;
		}
	}

	// Delete all the queues.
	delete topQueue;
	delete bottomQueue;
	delete topDisplayQueue;
	delete bottomDisplayQueue;
}

#endif
