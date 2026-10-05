#include <queue>
#include <vector>
#include <iostream>

using namespace std;

/*
    You are given an m x n binary matrix grid, where 0 represents a sea
cell and 1 represents a land cell.

    A move consists of walking from one land cell to another adjacent
(4-directionally) land cell or walking off the boundary of the grid.

    Return the number of land cells in grid for which we cannot walk off
the boundary of the grid in any number of moves.
*/

struct Point
{
    short row;
    short col;

    Point(short row = 0, short col = 0) :
        row(row), col(col)
    {}
};

int numEnclaves(vector<vector<int>>& grid)
{
    size_t m = grid.size();
    size_t n = grid[0].size();

    size_t i {};
    size_t j {};
    Point temp {};
    int res {};
    
    queue<Point> bfs {};
    
    for (; i < m; ++i)
    {
        if (grid[i][0])
        {
            bfs.emplace(i, 0);
            grid[i][0] = 0;
        }

        if (grid[i][n - 1])
        {
            bfs.emplace(i, n - 1);
            grid[i][n - 1] = 0;
        }
    }

    for (i = 1; i < n - 1; ++i)
    {
        if (grid[0][i])
        {
            bfs.emplace(0, i);
            grid[0][i] = 0;
        }

        if (grid[m - 1][i])
        {
            bfs.emplace(m - 1, i);
            grid[m - 1][i] = 0;
        }
    }

    while (!bfs.empty())
    {
        temp = bfs.front();
        grid[temp.row][temp.col] = 0;
        bfs.pop();

        if (temp.row > 0 && grid[temp.row - 1][temp.col])
        {
            bfs.emplace(temp.row - 1, temp.col);
            grid[temp.row - 1][temp.col] = 0;
        }

        if (temp.row < m - 1 && grid[temp.row + 1][temp.col])
        {
            bfs.emplace(temp.row + 1, temp.col);
            grid[temp.row + 1][temp.col] = 0;
        }

        if (temp.col > 0 && grid[temp.row][temp.col - 1])
        {
            bfs.emplace(temp.row, temp.col - 1);
            grid[temp.row][temp.col - 1] = 0;
        }

        if (temp.col < n - 1 && grid[temp.row][temp.col + 1])
        {
            bfs.emplace(temp.row, temp.col + 1);
            grid[temp.row][temp.col + 1] = 0;
        }
    }

    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if (grid[i][j])
            {
                ++res;
            }
        }
    }

    return res;
}

int main()
{
    vector<vector<int>> grid1 = {
        {0,0,0,0},
        {1,0,1,0},
        {0,1,1,0},
        {0,0,0,0}
    };
    vector<vector<int>> grid2 = {
        {0,1,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,0,0}
    };

    cout << numEnclaves(grid1) << '\n';
    cout << numEnclaves(grid2) << '\n';

    return 0;
}
