#include <array>
#include <vector>
#include <utility>
#include <cstddef>
#include <iostream>
#include <algorithm>

using namespace std;

long long maximumImportance(int n, vector<vector<int>>& roads)
{
    // <index, roads, fame>
    vector<array<unsigned short, 3>> temp(n);
    vector<array<unsigned short, 3>> city_road_count(n);
    long long res {};

    unsigned short i {};
    unsigned short fame {static_cast<unsigned short>(n)};
    unsigned short road_count {static_cast<unsigned short>(roads.size())};

    for (; i < n; ++i)
    {
        temp[i][0] = i;
    }

    for (i = 0; i < road_count; ++i)
    {
        ++temp[roads[i][0]][1];
        ++temp[roads[i][1]][1];
    }

    sort
    (
        temp.begin(), temp.end(),
        []
        (
            const array<unsigned short, 3>& l,
            const array<unsigned short, 3>& r
        )
        {
            return l[1] > r[1];
        }
    );

    for (i = 0; i < n; ++i, --fame)
    {
        temp[i][2] = fame;
        city_road_count[temp[i][0]] = move(temp[i]);
    }

    for (i = 0; i < road_count; ++i)
    {
        res += city_road_count[roads[i][0]][2] + city_road_count[roads[i][1]][2];
    }

    return res;
}

int main()
{
    int n1 = 5;
    vector<vector<int>> roads1 = {{0,1},{1,2},{2,3},{0,2},{1,3},{2,4}};

    cout << maximumImportance(n1, roads1) << '\n';

    return 0;
}
