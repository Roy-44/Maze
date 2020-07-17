#include "Maze.h"
#include "Point.h"

const int MAX_ROWS = 25;
const int MAX_COLS = 80;

void getAndCheckSize(int* rows, int* cols);
bool checkString(int rows, int cols, int curRow, char* row);
void cleanBuffer();

int main()
{
	int choice, rows, cols;
	char* row = nullptr;
	std::cout << "Maze: 1) From input 2) Random\n";
	std::cin >> choice;
	if (choice == 1)
	{
		getAndCheckSize(&rows, &cols);
		cleanBuffer();
		Maze maze(rows, cols);
		for (int i = 0; i < rows; i++)
		{
			delete[] row;
			row = new char[cols + 1]; 
			std::cin.getline(row, cols + 1);
			if (checkString(rows, cols, i, row))
			{
				int j;
				for (j = 0; j < cols && row[j] != '\0'; j++)
					maze.addToMaze(row[j], Point(i, j));
				if (j < cols)
				{
					for (j; j < cols; j++)
						maze.addToMaze(' ', Point(i, j));
				}
			}
			else
			{
				std::cout << "invalid input\n";
				exit(1);
			}
		}
		maze.solveMaze();
		maze.printMaze();
	}
	else if(choice == 2)
	{
		getAndCheckSize(&rows, &cols);
		Maze maze(rows, cols);
		maze.buildMaze(rows, cols);
		maze.solveMaze();
		maze.printMaze();
	}
	else
	{
		std::cout << "invalid input\n";
		exit(1);
	}
}

void getAndCheckSize(int * rows, int * cols)
{//get the input from the user and check it.
	std::cin >> *rows >> *cols;
	if (*rows < 3 || *rows > MAX_ROWS || *cols < 3 || *cols > MAX_COLS)
	{
		std::cout << "invalid input\n";
		exit(1);
	}
}

bool checkString(int rows, int cols, int curRow, char * row)
{//return true if the row entered is legal.
	int i;
	if (row[cols] != '\0' && curRow != rows - 2)
	{
		std::cout << "invalid input\n";
		exit(1);
	}
	if (curRow == 0 || curRow == rows - 1)//the first and last row must be row of *.
	{
		for (i = 0; i < cols; i++)
			if (row[i] != '*')
			{
				std::cout << "invalid input\n";
				exit(1);
			}
	}
	else if (curRow == 1)//the row of the enter.
	{
		if (row[0] != ' ')//the enter point must be space.
		{
			std::cout << "invalid input\n";
			exit(1);
		}
		for (i = 0; i < cols; i++)
			if (row[i] != '*' && row[i] != ' ')
			{
				std::cout << "invalid input\n";
				exit(1);
			}
	}
	else if (curRow == rows - 2)//the exit row
	{
		if (row[0] != '*')
		{
			std::cout << "invalid input\n";
			exit(1);
		}
		i = 1;
		while (row[i] != '\0')
		{
			if (row[i] != '*' && row[i] != ' ')
			{
				std::cout << "invalid input\n";
				exit(1);
			}
			i++;
		}
		if (i > cols - 1)//check if the exit point and the point befor are space
		{
			if (row[cols - 2] != ' ' || row[cols - 1] != ' ')
			{
				std::cout << "invalid input\n";
				exit(1);
			}
		}
		else if (i > cols - 2)//check if the exit point is space
		{
			if (row[cols - 2] != ' ')
			{
				std::cout << "invalid input\n";
				exit(1);
			}
		}
	}
	else//the other rows.
	{
		if (row[0] != '*' || row[cols - 1] != '*')
		{
			std::cout << "invalid input\n";
			exit(1);
		}
		for (i = 0; i < cols; i++)
			if (row[i] != '*' && row[i] != ' ')
			{
				std::cout << "invalid input\n";
				exit(1);
			}
	}
	return true;
}

void cleanBuffer()
{//cleaning the buffer.
	int c;
	do 
	{
		c = std::getchar();
	} while (c != EOF && c != '\n');
}
