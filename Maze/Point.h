#ifndef _POINT_H
#define _POINT_H

class Point
{
private:
	int x, y;

public:
	Point(int x = 0, int y = 0);

	int getX() const;
	int getY() const;

	bool setX(int num);
	bool setY(int num);
};

#endif