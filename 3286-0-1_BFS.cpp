#include <iostream>
#include <cstring>
#include <vector>
#include <deque>

using namespace std;

static inline short AT(size_t row, size_t col, size_t n)
{
    return static_cast<short>(row * n + col);
}

bool visited[2500];

bool findSafeWalk(vector<vector<int>>& grid, int health)
{
    ios_base::sync_with_stdio();
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    size_t m {grid.size()};
    size_t n {grid[0].size()};

    if ((grid[0][0] == 1 || grid[m - 1][n - 1] == 1) && health == 1)
    {
        return false;
    }

    size_t i;
    size_t j;

    int last {static_cast<int>(m * n - 1)};

    deque<int> dial;

    int current;
    int temp;
    int index;

    memset(visited, 0x0, m * n * sizeof(bool));
    visited[0] = true;
    
    dial.emplace_back(health - grid[0][0]);

    while (!dial.empty())
    {
        current = dial.front();
        dial.pop_front();

        i = static_cast<size_t>(current) >> 24;
        j = static_cast<size_t>(current & 0xFF0000) >> 16;

        if (i == m - 1 && j == n - 1)
        {
            return true;
        }

        if (i > 0)
        {
            index = AT(i - 1, j, n);

            if (!visited[index])
            {
                visited[index] = true;

                temp =  static_cast<int>(i - 1) << 24;
                temp += static_cast<int>(j) << 16;
                temp += current & 0xFFFF;

                if (grid[i - 1][j] == 0)
                {
                    dial.emplace_front(temp);
                }
                else if ((current & 0xFFFF) > 1)
                {
                    dial.emplace_back(temp - 1);
                }
            }
        }

        if (i < m - 1)
        {
            index = AT(i + 1, j, n);

            if (!visited[index])
            {
                visited[index] = true;

                temp =  static_cast<int>(i + 1) << 24;
                temp += static_cast<int>(j) << 16;
                temp += current & 0xFFFF;

                if (grid[i + 1][j] == 0)
                {
                    dial.emplace_front(temp);
                }
                else if ((current & 0xFFFF) > 1)
                {
                    dial.emplace_back(temp - 1);
                }
            }
        }

        if (j > 0)
        {
            index = AT(i, j - 1, n);

            if (!visited[index])
            {
                visited[index] = true;

                temp =  static_cast<int>(i) << 24;
                temp += static_cast<int>(j - 1) << 16;
                temp += current & 0xFFFF;

                if (grid[i][j - 1] == 0)
                {
                    dial.emplace_front(temp);
                }
                else if ((current & 0xFFFF) > 1)
                {
                    dial.emplace_back(temp - 1);
                }
            }
        }

        if (j < n - 1)
        {
            index = AT(i, j + 1, n);

            if (!visited[index])
            {
                visited[index] = true;

                temp =  static_cast<int>(i) << 24;
                temp += static_cast<int>(j + 1) << 16;
                temp += current & 0xFFFF;

                if (grid[i][j + 1] == 0)
                {
                    dial.emplace_front(temp);
                }
                else if ((current & 0xFFFF) > 1)
                {
                    dial.emplace_back(temp - 1);
                }
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
