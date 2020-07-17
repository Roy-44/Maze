#include "Stack.h"

Stack::Stack()
{
	top = nullptr;
}

Stack::~Stack()
{
	MakeEmpty();
}

void Stack::MakeEmpty()
{//make empty stack.
	Node* temp;
	while (top != nullptr)
	{
		temp = top;
		top = top->next;
		delete temp;
	}
}

bool Stack::IsEmpty()
{//return true if the stack is empty.
	return top == nullptr ? true : false;
}

void Stack::Push(const Point& p)
{//add new point p to the stack
	top = new Node(p, top);
}

Point Stack::Pop()
{//remove and return the top point in the stack.
	if (IsEmpty())
	{
		std::cout << "Stack Is Empty!\n";
		exit(1);
	}
	Node* temp = top;
	Point item = top->data;
	top = top->next;
	delete temp;
	return item;
}