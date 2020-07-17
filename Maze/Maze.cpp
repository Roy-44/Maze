#include "Maze.h"
#include "Queue.h"
#include "Point.h"
#include "Stack.h"
#include <stdlib.h>
#include <time.h>

Maze::Maze(int hight, int width)
{
	maze = new char* [hight];
	for (int i = 0; i < hight; i++)
		maze[i] = new char[width];
	for(int i=0;i<hight;i++)
		for (int j = 0; j < width; j++)
			if ((i != 1 && j != 0) || (i != hight - 1 && j != width))
				maze[i][j] = '*';
	this->hight = hight;
	this->width = width;
}

Maze::~Maze()
{
	for (int i = 0; i < hight; i++)
		delete[] maze[i];
	delete[] maze;
}

int Maze::getMazeHight() const
{//return the maze hight
	return hight;
}

int Maze::getMazeWidth() const
{//return the maze width
	return width;
}

char Maze::getFromMaze(int row, int col) const
{//return the character on point (row,col) if legal point.
	if (row<0 || row>hight - 1 || col<0 || col>width - 1)
	{
		std::cout << "Illegal position!\n";
		return 0;
	}
	return maze[row][col];
}

bool Maze::addToMaze(char ch, const Point& p)
{// add a char to the maze at point p.
 //return false if ilegal point, else return true.
	if (p.getX() > hight - 1 || p.getX() < 0 || p.getY() > width - 1 || p.getY() < 0)
	{
		std::cout << "Illegal position!\n";
		return false;
	}
	maze[p.getX()][p.getY()] = ch;
	return true;
}

void Maze::printMaze()
{//print the maze
	for (int i = 0; i < hight; i++)
	{
		for (int j = 0; j < width; j++)
			std::cout << maze[i][j] << " ";
		std::cout << "\n";
	}
}

bool Maze::IsFree(const Point & p)
{//return true if the char at point p is space.
 //return false if illegal point or not space at p.
	if (p.getX() < 1 || p.getX() > hight - 1 || p.getY() < 0 || p.getY() > width - 1)
		return false;
	if (maze[p.getX()][p.getY()] == ' ')
		return true;
	return false;
}

bool Maze::IsThereFreeNeighbors(const Point & p, int* freeNeighbors)
{//fill the array freeNeighbors with 1 if there is neighbor and 0 if no.
 //return true if there is at least 1 neighbor.
	if (IsFree(Point(p.getX(), p.getY() + 2)))
		freeNeighbors[0] = 1;
	if (IsFree(Point(p.getX() + 2, p.getY())))
		freeNeighbors[1] = 1;
	if (IsFree(Point(p.getX(), p.getY() - 2)))
		freeNeighbors[2] = 1;
	if (IsFree(Point(p.getX() - 2, p.getY())))
		freeNeighbors[3] = 1;
	if (freeNeighbors[0] || freeNeighbors[1] || freeNeighbors[2] || freeNeighbors[3])
		return true;
	return false;
}

void Maze::makeFullMaze(int rows, int cols)
{//initialize the maze as defined. 
	if (rows % 2 == 0 || cols % 2 == 0)
	{
		std::cout << "invalid input\n";
		exit(1);
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if ((i == 1 && j == 0) || (i == rows - 2 && j == cols - 1))
				maze[i][j] = ' ';
			else if (i % 2 == 1 && j % 2 == 1)
				maze[i][j] = ' ';
			else
				maze[i][j] = '*';
		}
	}
}

void Maze::cleanMazeBuild()
{//switch the @ to spaces.
	for (int i = 0; i < hight; i++)
		for (int j = 0; j < width; j++)
			if (maze[i][j] == '@')
				maze[i][j] = ' ';
}

void Maze::solveMaze()
{
	Queue q(this->hight * this->width);
	Point p;
	bool flag = false;
	q.EnQueue(Point(1, 0));
	while (!q.IsEmpty() && !flag)
	{
		p = q.DeQueue();
		addToMaze('$', p);
		if (p.getX()== hight - 2 && p.getY() == width - 1)
			flag = true;
		else
		{
			if (IsFree(Point(p.getX(), p.getY() + 1)))
				q.EnQueue(Point(p.getX(), p.getY() + 1));
			if (IsFree(Point(p.getX() + 1, p.getY())))
				q.EnQueue(Point(p.getX() + 1, p.getY()));
			if (IsFree(Point(p.getX(), p.getY() - 1)))
				q.EnQueue(Point(p.getX(), p.getY() - 1));
			if (IsFree(Point(p.getX() - 1, p.getY())))
				q.EnQueue(Point(p.getX() - 1, p.getY()));
		}
	}
	if ((flag && maze[hight - 2][width - 1] != '$') || !flag)
	{
		std::cout << "no solution\n";
		exit(1);
	}
}

void Maze::buildMaze(int rows, int cols)
{
	makeFullMaze(rows, cols);
	Stack s;
	Point p(1, 1), neighbor;
	int r;
	srand((unsigned)time(NULL));
	bool flag = false;
	int freeNeighbors[4] = { 0,0,0,0 };			//[0] = right, [1] = down, [2] = left, [3] = up
	s.Push(p);
	while (!s.IsEmpty())
	{
		p = s.Pop();
		addToMaze('@', p);
		if (IsThereFreeNeighbors(p, freeNeighbors))
		{
			flag = false;
			while (!flag)
			{
				r = rand() % 4;
				if (r == 0 && freeNeighbors[0])
				{//right
					maze[p.getX()][p.getY() + 1] = ' ';
					neighbor.setX(p.getX());
					neighbor.setY(p.getY() + 2);
					s.Push(p);
					s.Push(neighbor);
					flag = true;
				}
				else if (r == 1 && freeNeighbors[1])
				{//down
					maze[p.getX() + 1][p.getY()] = ' ';
					neighbor.setX(p.getX() + 2);
					neighbor.setY(p.getY());
					s.Push(p);
					s.Push(neighbor);
					flag = true;
				}
				else if (r == 2 && freeNeighbors[2])
				{//left
					maze[p.getX()][p.getY() - 1] = ' ';
					neighbor.setX(p.getX());
					neighbor.setY(p.getY() - 2);
					s.Push(p);
					s.Push(neighbor);
					flag = true;
				}
				else if (r == 3 && freeNeighbors[3])
				{//up
					maze[p.getX() - 1][p.getY()] = ' ';
					neighbor.setX(p.getX() - 2);
					neighbor.setY(p.getY());
					s.Push(p);
					s.Push(neighbor);
					flag = true;
				}
			}
		}
		for (int i = 0; i < 4; i++)
			freeNeighbors[i] = 0;
	}
	cleanMazeBuild();
}