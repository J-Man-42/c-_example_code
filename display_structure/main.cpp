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
		this->colour = '\0';
		this->left = nullptr;
		this->right = nullptr;
	}
	Node(const uint data, const char colour = '\0') {
		this->data = data;
		this->height = 1;
		this->colour = colour;
		this->left = nullptr;
		this->right = nullptr;
	}
	Node(Node* other) {
		this->data = other->data;
		this->height = other->height;
		this->colour = other->colour;
		this->left = nullptr;
		this->right = nullptr;
	}
	~Node() {
		this->left = nullptr;
		this->right = nullptr;
	}
	uint data;
	uint height;
	char colour;
	Node* left;
	Node* right;
};


// Recursively adjust the tree's height.
void adjustHeight(Node* node) {

	// Stopping condition.
	if (!node) {
		return;
	}

	// Traverse left and right child.
	adjustHeight(node->left);
	adjustHeight(node->right);

	// Update height of current node.
	uint left = (node->left ? node->left->height : 0);
	uint right = (node->right ? node->right->height : 0);
	node->height = 1 + max(left, right);
}


// Recursively delete the entire tree.
void deleteTree(Node* node) {

	// Stopping condition.
	if (!node) {
		return;
	}

	// Traverse left and right child.
	deleteTree(node->left);
	deleteTree(node->right);

	// Delete the current node.
	delete node;
}


// Main testing function.
int main() {

	// Create the array.
	uint SIZE = 31;
	uint array[SIZE] = {
		 1,
		 9,  2,
		13, 10,  5,  3,
		15, 14, 11, 21,  7,  6,  4, 17,
		16, 24, 28, 23, 12, 22, 27, 30, 8, 20, 26, 19, 31, 18, 25, 29
	};

	// Display the array.
	cout << "\nArray:" << endl;
	displayArray(array, SIZE);

	// Display as a heap.
	cout << "\nHeap:" << endl;
	displayHeap(array, SIZE);


	// Build the tree.
	Node* root = new Node(50, 'x');

	// Height 4.
	root->left = new Node(25);
	root->right = new Node(75);

	// Height 3.
	root->left->left = new Node(15, 'r');
	root->left->right = new Node(35);
	root->right->left = new Node(65);
	root->right->right = new Node(85);

	// Height 2.
	root->left->left->left = new Node(10);
	root->left->left->right = new Node(20);
	root->left->right->left = new Node(30);
	root->left->right->right = new Node(40, 'r');
	root->right->left->left = new Node(60);
	root->right->left->right = new Node(70);
	root->right->right->left = new Node(80, 'm');
	root->right->right->right = new Node(90);

	// Height 1.
	root->left->left->left->left = new Node(8);
	root->left->left->left->right = new Node(12, 'b');
	root->left->left->right->left = new Node(18);
	root->left->left->right->right = new Node(22);
	root->left->right->left->left = new Node(28);
	root->left->right->left->right = new Node(32);
	root->left->right->right->left = new Node(38);
	root->left->right->right->right = new Node(42);
	root->right->left->left->left = new Node(58, 'g');
	root->right->left->left->right = new Node(62);
	root->right->left->right->left = new Node(68, 'c');
	root->right->left->right->right = new Node(72, 'y');
	root->right->right->left->left = new Node(78);
	root->right->right->left->right = new Node(82);
	root->right->right->right->left = new Node(88);
	root->right->right->right->right = new Node(92);

	// Dynamically adjust tree heights.
	adjustHeight(root);

	// Display the tree.
	cout << "\nTree:" << endl;
	displayTree<Node>(root);

	// Delete dynamic memory.
	deleteTree(root);

	return 0;
}
