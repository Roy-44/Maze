#include "Node.h"

Node::Node(const Point& p, Node* next)
{
	data = p;
	this->next = next;
}

void Node::InsertAfter(Node* newNode)
{//insert the node after the node that operate the function.
	newNode->next = this->next;
	this->next = newNode;
}
