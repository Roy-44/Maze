#include "Point.h"

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

bool Point::setX(int num)
{
	x = num;
	return true;
}

bool Point::setY(int num)
{
	y = num;
	return true;
}
