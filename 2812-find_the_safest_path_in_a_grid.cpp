#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

/*
You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:

    A cell containing a thief if grid[r][c] = 1
    An empty cell if grid[r][c] = 0

    You are initially positioned at cell (0, 0). In one move, you can move to any
adjacent cell in the grid, including cells containing thieves.

    The safeness factor of a path on the grid is defined as the minimum manhattan
distance from any cell in the path to any thief in the grid.

Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).

    An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1),
(r + 1, c) and (r - 1, c) if it exists.

    The Manhattan distance between two cells (a, b) and (x, y) is equal to
|a - x| + |b - y|, where |val| denotes the absolute value of val.
*/

static inline size_t AT(size_t row, size_t col, size_t n)
{
    return row * n + col;
}

short dist[160000];

struct Path
{
    int index;
    short maxPathSafeness;

    Path(int _index = 0, short _maxPathSafeness = 0) :
        index(_index), maxPathSafeness(_maxPathSafeness)
    {}
};

struct comp
{
    bool operator() (const Path& l, const Path& r) const
    {
        return l.maxPathSafeness < r.maxPathSafeness;
    }
};

void manDistBFS(vector<vector<int>>& grid)
{
    size_t n = grid.size();

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

        i = static_cast<size_t>(temp) >> 16;
        j = static_cast<size_t>(temp & 0xFFFF); // lower 2 bytes

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
}

int maximumSafenessFactor(vector<vector<int>>& grid)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    size_t n {grid.size()};

    size_t i;
    size_t j;

    priority_queue<Path, vector<Path>, comp> pq;

    Path temp;
    int indexToAdd;
    short current;

    memset(dist, 0x0, n * n);

    manDistBFS(grid);

    pq.emplace(0, static_cast<short>(grid[0][0]));
    dist[0] = static_cast<short>(grid[0][0]);

    while (!pq.empty())
    {
        temp = pq.top();
        pq.pop();

        i = static_cast<size_t>(temp.index) >> 16;
        j = static_cast<size_t>(temp.index & 0xFFFF);

        if (i > 0)
        {
            current = min(dist[AT(i, j, n)], static_cast<short>(grid[i - 1][j]));

            if (current > dist[AT(i - 1, j, n)])
            {
                dist[AT(i - 1, j, n)] = current;

                if (i - 1 == n - 1 && j == n - 1)
                {
                    break;
                }

                indexToAdd =  static_cast<int>(i - 1) << 16;
                indexToAdd += static_cast<int>(j);
                pq.emplace(indexToAdd, current);
            }
        }
        
        if (i < n - 1)
        {
            current = min(dist[AT(i, j, n)], static_cast<short>(grid[i + 1][j]));

            if (current > dist[AT(i + 1, j, n)])
            {
                dist[AT(i + 1, j, n)] = current;

                if (i + 1 == n - 1 && j == n - 1)
                {
                    break;
                }

                indexToAdd =  static_cast<int>(i + 1) << 16;
                indexToAdd += static_cast<int>(j);
                pq.emplace(indexToAdd, current);
            }
        }
        
        if (j > 0)
        {
            current = min(dist[AT(i, j, n)], static_cast<short>(grid[i][j - 1]));

            if (current > dist[AT(i, j - 1, n)])
            {
                dist[AT(i, j - 1, n)] = current;

                if (i == n - 1 && j - 1 == n - 1)
                {
                    break;
                }

                indexToAdd =  static_cast<int>(i) << 16;
                indexToAdd += static_cast<int>(j - 1);
                pq.emplace(indexToAdd, current);
            }
        }
        
        if (j < n - 1)
        {
            current = min(dist[AT(i, j, n)], static_cast<short>(grid[i][j + 1]));

            if (current > dist[AT(i, j + 1, n)])
            {
                dist[AT(i, j + 1, n)] = current;

                if (i == n - 1 && j + 1 == n - 1)
                {
                    break;
                }

                indexToAdd =  static_cast<int>(i) << 16;
                indexToAdd += static_cast<int>(j + 1);
                pq.emplace(indexToAdd, current);
            }
        }
    }

    return static_cast<int>(dist[AT(n - 1, n - 1, n)]) - 1;
}

int main()
{
    vector<vector<int>> grid1 = {{1,0,0},{0,0,0},{0,0,1}};
    vector<vector<int>> grid2 = {{0,0,1},{0,0,0},{0,0,0}};
    vector<vector<int>> grid3 = {{0,0,0,1},{0,0,0,0},{0,0,0,0},{1,0,0,0}};
    vector<vector<int>> grid4 = {{0,1,1},{0,0,1},{1,0,0}};

    cout << maximumSafenessFactor(grid1) << '\n';
    cout << maximumSafenessFactor(grid2) << '\n';
    cout << maximumSafenessFactor(grid3) << '\n';
    cout << maximumSafenessFactor(grid4) << '\n';

    return 0;
}
