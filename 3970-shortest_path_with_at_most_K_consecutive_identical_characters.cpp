#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

/*
    You are given an integer n representing the number of nodes in a directed
weighted graph, numbered from 0 to n - 1. This is represented by a 2D integer
array edges, where edges[i] = [ui, vi, wi] represents a directed edge from
node ui to node vi with weight wi.

    You are also given a string labels of length n, where labels[i] is the
character assigned to node i, and an integer k.

    Return the minimum total edge weight of a path from node 0 to node n - 1
such that the concatenation of the labels of the nodes along the path contains
at most k consecutive identical characters. If no valid path exists, return -1.
*/

unsigned int dist[50000][50];

struct Edge
{
    unsigned short node;
    short repeats;
    int weight;

    Edge(unsigned short _node = 0, short _repeats = 0, int _weight = 0) :
        node(_node), repeats(_repeats), weight(_weight)
    {}
};

struct comp
{
    bool operator() (const Edge& l, const Edge& r) const
    {
        return l.weight > r.weight;
    }
};

int shortestPath(int n, vector<vector<int>>& edges, const string& labels, int k)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    unsigned int res {~0u};

    size_t size {edges.size()};

    size_t i;

    vector<vector<Edge>> adjList(n);

    priority_queue<Edge, vector<Edge>, comp> pq;

    Edge temp;
    int currentDist;
    short currentRepeats;

    memset(dist, 0xFF, n * 50 * sizeof(unsigned int));
    dist[0][0] = 0u;

    --k;

    pq.emplace(
        static_cast<unsigned short>(0),
        static_cast<short>(0),
        0
    );

    for (i = 0; i < size; ++i)
    {
        adjList[edges[i][0]].emplace_back(
            static_cast<unsigned short>(edges[i][1]),
            static_cast<short>(0),
            edges[i][2]
        );
    }

    while (!pq.empty())
    {
        temp = pq.top();
        pq.pop();

        if (temp.node == n - 1)
        {
            break;
        }

        size = adjList[temp.node].size();

        for (i = 0; i < size; ++i)
        {
            currentDist = static_cast<int>(temp.weight) + adjList[temp.node][i].weight;
            currentRepeats = labels[temp.node] == labels[adjList[temp.node][i].node] ? temp.repeats + 1 : 0;

            if (
                currentRepeats <= k &&
                dist[adjList[temp.node][i].node][currentRepeats] > currentDist
            )
            {
                dist[adjList[temp.node][i].node][currentRepeats] = currentDist;

                pq.emplace(
                    static_cast<unsigned short>(adjList[temp.node][i].node),
                    currentRepeats,
                    currentDist
                );
            }
        }
    }

    size = static_cast<int>(k + 1);

    for (i = 0; i < size; ++i)
    {
        if (dist[n - 1][i] < res)
        {
            res = dist[n - 1][i];
        }
    }

    return static_cast<int>(res);
}

int main()
{
    int n1 {3};
    vector<vector<int>> edges1 = {{0,1,1},{1,2,1},{0,2,3}};
    string labels1("aab");
    int k1 {1};
    
    int n2 {3};
    vector<vector<int>> edges2 = {{0,1,1},{1,2,1},{0,2,3}};
    string labels2("aab");
    int k2 {2};
    
    int n3 {3};
    vector<vector<int>> edges3 = {{0,1,1},{1,2,1}};
    string labels3("aaa");
    int k3 {2};
    
    int n4 {3};
    vector<vector<int>> edges4 = {{1,2,8426},{0,1,9},{1,2,4}};
    string labels4("aba");
    int k4 {1};
    
    int n5 {4};
    vector<vector<int>> edges5 = {{0,1,1},{0,2,10},{1,2,1},{2,3,1}};
    string labels5("aaaa");
    int k5 {3};

    cout << shortestPath(n1, edges1, labels1, k1) << '\n';
    cout << shortestPath(n2, edges2, labels2, k2) << '\n';
    cout << shortestPath(n3, edges3, labels3, k3) << '\n';
    cout << shortestPath(n4, edges4, labels4, k4) << '\n';
    cout << shortestPath(n5, edges5, labels5, k5) << '\n';

    return 0;
}
