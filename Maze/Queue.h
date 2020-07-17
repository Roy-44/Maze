#ifndef _QUEUE_H
#define _QUEUE_H
#include <iostream>
#include <string.h>
#pragma warning (disable: 4996)

class Point;

class Queue 
{
private:
	Point* q;
	int qSize;
	int head;
	int tail;

public:
	Queue(int size);
	Queue(const Queue& other) = delete;
	~Queue();

	void EnQueue(const Point& p);
	Point DeQueue();
	void MakeEmpty();
	bool IsEmpty();
	bool IsFull();
	int AddOne(int x);
};

#endif _QUEUE_H