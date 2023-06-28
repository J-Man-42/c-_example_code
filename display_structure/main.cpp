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
	cout << "\nTree:" << endl;
	displayTree<Node>(root);

	return 0;
}
