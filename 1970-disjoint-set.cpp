#include <queue>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

/*
    There is a 1-based binary matrix where 0 represents land and 1
represents water. You are given integers row and col representing the
number of rows and columns in the matrix, respectively.

    Initially on day 0, the entire matrix is land. However, each day a
new cell becomes flooded with water. You are given a 1-based 2D array
cells, where cells[i] = [ri, ci] represents that on the ith day, the
cell on the rith row and cith column (1-based coordinates) will be
covered with water (i.e., changed to 1).

    You want to find the last day that it is possible to walk from the
top to the bottom by only walking on land cells. You can start from any
cell in the top row and end at any cell in the bottom row. You can only
travel in the four cardinal directions (left, right, up, and down).

    Return the last day where it is possible to walk from the top to the
bottom by only walking on land cells.
*/

constexpr int maxCells {20003};

static inline short at(short row, short col, short cols)
{
    return row * cols + col;
}

bool water[maxCells];

struct DisjointSet
{
    short parent[maxCells];
    short weight[maxCells];

    void init(size_t size)
    {
        for (size_t i = 0; i < size; ++i)
        {
            parent[i] = static_cast<short>(i);
            weight[i] = static_cast<short>(1);
        }
        
        parent[maxCells - 2] = maxCells - 2;
        parent[maxCells - 1] = maxCells - 1;
    }

    DisjointSet(size_t size = 0)
    {
        init(size);
    }

    int getRoot(short node)
    {
        while (parent[node] ^ node)
        {
            node = getRoot(parent[node]);
        }

        return parent[node];
    }

    bool areInOneSet(short l, short r)
    {
        return getRoot(l) == getRoot(r);
    }

    bool unite(short l, short r)
    {
        short parentLeft = getRoot(l);
        short parentRight = getRoot(r);

        if (parentLeft == parentRight)
        {
            return false;
        }

        if (weight[parentRight] < weight[parentLeft])
        {
            parent[parentRight] = parentLeft;
            weight[parentLeft] += weight[parentRight];
        }
        else
        {
            parent[parentLeft] = parentRight;
            weight[parentRight] += weight[parentLeft];
        }

        return true;
    }
} ds;

int latestDayToCross(int rows, int cols, vector<vector<int>>& cells)
{
    size_t i {};
    size_t size {cells.size()};

    short row;
    short col;

    short west {maxCells - 2};
    short east {maxCells - 1};

    short current;
    short next;

    bool left;
    bool right;
    bool up;
    bool down;

    memset(water, false, maxCells * sizeof(bool));

    ds.init(size);

    for (; i < size; ++i)
    {
        if (ds.areInOneSet(west, east))
        {
            break;
        }

        row = static_cast<short>(cells[i][0] - 1);
        col = static_cast<short>(cells[i][1] - 1);

        current = at(row, col, cols);
        water[current] = true;

        up = row > 0;
        down = row < rows - 1;
        left = col > 0;
        right = col < cols - 1;

        if (col == 0)
        {
            ds.unite(west, at(row, col, cols));
        }
        else if (col == cols - 1)
        {
            ds.unite(east, at(row, col, cols));
        }

        // in the 4 cardinal directions

        next = at(row - 1, col, cols);
        if (up && water[next])
        {
            ds.unite(current, next);
        }
        
        next = at(row + 1, col, cols);
        if (down && water[next])
        {
            ds.unite(current, next);
        }

        next = at(row, col - 1, cols);
        if (left && water[next])
        {
            ds.unite(current, next);
        }
        
        next = at(row, col + 1, cols);
        if (right && water[next])
        {
            ds.unite(current, next);
        }

        // in diagonals

        next = at(row - 1, col - 1, cols);
        if (up && left && water[next])
        {
            ds.unite(current, next);
        }
        
        next = at(row - 1, col + 1, cols);
        if (up && right && water[next])
        {
            ds.unite(current, next);
        }

        next = at(row + 1, col - 1, cols);
        if (down && left && water[next])
        { 
            ds.unite(current, next);
        }
        
        next = at(row + 1, col + 1, cols);
        if (down && right && water[next])
        {
            ds.unite(current, next);
        }
    }

    return static_cast<int>(i - 1);
}

int main()
{
    int row1 {2};
    int col1 {2};
    vector<vector<int>> cells1 {{1,1},{2,1},{1,2},{2,2}};

    int row2 {2};
    int col2 {2};
    vector<vector<int>> cells2 {{1,1},{1,2},{2,1},{2,2}};

    int row3 {3};
    int col3 {3};
    vector<vector<int>> cells3 {{1,2},{2,1},{3,3},{2,2},{1,1},{1,3},{2,3},{3,2},{3,1}};

    cout << latestDayToCross(row1, col1, cells1) << '\n';
    cout << latestDayToCross(row2, col2, cells2) << '\n';
    cout << latestDayToCross(row3, col3, cells3) << '\n';

    return 0;
}
