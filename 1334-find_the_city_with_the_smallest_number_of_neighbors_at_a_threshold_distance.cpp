#include <queue>
#include <vector>
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

struct Edge
{
    unsigned char node;
    int weight;

    Edge(unsigned char node = 0, int weight = 0) :
        node(node), weight(weight)
    {}
};

struct
{
    bool operator()
    (
        const Edge& l,
        const Edge& r
    ) const
    {
        return l.weight > r.weight;
    }
} comp;

int djikstra
(
    unsigned char start,
    vector<bool>& visited,
    const vector<vector<Edge>>& edgeList,
    int distanceThreshold
)
{
    Edge temp {};

    size_t i {};
    size_t size {};

    priority_queue<Edge, vector<Edge>, decltype(comp)> pq (comp);
    pq.emplace(start, 0);

    int reachable {};

    while (!pq.empty())
    {
        temp = pq.top();
        pq.pop();

        if (!visited[temp.node])
        {
            visited[temp.node] = true;
            ++reachable;

            size = edgeList[temp.node].size();

            for (i = 0; i < size; ++i)
            {
                if
                (
                    !visited[edgeList[temp.node][i].node] &&
                    edgeList[temp.node][i].weight + temp.weight <= distanceThreshold
                )
                {
                    pq.emplace(
                        edgeList[temp.node][i].node,
                        edgeList[temp.node][i].weight + temp.weight
                    );
                }
            }
        }
    }

    return reachable;
}

void reset(vector<bool>& vec)
{
    for (size_t i {}, size = vec.size(); i < size; ++i)
    {
        vec[i] = false;
    }
}

int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold)
{
    vector<vector<Edge>> edgeList (n);

    size_t i {};
    size_t size {edges.size()};

    int city {};
    int minLen {static_cast<int>(~0u >> 1)};
    int temp {};

    vector<bool> visited (n);

    for (; i < size; ++i)
    {
        edgeList[edges[i][0]].emplace_back(
            static_cast<unsigned char>(edges[i][1]),
            edges[i][2]
        );
        edgeList[edges[i][1]].emplace_back(
            static_cast<unsigned char>(edges[i][0]),
            edges[i][2]
        );
    }

    for (i = 0; i < n; ++i)
    {
        temp = djikstra
        (
            static_cast<unsigned char>(i),
            visited,
            edgeList,
            distanceThreshold
        );

        if
        (
             temp <  minLen ||
            (temp == minLen && city < i)
        )
        {
            minLen = temp;
            city = static_cast<int>(i);
        }

        reset(visited);
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
