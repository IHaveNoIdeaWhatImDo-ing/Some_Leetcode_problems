#include <deque>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

/*
    You are given a 0-indexed 2D integer array grid of size m x n.
Each cell has one of two values:

    0 represents an empty cell,
    1 represents an obstacle that may be removed.

You can move up, down, left, or right from and to an empty cell.

    Return the minimum number of obstacles to remove so you can move
from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1).
*/

#define AT(x, y, cols) ((x) * cols + y)

unsigned int dist[100000];

struct Cell
{
    unsigned int row;
    unsigned int col;

    Cell(
        unsigned int _row = 0u,
        unsigned int _col = 0u
    ) :
        row(_row), col(_col)
    {}
};

int minimumObstacles(vector<vector<int>>& grid)
{
    size_t m {grid.size()};
    size_t n {grid[0].size()};

    // emplace_back  - cells with distance 0
    // emplace_front - cells with distance 1
    deque<Cell> bfs;

    Cell temp;
    unsigned int sum;
    unsigned int current;
    size_t idx;

    // 255 = 11111111 in binary
    memset(dist, -1, m * n * sizeof(unsigned int));
    dist[0] = 0u;

    bfs.emplace_front(0, 0);

    while (!bfs.empty())
    {
        temp = bfs.front();
        bfs.pop_front();

        current = dist[AT(temp.row, temp.col, n)];

        if (temp.row == m - 1 && temp.col == n - 1)
        {
            break;
        }

        if (temp.row > 0)
        {
            sum = current + grid[temp.row - 1][temp.col];

            if (dist[AT(temp.row - 1, temp.col, n)] > sum)
            {
                dist[AT(temp.row - 1, temp.col, n)] = sum;

                if (grid[temp.row - 1][temp.col] == 1)
                {
                    bfs.emplace_back(
                        temp.row - 1,
                        temp.col
                    );
                }
                else
                {
                    bfs.emplace_front(
                        temp.row - 1,
                        temp.col
                    );
                }
            }
        }

        if (temp.row < m - 1)
        {
            sum = current + grid[temp.row + 1][temp.col];

            if (dist[AT(temp.row + 1, temp.col, n)] > sum)
            {
                dist[AT(temp.row + 1, temp.col, n)] = sum;

                if (grid[temp.row + 1][temp.col] == 1)
                {
                    bfs.emplace_back(
                        temp.row + 1,
                        temp.col
                    );
                }
                else
                {
                    bfs.emplace_front(
                        temp.row + 1,
                        temp.col
                    );
                }
            }
        }

        if (temp.col > 0)
        {
            sum = current + grid[temp.row][temp.col - 1];

            if (dist[AT(temp.row, temp.col - 1, n)] > sum)
            {
                dist[AT(temp.row, temp.col - 1, n)] = sum;

                if (grid[temp.row][temp.col - 1] == 1)
                {
                    bfs.emplace_back(
                        temp.row,
                        temp.col - 1
                    );
                }
                else
                {
                    bfs.emplace_front(
                        temp.row,
                        temp.col - 1
                    );
                }
            }
        }

        if (temp.col < n - 1)
        {
            sum = current + grid[temp.row][temp.col + 1];

            if (dist[AT(temp.row, temp.col + 1, n)] > sum)
            {
                dist[AT(temp.row, temp.col + 1, n)] = sum;

                if (grid[temp.row][temp.col + 1] == 1)
                {
                    bfs.emplace_back(
                        temp.row,
                        temp.col + 1
                    );
                }
                else
                {
                    bfs.emplace_front(
                        temp.row,
                        temp.col + 1
                    );
                }
            }
        }
    }

    return static_cast<int>(dist[m * n - 1]);
}

int main()
{
    vector<vector<int>> grid1 {{0,1,1},{1,1,0},{1,1,0}};
    vector<vector<int>> grid2 {{0,1,0,0,0},{0,1,0,1,0},{0,0,0,1,0}};

    cout << minimumObstacles(grid1) << '\n';
    cout << minimumObstacles(grid2) << '\n';

    return 0;
}
