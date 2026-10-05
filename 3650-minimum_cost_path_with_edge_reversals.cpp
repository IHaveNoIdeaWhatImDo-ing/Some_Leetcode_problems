#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
    You are given a directed, weighted graph with n nodes labeled from 0 to n - 1,
and an array edges where edges[i] = [ui, vi, wi] represents a directed edge from node
ui to node vi with cost wi.

    Each node ui has a switch that can be used at most once: when you arrive at ui and
have not yet used its switch, you may activate it on one of its incoming edges vi → ui
reverse that edge to ui → vi and immediately traverse it.

    The reversal is only valid for that single move, and using a reversed edge
costs 2 * wi.

    Return the minimum total cost to travel from node 0 to node n - 1. If it is not
possible, return -1.
*/

struct Edge
{
    unsigned short node;
    unsigned int weight;

    Edge(unsigned short node = 0, unsigned int weight = 0u) :
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

int minCost(int n, vector<vector<int>>& edges)
{
    vector<vector<Edge>> edgeList (n);

    priority_queue<Edge, vector<Edge>, comp> pq;

    vector<bool> visited (n);

    size_t i {};
    size_t size {edges.size()};
    Edge temp {};

    for (; i < size; ++i)
    {
        edgeList[edges[i][0]].emplace_back(
            static_cast<unsigned short>(edges[i][1]),
            edges[i][2]
        );
        edgeList[edges[i][1]].emplace_back(
            static_cast<unsigned short>(edges[i][0]),
            edges[i][2] * 2
        );
    }

    pq.emplace(0, 0u);

    while (!pq.empty())
    {
        temp = pq.top();

        if (temp.node == static_cast<unsigned short>(n - 1))
        {
            return temp.weight;
        }

        pq.pop();

        if (!visited[temp.node])
        {
            visited[temp.node] = true;

            size = edgeList[temp.node].size();

            for (i = 0; i < size; ++i)
            {
                pq.emplace(
                    edgeList[temp.node][i].node,
                    edgeList[temp.node][i].weight + temp.weight
                );
            }
        }
    }

    return -1;
}

int main()
{
    int n1 {4};
    vector<vector<int>> edges1 = {{0,1,3},{3,1,1},{2,3,4},{0,2,2}};
    
    int n2 {4};
    vector<vector<int>> edges2 = {{0,2,1},{2,1,1},{1,3,1},{2,3,3}};

    cout << minCost(n1, edges1) << '\n';
    cout << minCost(n2, edges2) << '\n';

    return 0;
}
