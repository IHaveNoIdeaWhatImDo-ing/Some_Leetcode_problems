#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

/*
You are given an m x n binary matrix grid and an integer health.

    You start on the upper-left corner (0, 0) and would like to
get to the lower-right corner (m - 1, n - 1).

    You can move up, down, left, or right from one cell to another
adjacent cell as long as your health remains positive.

    Cells (i, j) with grid[i][j] = 1 are considered unsafe and
reduce your health by 1.

    Return true if you can reach the final cell with a health
value of 1 or more, and false otherwise.
*/

static inline int AT(size_t row, size_t col, size_t n)
{
    return static_cast<int>(row * n + col);
}

short dist[2500];

struct comp
{
    bool operator() (int l, int r) const
    {
        return (l & 0xFFFF) < (r & 0xFFFF);
    }
};

bool findSafeWalk(vector<vector<int>>& grid, int health)
{
    ios_base::sync_with_stdio();
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t m {grid.size()};
    size_t n {grid[0].size()};
    short last {static_cast<short>(m * n - 1)};

    size_t i;
    size_t j;
    short hp;

    priority_queue<int, vector<int>, comp> pq;

    int temp {static_cast<int>(health - grid[0][0])};
    short current;

    int index;

    memset(dist, 0x0, m * n * sizeof(short));
    dist[0] = static_cast<short>(temp);

    pq.emplace(temp);

    while (!pq.empty())
    {
        temp = pq.top();
        pq.pop();

        i = static_cast<size_t>(temp) >> 24; // eldest byte
        j = static_cast<size_t>(temp & 0xFFFFFF) >> 16; // second last byte

        if (i > 0)
        {
            current = dist[AT(i, j, n)] - grid[i - 1][j];
            index = AT(i - 1, j, n);

            if (dist[index] < current && current > 0)
            {
                if (index == last)
                {
                    return true;
                }

                dist[index] = current;

                temp =  static_cast<int>(i - 1) << 24;
                temp += static_cast<int>(j) << 16;
                temp += static_cast<int>(current);

                pq.emplace(temp);
            }
        }

        if (i < m - 1)
        {
            current = dist[AT(i, j, n)] - grid[i + 1][j];
            index = AT(i + 1, j, n);

            if (dist[index] < current && current > 0)
            {
                if (index == last)
                {
                    return true;
                }

                dist[index] = current;

                temp =  static_cast<int>(i + 1) << 24;
                temp += static_cast<int>(j) << 16;
                temp += static_cast<int>(current);

                pq.emplace(temp);
            }
        }

        if (j > 0)
        {
            current = dist[AT(i, j, n)] - grid[i][j - 1];
            index = AT(i, j - 1, n);

            if (dist[index] < current && current > 0)
            {
                if (index == last)
                {
                    return true;
                }

                dist[index] = current;

                temp =  static_cast<int>(i) << 24;
                temp += static_cast<int>(j - 1) << 16;
                temp += static_cast<int>(current);

                pq.emplace(temp);
            }
        }

        if (j < n - 1)
        {
            current = dist[AT(i, j, n)] - grid[i][j + 1];
            index = AT(i, j + 1, n);

            if (dist[index] < current && current > 0)
            {
                if (index == last)
                {
                    return true;
                }

                dist[index] = current;

                temp =  static_cast<int>(i) << 24;
                temp += static_cast<int>(j + 1) << 16;
                temp += static_cast<int>(current);

                pq.emplace(temp);
            }
        }
    }

    return false;
}

int main()
{
    vector<vector<int>> grid1 = {{0,1,0,0,0},{0,1,0,1,0},{0,0,0,1,0}};
    int health1 {1};
    
    vector<vector<int>> grid2 = {{0,1,1,0,0,0},{1,0,1,0,0,0},{0,1,1,1,0,1},{0,0,1,0,1,0}};
    int health2 {3};
    
    vector<vector<int>> grid3 = {{1,1,1},{1,0,1},{1,1,1}};
    int health3 {5};
    
    cout << boolalpha << findSafeWalk(grid1, health1) << '\n';
    cout << boolalpha << findSafeWalk(grid2, health2) << '\n';
    cout << boolalpha << findSafeWalk(grid3, health3) << '\n';

    return 0;
}
