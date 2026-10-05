#include <queue>
#include <vector>
#include <cstdint>
#include <iostream>

using namespace std;

/*
    You are given an m x n matrix maze (0-indexed) with empty cells (represented as '.')
and walls (represented as '+'). You are also given the entrance of the maze, where
entrance = [entrancerow, entrancecol] denotes the row and column of the cell you are initially standing at.

    In one step, you can move one cell up, down, left, or right. You cannot step into a cell with
a wall, and you cannot step outside the maze. Your goal is to find the nearest exit from the entrance.
An exit is defined as an empty cell that is at the border of the maze. The entrance does not count as an exit.

    Return the number of steps in the shortest path from the entrance to the nearest exit,
or -1 if no such path exists.
*/

struct Point
{
    int row;
    int col;

    Point (int row = 0, int col = 0)
    {
        this->row = row;
        this->col = col;
    }
};

int nearestExit(vector<vector<char>>& maze, vector<int>& entrance)
{
    int rows = static_cast<int>(maze.size());
    int cols = static_cast<int>(maze[0].size());

    Point entry {entrance[0], entrance[1]};
    queue<Point> fringe {};
    fringe.push(entry);

    int len {};
    size_t fringeSize {1};
    Point temp {};

    temp = fringe.front();
    
    maze[temp.row][temp.col] = '+';
    fringe.pop();
    --fringeSize;

    if (temp.row > 0 && maze[temp.row - 1][temp.col] ^ '+')
    {
        fringe.emplace(temp.row - 1, temp.col);
        maze[temp.row - 1][temp.col] = '+';
    }

    if (temp.row < rows - 1 && maze[temp.row + 1][temp.col] ^ '+')
    {
        fringe.emplace(temp.row + 1, temp.col);
        maze[temp.row + 1][temp.col] = '+';
    }
    
    if (temp.col > 0 && maze[temp.row][temp.col - 1] ^ '+')
    {
        fringe.emplace(temp.row, temp.col - 1);
        maze[temp.row][temp.col - 1] = '+';
    }

    if (temp.col < cols - 1 && maze[temp.row][temp.col + 1] ^ '+')
    {
        fringe.emplace(temp.row, temp.col + 1);
        maze[temp.row][temp.col + 1] = '+';
    }

    fringeSize = fringe.size();
    ++len;

    while (!fringe.empty())
    {
        temp = fringe.front();

        if
        (
            temp.row == 0 ||
            temp.row == rows - 1 ||
            temp.col == 0 ||
            temp.col == cols - 1
        )
        {
            return len;
        }


        maze[temp.row][temp.col] = '+';
        fringe.pop();
        --fringeSize;

        if (temp.row > 0 && maze[temp.row - 1][temp.col] ^ '+')
        {
            fringe.emplace(temp.row - 1, temp.col);
            maze[temp.row - 1][temp.col] = '+';
        }

        if (temp.row < rows - 1 && maze[temp.row + 1][temp.col] ^ '+')
        {
            fringe.emplace(temp.row + 1, temp.col);
            maze[temp.row + 1][temp.col] = '+';
        }
        
        if (temp.col > 0 && maze[temp.row][temp.col - 1] ^ '+')
        {
            fringe.emplace(temp.row, temp.col - 1);
            maze[temp.row][temp.col - 1] = '+';
        }

        if (temp.col < cols - 1 && maze[temp.row][temp.col + 1] ^ '+')
        {
            fringe.emplace(temp.row, temp.col + 1);
            maze[temp.row][temp.col + 1] = '+';
        }

        if (!fringeSize)
        {
            fringeSize = fringe.size();
            ++len;
        }
    }

    return -1;
}

int main()
{
    vector<vector<char>> maze1 = {{'+','+','.','+'},{'.','.','.','+'},{'+','+','+','.'}};
    vector<int> entrance1 = {1,2};
    
    vector<vector<char>> maze2 = {{'+','+','+'},{'.','.','.'},{'+','+','+'}};
    vector<int> entrance2 = {1,0};
    
    vector<vector<char>> maze3 = {{'.','+'}};
    vector<int> entrance3 = {0,0};

    vector<vector<char>> maze4 = {{'.','.'}};
    vector<int> entrance4 = {0,1};

    cout << nearestExit(maze1, entrance1) << '\n';
    cout << nearestExit(maze2, entrance2) << '\n';
    cout << nearestExit(maze3, entrance3) << '\n';
    cout << nearestExit(maze4, entrance4) << '\n';

    return 0;
}
