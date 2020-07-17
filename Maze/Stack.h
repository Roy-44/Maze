#ifndef _STACK_H
#define _STACK_H
#include "Node.h"

class Stack
{
private:
	Node* top;

public:
	Stack();
	Stack(const Stack& other) = delete;
	~Stack();

	void MakeEmpty();
	bool IsEmpty();
	void Push(const Point& p);
	Point Pop();
};

#endif _STACK_H