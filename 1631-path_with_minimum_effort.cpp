#include <queue>
#include <vector>
#include <iostream>

using namespace std;

/*
    You are a hiker preparing for an upcoming hike. You are given heights, a
2D array of size rows x columns, where heights[row][col] represents the height
of cell (row, col). You are situated in the top-left cell, (0, 0), and you hope
to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). You
can move up, down, left, or right, and you wish to find a route that requires
the minimum effort.

    A route's effort is the maximum absolute difference in heights between two
consecutive cells of the route.

    Return the minimum effort required to travel from the top-left cell to the
bottom-right cell.
*/

struct CoordsEffort
{
    unsigned char row;
    unsigned char col;

    int maxDif;

    CoordsEffort(
        unsigned char row = 0,
        unsigned char col = 0,
        int maxDif = 0
    )
        : row(row), col(col), maxDif(maxDif)
    {}
};

struct comp
{
    bool operator() (const CoordsEffort& l, const CoordsEffort& r) const
    {
        return l.maxDif > r.maxDif;
    }
};

constexpr int intMax {static_cast<int>(~0u >> 1)};

int minimumEffortPath(vector<vector<int>>& heights)
{
    int rows = static_cast<int>(heights.size());
    int cols = static_cast<int>(heights[0].size());

    priority_queue<CoordsEffort, vector<CoordsEffort>, comp> pq;
    pq.emplace(0, 0, 0);

    vector<vector<int>> effort(rows, vector<int>(cols, intMax));
    effort[0][0] = 0;

    CoordsEffort temp;
    int index;
    int dif;

    while (!pq.empty())
    {
        temp = pq.top();
        pq.pop();

        if (temp.row == rows - 1 && temp.col == cols - 1)
        {
            return temp.maxDif;
        }

        if (temp.maxDif > effort[temp.row][temp.col])
        {
            continue;
        }

        if (temp.row > 0)
        {
            dif = max(temp.maxDif, abs(heights[temp.row][temp.col] - heights[temp.row - 1][temp.col]));

            if (dif < effort[temp.row - 1][temp.col])
            {
                effort[temp.row - 1][temp.col] = dif;

                pq.emplace(
                    temp.row - 1,
                    temp.col,
                    dif
                );
            }
        }

        if (temp.row < rows - 1)
        {
            dif = max(temp.maxDif, abs(heights[temp.row][temp.col] - heights[temp.row + 1][temp.col]));

            if (dif < effort[temp.row + 1][temp.col])
            {
                effort[temp.row + 1][temp.col] = dif;
                
                pq.emplace(
                    temp.row + 1,
                    temp.col,
                    dif
                );
            }
        }
        
        if (temp.col > 0)
        {
            dif = max(temp.maxDif, abs(heights[temp.row][temp.col] - heights[temp.row][temp.col - 1]));

            if (dif < effort[temp.row][temp.col - 1])
            {
                effort[temp.row][temp.col - 1] = dif;
                
                pq.emplace(
                    temp.row,
                    temp.col - 1,
                    dif
                );
            }
        }

        if (temp.col < cols - 1)
        {
            dif = max(temp.maxDif, abs(heights[temp.row][temp.col] - heights[temp.row][temp.col + 1]));

            if (dif < effort[temp.row][temp.col + 1])
            {
                effort[temp.row][temp.col + 1] = dif;

                pq.emplace(
                    temp.row,
                    temp.col + 1,
                    dif
                );
            }
        }
    }

    return 0;
}

int main()
{
    vector<vector<int>> heights1 = {{1,2,2},{3,8,2},{5,3,5}};
    vector<vector<int>> heights2 = {{1,2,3},{3,8,4},{5,3,5}};
    vector<vector<int>> heights3 = {{1,2,1,1,1},{1,2,1,2,1},{1,2,1,2,1},{1,2,1,2,1},{1,1,1,2,1}};
    vector<vector<int>> heights4 = {{1,10,6,7,9,10,4,9}};
    vector<vector<int>> heights5 = {{10,8},{10,8},{1,2},{10,3},{1,3},{6,3},{5,2}};

    cout << minimumEffortPath(heights1) << '\n';
    cout << minimumEffortPath(heights2) << '\n';
    cout << minimumEffortPath(heights3) << '\n';
    cout << minimumEffortPath(heights4) << '\n';
    cout << minimumEffortPath(heights5) << '\n';

    return 0;
}
