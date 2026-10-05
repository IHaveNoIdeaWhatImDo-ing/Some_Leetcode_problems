#include <queue>
#include <vector>
#include <iostream>

using namespace std;

/*
    You are given two integers, n and threshold, as well as a directed weighted graph
of n nodes numbered from 0 to n - 1. The graph is represented by a 2D integer array
edges, where edges[i] = [Ai, Bi, Wi] indicates that there is an edge going from node
Ai to node Bi with weight Wi.

    You have to remove some edges from this graph (possibly none), so that it satisfies
the following conditions:

    Node 0 must be reachable from all other nodes.
    The maximum edge weight in the resulting graph is minimized.
    Each node has at most threshold outgoing edges.

    Return the minimum possible value of the maximum edge weight after removing the
necessary edges. If it is impossible for all conditions to be satisfied, return -1.
*/

struct Edge
{
    int node;
    int weight;

    Edge(int node = 0, int weight = 0) :
        node(node), weight(weight)
    {}
};

struct comp
{
    bool operator() (const Edge& l, const Edge& r) const
    {
        return l.weight > r.weight;
    }
};

constexpr int maxInt {static_cast<int>(~0u >> 1)};

int minMaxWeight(int n, vector<vector<int>>& edges, int threshold)
{
    int minMax {};

    vector<int> dist (n, maxInt);

    vector<vector<Edge>> adjList (n);

    size_t i {};
    size_t size {edges.size()};

    priority_queue<Edge, vector<Edge>, comp> pq;

    Edge temp;
    int bigger;

    dist[0] = 0;
    pq.emplace(0, 0);

    for (; i < size; ++i)
    {
        adjList[edges[i][1]].emplace_back(
            edges[i][0],
            edges[i][2]
        );
    }

    while (!pq.empty())
    {
        temp = pq.top();
        pq.pop();

        if (temp.weight > dist[temp.node])
        {
            continue;
        }

        //cout << temp.node << ", " << temp.weight << '\n';

        size = adjList[temp.node].size();

        for (i = 0; i < size; ++i)
        {
            bigger = max(temp.weight, adjList[temp.node][i].weight);

            if (bigger >= dist[adjList[temp.node][i].node])
            {
                continue;
            }

            //cout << adjList[temp.node][i].node << ", " << adjList[temp.node][i].weight << " added\n";

            dist[adjList[temp.node][i].node] = bigger;

            pq.emplace(
                adjList[temp.node][i].node,
                bigger
            );
        }
    }

    //cout << '\n';

    size = static_cast<size_t>(n);
    for (i = 1; i < size; ++i)
    {
        //cout << i << " : " << dist[i] << '\n';

        if (dist[i] == maxInt)
        {
            return -1;
        }
        else if (dist[i] > minMax)
        {
            minMax = dist[i];
        }
    }

    return minMax;
}

int main()
{
    int n1 {5};
    vector<vector<int>> edges1 {{1,0,1},{2,0,2},{3,0,1},{4,3,1},{2,1,1}};
    int threshold1 {2};
    
    int n2 {5};
    vector<vector<int>> edges2 {{0,1,1},{0,2,2},{0,3,1},{0,4,1},{1,2,1},{1,4,1}};
    int threshold2 {1};
    
    int n3 {5};
    vector<vector<int>> edges3 {{1,2,1},{1,3,3},{1,4,5},{2,3,2},{3,4,2},{4,0,1}};
    int threshold3 {1};
    
    int n4 {5};
    vector<vector<int>> edges4 {{1,2,1},{1,3,3},{1,4,5},{2,3,2},{4,0,1}};
    int threshold4 {1};
    
    int n5 {3};
    vector<vector<int>> edges5 {{2,0,83},{1,0,22},{0,1,64}};
    int threshold5 {1};
    
    int n6 {4};
    vector<vector<int>> edges6 {{3,2,24},{3,0,92},{2,1,8},{3,2,87},{1,3,20}};
    int threshold6 {3};

    cout << minMaxWeight(n1, edges1, threshold1) << '\n';
    cout << minMaxWeight(n2, edges2, threshold2) << '\n';
    cout << minMaxWeight(n3, edges3, threshold3) << '\n';
    cout << minMaxWeight(n4, edges4, threshold4) << '\n';
    cout << minMaxWeight(n5, edges5, threshold5) << '\n';
    cout << minMaxWeight(n6, edges6, threshold6) << '\n';

    return 0;
}
