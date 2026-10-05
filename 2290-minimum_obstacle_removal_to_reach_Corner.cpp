#include <queue>
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

struct Cell
{
    int row;
    int col;
    unsigned int weight;

    Cell(int _row = 0, int _col = 0, unsigned int _weight = 0) :
        row(_row), col(_col), weight(_weight)
    {}
};

struct comp
{
    bool operator() (const Cell& l, const Cell& r) const
    {
        return l.weight > r.weight;
    }
};

unsigned int dist[100000];

int minimumObstacles(vector<vector<int>>& grid)
{
    size_t m {grid.size()};
    size_t n {grid[0].size()};

    priority_queue<Cell, vector<Cell>, comp> bfs;

    Cell temp;
    unsigned int sum;

    memset(&dist[0], -1, m * n * sizeof(unsigned int));

    dist[0] = 0;
    bfs.emplace(0, 0, 0);

    while (!bfs.empty())
    {
        temp = bfs.top();
        bfs.pop();

        if (temp.weight > dist[temp.row * n + temp.col])
        {
            continue;
        }

        if (temp.row == m - 1 && temp.col == n - 1)
        {
            break;
        }

        if (temp.row > 0)
        {
            sum = dist[temp.row * n + temp.col] + static_cast<unsigned int>(grid[temp.row - 1][temp.col] == 1);

            if (dist[(temp.row - 1) * n + temp.col] > sum)
            {
                dist[(temp.row - 1) * n + temp.col] = sum;

                bfs.emplace(
                    temp.row - 1,
                    temp.col,
                    sum
                );
            }
        }

        if (temp.row < m - 1)
        {
            sum = dist[temp.row * n + temp.col] + static_cast<unsigned int>(grid[temp.row + 1][temp.col] == 1);

            if (dist[(temp.row + 1) * n + temp.col] > sum)
            {
                dist[(temp.row + 1) * n + temp.col] = sum;

                bfs.emplace(
                    temp.row + 1,
                    temp.col,
                    sum
                );
            }
        }

        if (temp.col > 0)
        {

            sum = dist[temp.row * n + temp.col] + static_cast<unsigned int>(grid[temp.row][temp.col - 1] == 1);

            if (dist[temp.row * n + temp.col - 1] > sum)
            {
                dist[temp.row * n + temp.col - 1] = sum;

                bfs.emplace(
                    temp.row,
                    temp.col - 1,
                    sum
                );
            }
        }

        if (temp.col < n - 1)
        {
            sum = dist[temp.row * n + temp.col] + static_cast<unsigned int>(grid[temp.row][temp.col + 1] == 1);

            if (dist[temp.row * n + temp.col + 1] > sum)
            {
                dist[temp.row * n + temp.col + 1] = sum;

                bfs.emplace(
                    temp.row,
                    temp.col + 1,
                    sum
                );
            }
        }
    }

    return dist[m * n - 1];
}

int main()
{
    vector<vector<int>> grid1 {{0,1,1},{1,1,0},{1,1,0}};
    vector<vector<int>> grid2 {{0,1,0,0,0},{0,1,0,1,0},{0,0,0,1,0}};

    cout << minimumObstacles(grid1) << '\n';
    cout << minimumObstacles(grid2) << '\n';

    return 0;
}
