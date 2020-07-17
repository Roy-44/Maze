#ifndef _MAZE_H
#define _MAZE_H
#include <iostream>

class Point;

class Maze
{
private:
	char** maze;
	int hight;
	int width;

public:
	Maze(int hight, int width);
	Maze(const Maze& other) = delete;
	~Maze();

	int getMazeHight() const;
	int getMazeWidth() const;
	char getFromMaze(int row, int col) const;
	bool addToMaze(char ch, const Point& p);

	void printMaze();
	bool IsFree(const Point& p);
	bool IsThereFreeNeighbors(const Point& p, int *freeNeighbors);
	void makeFullMaze(int rows, int cols);
	void cleanMazeBuild();

	void solveMaze();
	void buildMaze(int rows, int cols);
};

#endif _MAZE_H