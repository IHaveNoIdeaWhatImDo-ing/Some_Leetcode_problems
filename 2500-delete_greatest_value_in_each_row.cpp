#include <vector>
#include <cstddef>
#include <iostream>
#include <algorithm>

using namespace std;

int deleteGreatestValue(vector<vector<int>>& grid)
{
    int res {};
    int max {};
    int rows {static_cast<int>(grid.size())};
    int cols {static_cast<int>(grid[0].size())};

    for (vector<int>& row : grid)
    {
        make_heap(row.begin(), row.end());
    }
    
    for (int i {}; i < cols; ++i)
    {
        max = 1 << (sizeof(int) * 8 - 1) ^ 0;

        for (int j {}; j < rows; ++j)
        {
            if (grid[j][0] > max)
            {
                max = grid[j][0];
            }

            pop_heap(grid[j].begin(), grid[j].end() - i);
        }

        res += max;
    }

    return res;
}

int main()
{
    vector<vector<int>> grid1 = {{1,2,4},{3,3,1}};
    vector<vector<int>> grid2 = {{10}};

    cout << deleteGreatestValue(grid1) << '\n';
    cout << deleteGreatestValue(grid2) << '\n';

    return 0;
}
