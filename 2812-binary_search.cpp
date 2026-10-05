#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

static inline int AT(size_t row, size_t col, size_t n)
{
    return static_cast<int>(row * n + col);
} 

bool visited[160000];

void manhattanDistMap(vector<vector<int>>& grid)
{
    size_t n {grid.size()};

    size_t i;
    size_t j;

    queue<int> bfs;

    int temp;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if (grid[i][j] == 1)
            {
                temp =  static_cast<int>(i) << 16;
                temp += static_cast<int>(j);

                bfs.emplace(temp);
            }
        }
    }

    while (!bfs.empty())
    {
        temp = bfs.front();
        bfs.pop();

        i = static_cast<size_t>(temp >> 16);
        j = static_cast<size_t>(temp & 0xFFFF);

        if (i > 0)
        {
            if (grid[i - 1][j] == 0 || grid[i - 1][j] > grid[i][j] + 1)
            {
                grid[i - 1][j] = grid[i][j] + 1;

                temp =  static_cast<int>(i - 1) << 16;
                temp += static_cast<int>(j);

                bfs.emplace(temp);
            }
        }

        if (i < n - 1)
        {
            if (grid[i + 1][j] == 0 || grid[i + 1][j] > grid[i][j] + 1)
            {
                grid[i + 1][j] = grid[i][j] + 1;

                temp =  static_cast<int>(i + 1) << 16;
                temp += static_cast<int>(j);

                bfs.emplace(temp);
            }
        }

        if (j > 0)
        {
            if (grid[i][j - 1] == 0 || grid[i][j - 1] > grid[i][j] + 1)
            {
                grid[i][j - 1] = grid[i][j] + 1;

                temp =  static_cast<int>(i) << 16;
                temp += static_cast<int>(j - 1);

                bfs.emplace(temp);
            }
        }

        if (j < n - 1)
        {
            if (grid[i][j + 1] == 0 || grid[i][j + 1] > grid[i][j] + 1)
            {
                grid[i][j + 1] = grid[i][j] + 1;

                temp =  static_cast<int>(i) << 16;
                temp += static_cast<int>(j + 1);

                bfs.emplace(temp);
            }
        }
    }

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            --grid[i][j];
        }
    }
}

bool isTraversable(const vector<vector<int>>& grid, int threshold)
{
    if (grid[0][0] < threshold)
    {
        return false;
    }

    size_t n {grid.size()};

    size_t i;
    size_t j;

    queue<int> bfs;

    int temp;
    int index;

    memset(visited, 0x0, n * n);

    bfs.emplace(0);
    visited[0] = true;

    while (!bfs.empty())
    {
        temp = bfs.front();
        bfs.pop();

        i = static_cast<size_t>(temp >> 16);
        j = static_cast<size_t>(temp & 0xFFFF);

        if (i > 0)
        {
            index = AT(i - 1, j, n);

            if (!visited[index] && grid[i - 1][j] >= threshold)
            {
                if (i - 1 == n - 1 && j == n - 1)
                {
                    return true;
                }
                
                visited[index] = true;

                temp =  static_cast<int>(i - 1) << 16;
                temp += static_cast<int>(j);

                bfs.emplace(temp);
            }
        }

        if (i < n - 1)
        {
            index = AT(i + 1, j, n);

            if (!visited[index] && grid[i + 1][j] >= threshold)
            {
                if (i + 1 == n - 1 && j == n - 1)
                {
                    return true;
                }

                visited[index] = true;

                temp =  static_cast<int>(i + 1) << 16;
                temp += static_cast<int>(j);

                bfs.emplace(temp);
            }
        }

        if (j > 0)
        {
            index = AT(i, j - 1, n);

            if (!visited[index] && grid[i][j - 1] >= threshold)
            {
                if (i == n - 1 && j - 1 == n - 1)
                {
                    return true;
                }

                visited[index] = true;

                temp =  static_cast<int>(i) << 16;
                temp += static_cast<int>(j - 1);

                bfs.emplace(temp);
            }
        }

        if (j < n - 1)
        {
            index = AT(i, j + 1, n);

            if (!visited[index] && grid[i][j + 1] >= threshold)
            {
                if (i == n - 1 && j + 1 == n - 1)
                {
                    return true;
                }

                visited[index] = true;
            
                temp =  static_cast<int>(i) << 16;
                temp += static_cast<int>(j + 1);

                bfs.emplace(temp);
            }
        }
    }

    return false;
}

int maximumSafenessFactor(vector<vector<int>>& grid)
{
    ios_base::sync_with_stdio();
    cin.tie(nullptr);
    cout.tie(nullptr);

    int res {-1};

    size_t n {grid.size()};

    if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
    {
        return 0;
    }

    int left {0};
    int right {static_cast<int>(n) << 1};
    int mid;

    manhattanDistMap(grid);

    while (left <= right)
    {
        mid = (left + right) / 2;

        bool possible = isTraversable(grid, mid);

        if (possible)
        {
            res = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return res;
}

int main()
{
    vector<vector<int>> grid1 = {{1,0,0},{0,0,0},{0,0,1}};
    vector<vector<int>> grid2 = {{0,0,1},{0,0,0},{0,0,0}};
    vector<vector<int>> grid3 = {{0,0,0,1},{0,0,0,0},{0,0,0,0},{1,0,0,0}};
    vector<vector<int>> grid4 = {{0,1,1},{0,0,1},{1,0,0}};
    vector<vector<int>> grid5 = {{0,1,1},{0,0,0},{0,0,0}};

    cout << maximumSafenessFactor(grid1) << '\n';
    cout << maximumSafenessFactor(grid2) << '\n';
    cout << maximumSafenessFactor(grid3) << '\n';
    cout << maximumSafenessFactor(grid4) << '\n';
    cout << maximumSafenessFactor(grid5) << '\n';

    return 0;
}
