#include <queue>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

/*
    A city is represented as a bi-directional connected graph with n vertices
where each vertex is labeled from 1 to n (inclusive). The edges in the graph
are represented as a 2D integer array edges, where each edges[i] = [ui, vi]
denotes a bi-directional edge between vertex ui and vertex vi. Every vertex
pair is connected by at most one edge, and no vertex has an edge to itself.
The time taken to traverse any edge is time minutes.

    Each vertex has a traffic signal which changes its color from green to
red and vice versa every change minutes. All signals change at the same time.
You can enter a vertex at any time, but can leave a vertex only when the signal
is green. You cannot wait at a vertex if the signal is green.

    The second minimum value is defined as the smallest value strictly
larger than the minimum value.

    - For example the second minimum value of [2, 3, 4] is 3, and the second
      minimum value of [2, 2, 4] is 4.

    Given n, edges, time, and change, return the second minimum time it will
take to go from vertex 1 to vertex n.

Notes:

    - You can go through any vertex any number of times, including 1 and n.
    - You can assume that when the journey starts, all signals have just
      turned green.

*/

constexpr unsigned int maxInt {static_cast<unsigned int>(-1)};

vector<vector<short>> adjList;

unsigned int dist1 [10000];
unsigned int dist2 [10000];

struct Vertex
{
    short node;
    unsigned int len;

    Vertex(
        short _node = 0,
        unsigned int _len = 0u
    ) :
        node(_node), len(_len)
    {}
};

int secondMinimum(int n, vector<vector<int>>& edges, int time, int change)
{
    queue<Vertex> bfs;

    Vertex temp;

    size_t i;
    size_t size {edges.size()};

    short timeToChange;
    unsigned int sum;

    adjList.clear();
    adjList.resize(n);

    for (i = 0; i < size; ++i)
    {
        adjList[edges[i][0] - 1].emplace_back(static_cast<short>(edges[i][1] - 1));
        adjList[edges[i][1] - 1].emplace_back(static_cast<short>(edges[i][0] - 1));
    }

    memset(dist1, maxInt, n * sizeof(unsigned int));
    memset(dist2, maxInt, n * sizeof(unsigned int));
    bfs.emplace(0, 0);
    dist1[0] = 0;

    while (!bfs.empty())
    {
        temp = bfs.front();
        bfs.pop();

        size = adjList[temp.node].size();

        for (i = 0; i < size; ++i)
        {
            sum = temp.len + time;

            if (dist1[adjList[temp.node][i]] <= sum)
            {
                if (
                    dist2[adjList[temp.node][i]] > sum &&
                    dist1[adjList[temp.node][i]] < sum
                )
                {
                    dist2[adjList[temp.node][i]] = sum;

                    if (adjList[temp.node][i] == n - 1)
                    {
                        return sum;
                    }
                }
                else
                {
                    continue;
                }
            }
            else
            {
                dist1[adjList[temp.node][i]] = sum;
            }


            timeToChange = 0;
            if (((temp.len + time) / change) % 2 == 1)
            {
                
                timeToChange = change - (temp.len + time) % change;
            }

            bfs.emplace(
                adjList[temp.node][i],
                sum + timeToChange
            );
        }
    }

    return dist2[n - 1];
}

int main()
{
    int n1 {5};
    vector<vector<int>> edges1 {{1,2},{1,3},{1,4},{3,4},{4,5}};
    int time1 {3};
    int change1 {5};
    
    int n2 {2};
    vector<vector<int>> edges2 {{1,2}};
    int time2 {3};
    int change2 {2};

    cout << secondMinimum(n1, edges1, time1, change1) << '\n';
    cout << secondMinimum(n2, edges2, time2, change2) << '\n';

    return 0;
}
