#include "Queue.h"
#include "Point.h"

Queue::Queue(int size)
{
	qSize = size;
	q = new Point[qSize + 1];
	head = 1;
	tail = 0;
}

Queue::~Queue()
{
	delete[] q;
}

void Queue::EnQueue(const Point& p)
{//add the point p to the queue.
	if (IsFull())
	{
		std::cout << "Queue Is Full!\n";
		std::cout << "Error!\n";
		exit(1);
	}
	this->tail = AddOne(this->tail);
	q[tail] = p;
}

Point Queue::DeQueue()
{//return the last point in the queue.
	if (IsEmpty())
	{
		std::cout << "Queue Is Empty!\n";
		std::cout << "Error!\n";
		exit(1);
	}
	Point* temp = &(q[head]);
	head = AddOne(head);
	return *temp;
}

void Queue::MakeEmpty()
{
	head = 1;
	tail = 0;
}

bool Queue::IsEmpty()
{//return true if the queue is empty else false.
	return AddOne(tail) == head ? true : false;
}

bool Queue::IsFull()
{//return true if the queue is empty else false.
	return AddOne(AddOne(tail)) == head ? true : false;
}

int Queue::AddOne(int x)
{//add 1 to the index of circle queue
	return (x + 1) % qSize;
}