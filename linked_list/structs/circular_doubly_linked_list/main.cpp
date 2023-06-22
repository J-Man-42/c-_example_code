#include <iostream>
using namespace std;


// The node struct for linked list.
struct Node
{
	int data;
	Node* next;
	Node* prev;
};


// Linked List structure.
struct LinkedList
{
	Node* head;
};


// Function prototypes.
void append(LinkedList& list, int element);
void insert(LinkedList& list, int element);
void print(LinkedList& list, bool ascending = true);
bool search(LinkedList& list, int element);
bool remove(LinkedList& list, int element);


// Append element to the end of the list.
void append(LinkedList& list, int element) {
	if (!list.head) {
		list.head = new Node;
		list.head->data = element;
		list.head->next = list.head;
		list.head->prev = list.head;
	} else {
		Node* newNode = new Node;
		newNode->data = element;
		newNode->next = list.head;
		newNode->prev = list.head->prev;
		newNode->next->prev = newNode;
		newNode->prev->next = newNode;
	}
}


// Insert element at the beginning of the list.
void insert(LinkedList& list, int element) {
	if (!list.head) {
		list.head = new Node;
		list.head->data = element;
		list.head->next = list.head;
		list.head->prev = list.head;
	} else {
		Node* newNode = new Node;
		newNode->data = element;
		newNode->next = list.head;
		newNode->prev = list.head->prev;
		newNode->next->prev = newNode;
		newNode->prev->next = newNode;
		list.head = newNode;
	}
}


// Print all entries of the linked list.
void print(LinkedList& list, bool ascending) {
	if (!list.head) {
		cout << endl;
		return;
	}
	Node* nodePtr = list.head;
	if (ascending) {
		do {
			cout << nodePtr->data << " ";
			nodePtr = nodePtr->next;
		} while (nodePtr != list.head);
	} else {
		do {
			nodePtr = nodePtr->prev;
			cout << nodePtr->data << " ";
		} while (nodePtr != list.head);
	}
	cout << endl;
}


// Search the linked list for the given element.
bool search(LinkedList& list, int element) {
	if (!list.head) {
		return false;
	}
	Node* nodePtr = list.head;
	do {
		if (nodePtr->data == element) {
			return true;
		}
		nodePtr = nodePtr->next;
	} while (nodePtr != list.head);
	return false;
}


// The remove the given element from the list.
bool remove(LinkedList& list, int element) {
	if (!list.head) {
		return false;
	}

	if (list.head->data == element) {
		if (list.head->next == list.head) {
			delete list.head;
			list.head = nullptr;
		} else {
			Node* nodePtr = list.head;
			list.head = nodePtr->next;
			nodePtr->prev->next = nodePtr->next;
			nodePtr->next->prev = nodePtr->prev;
			delete nodePtr;
		}
		return true;
	}

	Node* nodePtr = list.head->next;
	while (nodePtr != list.head) {
		if (nodePtr->data == element) {
			nodePtr->prev->next = nodePtr->next;
			nodePtr->next->prev = nodePtr->prev;
			delete nodePtr;
			return true;
		}
		nodePtr = nodePtr->next;
	}

	return false;
}



// Main function starts here.
int main() {
	char answer;
	int element;
	LinkedList* list = new LinkedList;

	do {
		cout << "\n\nList:\n";
		cout << "Forward:   ";
		print(*list);
		cout << "Backward:  ";
		print(*list, false);

		cout << "\n====================" << endl;
		cout << "(1)  append(element)" << endl;
		cout << "(2)  insert(element)" << endl;
		cout << "(3)  search(element)" << endl;
		cout << "(4)  remove(element)" << endl;
		cout << "(Q)  QUIT PROGRAM" << endl;
		cout << "====================" << endl;
		cout << "> ";
		cin >> answer;
		answer = toupper(answer);

		switch (answer) {
		case '1':
			cout << "append(element)" << endl;
			cout << "element = ";
			cin >> element;
			append(*list, element);
			break;
		case '2':
			cout << "insert(element)" << endl;
			cout << "element = ";
			cin >> element;
			insert(*list, element);
			break;
		case '3':
			cout << "search(element)" << endl;
			cout << "element = ";
			cin >> element;
			cout << "element found:  ";
			if (search(*list, element)) {
				cout << "true" << endl;
			} else {
				cout << "false" << endl;
			}
			break;
		case '4':
			cout << "remove(element)" << endl;
			cout << "element = ";
			cin >> element;
			cout << "element removed:  ";
			if (remove(*list, element)) {
				cout << "true" << endl;
			} else {
				cout << "false" << endl;
			}
			break;
		}

	} while (answer != 'Q');
	return 0;
}
