#ifndef LINKED_LIST_H
#define LINKED_LIST_H


// The Node struct.
template<class T>
struct Node
{
	T data;
	Node* next;
	Node* prev;
};


// The standard linked list.
template<class T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();
	void clear();
private:
	Node<T>* head;
	Node<T>* tail;
};


#endif