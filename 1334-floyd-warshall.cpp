#include <queue>
#include <vector>
#include <iomanip>
#include <iostream>

using namespace std;

/*
    There are n cities numbered from 0 to n-1. Given the array edges where
edges[i] = [from_i, to_i, weight_i] represents a bidirectional and weighted edge
between cities fromi and toi, and given the integer distanceThreshold.

    Return the city with the smallest number of cities that are reachable
through some path and whose distance is at most distanceThreshold, If there
are multiple such cities, return the city with the greatest number.

    Notice that the distance of a path connecting cities i and j is equal to
the sum of the edges' weights along that path.

    - 2 <= n <= 100
    - 1 <= edges.length <= n * (n - 1) / 2
    - edges[i].length == 3
    - 0 <= from_i < to_i < n
    - 1 <= weight_i, distanceThreshold <= 10^4
    - All pairs (from_i, to_i) are distinct.
*/

void printMat(const vector<vector<unsigned short>>& mat)
{
    for (const vector<unsigned short>& row : mat)
    {
        for (unsigned short num : row)
        {
            cout << setw(5) << num  << ' ';
        }
        cout << '\n';
    }
}

int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold)
{
    constexpr int iMax {~0u >> 1};

    int i {};
    int j {};
    int k {};
    int size = static_cast<int>(edges.size());

    int city {-1};
    int minLen {iMax};
    int tmpLen {iMax};

    vector<vector<int>> adjMat (n, vector<int>(n, iMax));

    for (; i < n; ++i)
    {
        adjMat[i][i] = 0;
    }

    for (i = 0; i < size; ++i)
    {
        adjMat[edges[i][0]][edges[i][1]] = edges[i][2];
        adjMat[edges[i][1]][edges[i][0]] = edges[i][2];
    }

    for (; k < n; ++k)
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                if (adjMat[i][k] != iMax && adjMat[k][j] != iMax)
                {
                    adjMat[i][j] = min(
                        adjMat[i][j],
                        adjMat[i][k] + adjMat[k][j]
                    );
                }
            }
        }
    }

    for (i = 0; i < n; ++i)
    {
        tmpLen = 0;
        
        for (j = 0; j < n; ++j)
        {
            if (adjMat[i][j] <= distanceThreshold)
            {
                ++tmpLen;
            }
        }

        if (tmpLen <= minLen)
        {
            minLen = tmpLen;
            city = i;
        }
    }

    return city;
}

int main()
{
    int n1 {4};
    vector<vector<int>> edges1 {{0,1,3},{1,2,1},{1,3,4},{2,3,1}};
    int distanceThreshold1 {4};
    
    int n2 {5};
    vector<vector<int>> edges2 {{0,1,2},{0,4,8},{1,2,3},{1,4,2},{2,3,1},{3,4,1}};
    int distanceThreshold2 {2};
    
    int n3 {6};
    vector<vector<int>> edges3 {{0,1,10},{0,2,1},{2,3,1},{1,3,1},{1,4,1},{4,5,10}};
    int distanceThreshold3 {20};

    cout << findTheCity(n1, edges1, distanceThreshold1) << '\n';
    cout << findTheCity(n2, edges2, distanceThreshold2) << '\n';
    cout << findTheCity(n3, edges3, distanceThreshold3) << '\n';

    return 0;
}
