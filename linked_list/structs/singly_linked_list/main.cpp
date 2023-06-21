#include <iostream>
using namespace std;


// The node struct for linked lists.
struct Node
{
	int data;
	Node* next;
};


// Linked List with only head.
struct LinkedListV1
{
	Node* head;
};


// Linked List with both head and tail.
struct LinkedListV2
{
	Node* head;
	Node* tail;
};


// Function prototypes.

// Linked List with only head.
void append(LinkedListV1& list, int element);
void insert(LinkedListV1& list, int element);
void print(LinkedListV1& list);
void search(LinkedListV1& list, int element);
void remove(LinkedListV1& list, int element);

// Linked List with both head and tail.
void append(LinkedListV2& list, int element);
void insert(LinkedListV2& list, int element);
void print(LinkedListV2& list);
void search(LinkedListV2& list, int element);
void remove(LinkedListV2& list, int element);



// Append element to the end of the list.
void append(LinkedListV1& list, int element) {
	if (!list.head) {
		list.head = new Node{element, nullptr};
	} else {
		Node* nodePtr = list.head;
		while (nodePtr->next) {
			nodePtr = nodePtr->next;
		}
		nodePtr->next = new Node{element, nullptr};
	}
}

void append(LinkedListV2& list, int element) {
	if (!list.head) {
		list.head = list.tail = new Node{element, nullptr};
	} else {
		list.tail->next = new Node{element, nullptr};
		list.tail = list.tail->next;
	}
}



// Insert element at the beginning of the list.
void insert(LinkedListV1& list, int element) {
	if (!list.head) {
		list.head = new Node{element, nullptr};
	} else {
		Node* newNode = new Node{element, nullptr};
		newNode->next = list.head;
		list.head = newNode;
	}
}

void insert(LinkedListV2& list, int element) {
	if (!list.head) {
		list.head = list.tail = new Node{element, nullptr};
	} else {
		Node* newNode = new Node{element, nullptr};
		newNode->next = list.head;
		list.head = newNode;
	}
}




// Main function starts here.
int main() {
	cout << "Hello world!" << endl;
	return 0;
}
