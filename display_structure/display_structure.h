#ifndef DISPLAY_STRUCTURE_H
#define DISPLAY_STRUCTURE_H

#include <iostream>
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
	cout << "height = " << height << endl;

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

	// The node and current depth variables.
	Node* nodePtr;
	uint d = 0;

	// Loop for all heights.
	topQueue->push(root);
	while (d < height) {
		nodePtr = topQueue->pop();

		// If node is not null, add its children to queue.
		if (nodePtr) {
			cout << nodePtr->data << "  ";
			bottomQueue->push(nodePtr->left);
			bottomQueue->push(nodePtr->right);
		}

		// Add null otherwise.
		else {
			cout << "##  ";
			bottomQueue->push(nullptr);
			bottomQueue->push(nullptr);
		}

		// When the top queue is empty, swap queues and increment depth.
		if (topQueue->isEmpty()) {
			swap(topQueue, bottomQueue);
			d++;
			cout << endl;
		}
	}

	// Delete the queues.
	delete topQueue;
	delete bottomQueue;
}

#endif