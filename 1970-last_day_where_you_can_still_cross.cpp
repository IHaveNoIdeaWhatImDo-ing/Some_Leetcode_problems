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

#define AT(x, y, cols) ((x) * cols + y)

bool grid [20000];
bool visited [20000];

bool reachesShore(size_t rows, size_t cols)
{
    queue<unsigned short> bfs;

    unsigned short temp;
    unsigned short row;
    unsigned short col;

    memset(visited, false, rows * cols * sizeof(bool));

    for (size_t i {}; i < cols; ++i)
    {
        if (grid[i] == false)
        {
            bfs.emplace(i);
            visited[i] = true;
        }
    }

    while (!bfs.empty())
    {
        temp = bfs.front();
        bfs.pop();

        row = temp / cols;
        col = temp % cols;

        if (row == rows - 1)
        {
            return true;
        }

        if (row > 0)
        {
            temp = AT(row - 1, col, cols);

            if (!visited[temp] && !grid[temp])
            {
                visited[temp] = true;
                bfs.emplace(temp);
            }
        }

        if (row < rows - 1)
        {
            temp = AT(row + 1, col, cols);

            if (!visited[temp] && !grid[temp])
            {
                visited[temp] = true;
                bfs.emplace(temp);
            }
        }

        if (col > 0)
        {
            temp = AT(row, col - 1, cols);

            if (!visited[temp] && !grid[temp])
            {
                visited[temp] = true;
                bfs.emplace(temp);
            }
        }

        if (col < cols - 1)
        {
            temp = AT(row, col + 1, cols);

            if (!visited[temp] && !grid[temp])
            {
                visited[temp] = true;
                bfs.emplace(temp);
            }
        }
    }

    return false;
}

int latestDayToCross(int row, int col, vector<vector<int>>& cells)
{
    int res;

    size_t minTime {};
    size_t maxTime {cells.size() - 1};

    size_t mid {(minTime + maxTime) / 2};

    size_t i {};

    bool isReachable;

    for (; i < mid; ++i)
    {
        grid[AT(cells[i][0] - 1, cells[i][1] - 1, col)] = true;
    }

    while (minTime <= maxTime)
    {
        isReachable = reachesShore(row, col);

        if (isReachable)
        {
            minTime = mid + 1;

            mid = (minTime + maxTime) / 2;
        }
        else
        {
            maxTime = mid - 1;
            res = static_cast<int>(mid);

            mid = (minTime + maxTime) / 2;
        }

        memset(grid, false, row * col * sizeof(bool));
        for (i = 0; i < mid; ++i)
        {
            grid[AT(cells[i][0] - 1, cells[i][1] - 1, col)] = true;
        }
    }

    return res - 1;
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
