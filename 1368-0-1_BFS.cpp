#include <deque>
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

#define AT(x, y, cols) ((x) * cols + y)

struct Cell
{
    unsigned char row;
    unsigned char col;

    Cell(
        unsigned char _row = 0,
        unsigned char _col = 0
    ) :
        row(_row), col(_col)
    {}
};

unsigned char dist[10000];

int minCost(vector<vector<int>>& grid)
{
    size_t m {grid.size()};
    size_t n {grid[0].size()};

    deque<Cell> bfs;

    Cell temp;
    unsigned char sum;
    unsigned char current;
    bool is_direction;

    memset(dist, -1, m * n * sizeof(unsigned char));
    dist[0] = static_cast<unsigned char>(0);
    bfs.emplace_front(0, 0);

    while (!bfs.empty())
    {
        temp = bfs.front();
        bfs.pop_front();

        if (temp.row == m - 1 && temp.col == n - 1)
        {
            break;
        }

        current = dist[AT(temp.row, temp.col, n)];

        if (temp.row > 0)
        {
            is_direction = grid[temp.row][temp.col] != 4;
            sum = current + static_cast<unsigned char>(is_direction);

            if (dist[AT(temp.row - 1, temp.col, n)] > sum)
            {
                dist[AT(temp.row - 1, temp.col, n)] = sum;

                if (is_direction)
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
            is_direction = grid[temp.row][temp.col] != 3;
            sum = current + static_cast<unsigned char>(is_direction);

            if (dist[AT(temp.row + 1,temp.col, n)] > sum)
            {
                dist[AT(temp.row + 1,temp.col, n)] = sum;

                if (is_direction)
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
            is_direction = grid[temp.row][temp.col] != 2;
            sum = current + static_cast<unsigned char>(is_direction);

            if (dist[AT(temp.row, temp.col - 1, n)] > sum)
            {
                dist[AT(temp.row, temp.col - 1, n)] = sum;

                if (is_direction)
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
            is_direction = grid[temp.row][temp.col] != 1;
            sum = current + static_cast<unsigned char>(is_direction);

            if (dist[AT(temp.row, temp.col + 1, n)] > sum)
            {
                dist[AT(temp.row, temp.col + 1, n)] = sum;

                if (is_direction)
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

    return dist[m * n - 1];
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
