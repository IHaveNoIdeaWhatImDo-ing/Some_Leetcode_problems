#include <queue>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

/*
    You are given an n x n integer matrix grid where each value grid[i][j]
represents the elevation at that point (i, j).

    It starts raining, and water gradually rises over time. At time t, the
water level is t, meaning any cell with elevation less than equal to t is
submerged or reachable.

    You can swim from a square to another 4-directionally adjacent square
if and only if the elevation of both squares individually are at most t.
You can swim infinite distances in zero time. Of course, you must stay
within the boundaries of the grid during your swim.

    Return the minimum time until you can reach the bottom right square
(n - 1, n - 1) if you start at the top left square (0, 0).
*/

static inline size_t at(size_t row, size_t col, size_t n)
{
    return row * n + col;
}

constexpr short gridSize {2500};

struct DisjointSet
{
    short parent[gridSize];
    short weight[gridSize];

    void init(size_t size)
    {
        for (size_t i = 0; i < size; ++i)
        {
            parent[i] = static_cast<short>(i);
            weight[i] = static_cast<short>(1);
        }
    }

    DisjointSet(size_t size = 0)
    {
        init(size);
    }

    short getRoot(short n)
    {
        if (static_cast<bool>(n ^ parent[n]))
        {
            parent[n] = getRoot(parent[n]);
        }

        return parent[n];
    }

    bool areConnected(short l, short r)
    {
        return getRoot(l) == getRoot(r);
    }

    bool unite(short l, short r)
    {
        short rootLeft = getRoot(l);
        short rootRight = getRoot(r);

        if (!static_cast<bool>(rootLeft ^ rootRight))
        {
            return false;
        }

        if (weight[rootLeft] > weight[rootRight])
        {
            parent[rootRight] = rootLeft;
            weight[rootLeft] += weight[rootRight];
        }
        else
        {
            parent[rootLeft] = rootRight;
            weight[rootRight] += weight[rootLeft];
        }

        return true;
    }
} ds;

short heights[gridSize];
bool flooded[gridSize];

int swimInWater(vector<vector<int>>& grid)
{
    size_t n {grid.size()};

    size_t i;
    size_t j;
    size_t size {n * n};

    short row;
    short col;

    short next;

    memset(flooded, false, size * sizeof(bool));
    ds.init(size);
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            heights[grid[i][j]] = at(i, j, n);
        }
    }

    for (i = 0; i < size; ++i)
    {
        flooded[heights[i]] = true;

        row = heights[i] / n;
        col = heights[i] % n;

        if (row > 0)
        {
            next = static_cast<short>(at(row - 1, col, n));

            if (flooded[next])
            {
                ds.unite(heights[i], next);
            }
        }

        if (row < n - 1)
        {
            next = static_cast<short>(at(row + 1, col, n));

            if (flooded[next])
            {
                ds.unite(heights[i], next);
            }
        }

        if (col > 0)
        {
            next = static_cast<short>(at(row, col - 1, n));

            if (flooded[next])
            {
                ds.unite(heights[i], next);
            }
        }

        if (col < n - 1)
        {
            next = static_cast<short>(at(row, col + 1, n));

            if (flooded[next])
            {
                ds.unite(heights[i], next);
            }
        }

        if (ds.areConnected(0, size - 1))
        {
            break;
        }
    }

    return static_cast<int>(i);
}

int main()
{
    vector<vector<int>> grid1 {{0,2},{1,3}};
    vector<vector<int>> grid2 {{0,1,2,3,4},{24,23,22,21,5},{12,13,14,15,16},{11,17,18,19,20},{10,9,8,7,6}};

    cout << swimInWater(grid1) << '\n';
    cout << swimInWater(grid2) << '\n';

    return 0;
}
