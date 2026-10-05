#include <queue>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

/*
    Given an m x n grid. Each cell of the grid has a sign pointing to thenext cell you
should visit if you are currently in this cell. The sign of grid[i][j] can be:

    1 which means go to the cell to the right. (i.e go from grid[i][j] to grid[i][j + 1])
    2 which means go to the cell to the left. (i.e go from grid[i][j] to grid[i][j - 1])
    3 which means go to the lower cell. (i.e go from grid[i][j] to grid[i + 1][j])
    4 which means go to the upper cell. (i.e go from grid[i][j] to grid[i - 1][j])

    Notice that there could be some signs on the cells of the grid that point outside the
grid.

    You will initially start at the upper left cell (0, 0). A valid path in the grid is a
path that starts from the upper left cell (0, 0) and ends at the bottom-right cell
(m - 1, n - 1) following the signs on the grid. The valid path does not have to be the
shortest.

    You can modify the sign on a cell with cost = 1. You can modify the sign on a cell
one time only.

Return the minimum cost to make the grid have at least one valid path.
*/

struct Cell
{
    unsigned char row;
    unsigned char col;
    unsigned char cost;

    Cell(
        unsigned char _row = 0,
        unsigned char _col = 0,
        unsigned char _cost = 0
    ) :
        row(_row), col(_col), cost(_cost)
    {}
};

struct comp
{
    bool operator() (const Cell& l, const Cell& r) const
    {
        return l.cost > r.cost;
    }
};

constexpr unsigned char maxDist {static_cast<unsigned char>(201)};

unsigned char dist[100][100];

int minCost(vector<vector<int>>& grid)
{
    size_t m {grid.size()};
    size_t n {grid[0].size()};

    priority_queue<Cell, vector<Cell>, comp> pq;

    Cell temp;
    unsigned char sum;

    memset(&dist[0][0], maxDist, m * 100 * sizeof(unsigned char));
    dist[0][0] = 0;
    pq.emplace(0, 0, 0);

    while (!pq.empty())
    {
        temp = pq.top();
        pq.pop();

        if (temp.cost > dist[temp.row][temp.col])
        {
            continue;
        }

        //cout << (int)temp.row << ", " << (int)temp.col << " : " << (int)temp.cost << '\n';

        if (temp.row > 0)
        {
            sum = dist[temp.row][temp.col] + static_cast<unsigned char>(grid[temp.row][temp.col] != 4);

            if (sum < dist[temp.row - 1][temp.col])
            {
                //cout << (int)temp.row - 1 << ", " << (int)temp.col << " : " << (int)sum << " added\n";
                
                dist[temp.row - 1][temp.col] = sum;

                pq.emplace(
                    temp.row - 1,
                    temp.col,
                    sum
                );
            }
        }

        if (temp.row < m - 1)
        {
            sum = dist[temp.row][temp.col] + static_cast<unsigned char>(grid[temp.row][temp.col] != 3);

            if (sum < dist[temp.row + 1][temp.col])
            {
                //cout << (int)temp.row + 1 << ", " << (int)temp.col << " : " << (int)sum << " added\n";
                
                dist[temp.row + 1][temp.col] = sum;

                pq.emplace(
                    temp.row + 1,
                    temp.col,
                    sum
                );
            }
        }
        
        if (temp.col > 0)
        {
            sum = dist[temp.row][temp.col] + static_cast<unsigned char>(grid[temp.row][temp.col] != 2);

            if (sum < dist[temp.row][temp.col - 1])
            {
                //cout << (int)temp.row << ", " << (int)temp.col - 1 << " : " << (int)sum << " added\n";
                
                dist[temp.row][temp.col - 1] = sum;

                pq.emplace(
                    temp.row,
                    temp.col - 1,
                    sum
                );
            }
        }

        if (temp.col < n - 1)
        {
            sum = dist[temp.row][temp.col] + static_cast<unsigned char>(grid[temp.row][temp.col] != 1);

            if (sum < dist[temp.row][temp.col + 1])
            {
                //cout << (int)temp.row << ", " << (int)temp.col + 1 << " : " << (int)sum << " added\n";
                
                dist[temp.row][temp.col + 1] = sum;

                pq.emplace(
                    temp.row,
                    temp.col + 1,
                    sum
                );
            }
        }
    }

    return dist[m - 1][n - 1];
}

int main()
{
    vector<vector<int>> grid1 {{1,1,1,1},{2,2,2,2},{1,1,1,1},{2,2,2,2}};
    vector<vector<int>> grid2 {{1,1,3},{3,2,2},{1,1,4}};
    vector<vector<int>> grid3 {{1,2},{4,3}};
    vector<vector<int>> grid4 {{3,4,3},{2,2,2},{2,1,1},{4,3,2},{2,1,4},{2,4,1},{3,3,3},{1,4,2},{2,2,1},{2,1,1},{3,3,1},{4,1,4},{2,1,4},{3,2,2},{3,3,1},{4,4,1},{1,2,2},{1,1,1},{1,3,4},{1,2,1},{2,2,4},{2,1,3},{1,2,1},{4,3,2},{3,3,4},{2,2,1},{3,4,3},{4,2,3},{4,4,4}};

    cout << minCost(grid1) << '\n';
    cout << minCost(grid2) << '\n';
    cout << minCost(grid3) << '\n';
    cout << minCost(grid4) << '\n';

    return 0;
}
