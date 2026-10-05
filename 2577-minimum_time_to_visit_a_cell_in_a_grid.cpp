#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

/*
    You are given a m x n matrix grid consisting of non-negative integers
where grid[row][col] represents the minimum time required to be able to
visit the cell (row, col), which means you can visit the cell (row, col)
only when the time you visit it is greater than or equal to grid[row][col].

    You are standing in the top-left cell of the matrix in the 0th second,
and you must move to any adjacent cell in the four directions: up, down,
left, and right. Each move you make takes 1 second.

    Return the minimum time required in which you can visit the
bottom-right cell of the matrix. If you cannot visit the bottom-right cell,
then return -1.
*/

static inline int AT(int row, int col, int n)
{
    return row * n + col;
}

unsigned int dist[100000];

struct Cell
{
    short row;
    short col;
    unsigned int steps;

    Cell(short _row = 0, short _col = 0, unsigned int _steps = 0u) :
        row(_row), col(_col), steps(_steps)
    {}
};

struct comp
{
    bool operator() (const Cell& l, const Cell& r) const
    {
        return l.steps > r.steps;
    }
};

int minimumTime(vector<vector<int>>& grid)
{
    if (grid[0][1] > 1 && grid[1][0] > 1)
    {
        return -1;
    }

    size_t m {grid.size()};
    size_t n {grid[0].size()};

    priority_queue<Cell, vector<Cell>, comp> pq;

    pq.emplace(0, 0, 0);

    Cell temp;
    unsigned int currentDist;
    int currIdx;
    int nextIdx;

    memset(dist, 0xFF, m * n * sizeof(unsigned int));
    dist[0] = 0u;

    while (!pq.empty())
    {
        temp = pq.top();
        pq.pop();

        if (temp.row == m - 1 && temp.col == n - 1)
        {
            break;
        }

        currIdx = AT(temp.row, temp.col, n);

        if (temp.row > 0)
        {
            currentDist = max(
                dist[currIdx] + 1,
                grid[temp.row - 1][temp.col] + static_cast<unsigned int>(temp.steps % 2 == grid[temp.row - 1][temp.col] % 2)
            );
            nextIdx = AT(temp.row - 1, temp.col, n);

            if (dist[nextIdx] > currentDist)
            {
                dist[nextIdx] = currentDist;

                pq.emplace(
                    temp.row - 1,
                    temp.col,
                    currentDist
                );
            }
        }

        if (temp.row < m - 1)
        {
            currentDist = max(
                dist[currIdx] + 1,
                grid[temp.row + 1][temp.col] + static_cast<unsigned int>(temp.steps % 2 == grid[temp.row + 1][temp.col] % 2)
            );
            nextIdx = AT(temp.row + 1, temp.col, n);

            if (dist[nextIdx] > currentDist)
            {
                dist[nextIdx] = currentDist;

                pq.emplace(
                    temp.row + 1,
                    temp.col,
                    currentDist
                );
            }
        }

        if (temp.col > 0)
        {
            currentDist = max(
                dist[currIdx] + 1,
                grid[temp.row][temp.col - 1] + static_cast<unsigned int>(temp.steps % 2 == grid[temp.row][temp.col - 1] % 2)
            );
            nextIdx = AT(temp.row, temp.col - 1, n);

            if (dist[nextIdx] > currentDist)
            {
                dist[nextIdx] = currentDist;

                pq.emplace(
                    temp.row,
                    temp.col - 1,
                    currentDist
                );
            }
        }

        if (temp.col < n - 1)
        {
            currentDist = max(
                dist[currIdx] + 1,
                grid[temp.row][temp.col + 1] + static_cast<unsigned int>(temp.steps % 2 == grid[temp.row][temp.col + 1] % 2)
            );
            nextIdx = AT(temp.row, temp.col + 1, n);

            if (dist[nextIdx] > currentDist)
            {
                dist[nextIdx] = currentDist;

                pq.emplace(
                    temp.row,
                    temp.col + 1,
                    currentDist
                );
            }
        }
    }

    return static_cast<int>(dist[AT(m - 1, n - 1, n)]);
}

int main()
{
    vector<vector<int>> grid1 = {{0,1,3,2},
                                 {5,1,2,5},
                                 {4,3,8,6}};
    vector<vector<int>> grid2 = {{0,2,4},
                                 {3,2,1},
                                 {1,0,4}};
    vector<vector<int>> grid3 = {{   0,    1, 1000, 2},
                                 {1000, 1000,    2, 5},
                                 {   4,    3,    8, 6}};

    cout << minimumTime(grid1) << '\n';
    cout << minimumTime(grid2) << '\n';
    cout << minimumTime(grid3) << '\n';

    return 0;
}
