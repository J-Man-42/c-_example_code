#include <iostream>
#include "display_structure.h"
#include "../random/random.h"
using namespace std;


// The example node class for trees.
class Node
{
public:
	Node() {
		this->data = 0;
		this->height = 0;
		this->left = nullptr;
		this->right = nullptr;
	}
	Node(const int data, const uint height = 1) {
		this->data = data;
		this->height = height;
		this->left = nullptr;
		this->right = nullptr;
	}
	Node(Node* other) {
		this->data = other->data;
		this->height = other->height;
		this->left = nullptr;
		this->right = nullptr;
	}
	~Node() {
		this->left = nullptr;
		this->right = nullptr;
	}
	int data;
	uint height;
	Node* left;
	Node* right;
};


// Main testing function.
int main() {

	// Create the array.
	uint SIZE = 63;
	uint array[SIZE] = {
		50,
		25, 75,
		15, 35, 65, 85,
		10, 20, 30, 40, 60, 70, 80, 90,
		8, 12, 18, 22, 28, 32, 38, 42, 58, 62, 68, 72, 78, 82, 88, 92,
		7, 9, 11, 13, 17, 19, 21, 23, 27, 29, 31, 33, 37, 39, 41, 43,
		57, 59, 61, 63, 67, 69, 71, 73, 77, 79, 81, 83, 87, 89, 91, 93
	};
	SIZE = 25;

	// Display the array.
	displayArray(array, SIZE);

	// Display as a heap.
	displayHeap(array, SIZE);

	// Build the tree.
	Node* root = new Node(50, 4);
	root->left = new Node(25, 3);
	root->right = new Node(75, 3);
	root->left->left = new Node(15, 2);
	root->left->right = new Node(35, 2);
	root->right->left = new Node(65, 2);
	root->right->right = new Node(85, 2);
	root->left->left->left = new Node(10);
	root->left->left->right = new Node(20);
	root->left->right->left = new Node(30);
	root->left->right->right = new Node(40);
	root->right->left->left = new Node(60);
	root->right->left->right = new Node(70);
	root->right->right->left = new Node(80);
	root->right->right->right = new Node(90);

	// Display the tree.
	displayTree<Node>(root);

	return 0;
}
