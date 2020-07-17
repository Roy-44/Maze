#ifndef _NODE_H
#define _NODE_H
#include <iostream>
#include "Point.h"

class Node
{
private:
	Point data;
	Node* next;
	friend class Stack;

public:
	Node(const Point& p, Node* ptr = nullptr);

	void InsertAfter(Node* newNode);	
};

#endif _NODE_H