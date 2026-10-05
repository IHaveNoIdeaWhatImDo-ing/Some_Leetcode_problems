#include <vector>
#include <iostream>

using namespace std;

/*
    There is an undirected star graph consisting of n nodes labeled from 1 to n.
A star graph is a graph where there is one center node and exactly n - 1 edges
that connect the center node with every other node.

    You are given a 2D integer array edges where each edges[i] = [ui, vi] indicates
that there is an edge between the nodes ui and vi. Return the center of the given star graph.
*/

int findCenter(vector<vector<int>>& edges)
{
    int i {};
    int n {static_cast<int>(edges.size()) + 1};

    vector<int> node_edges_amount(n);
    
    for (const vector<int>& edge : edges)
    {
        ++node_edges_amount[edge[0] - 1];
        ++node_edges_amount[edge[1] - 1];
    }

    for (; i < n; ++i)
    {
        if (node_edges_amount[i] == n - 1)
        {
            return i + 1;
        }
    }

    return 0;
}

int main()
{
    vector<vector<int>> edges1 = {{1,2},{5,1},{1,3},{1,4}};
    vector<vector<int>> edges2 = {{1,2},{2,3},{4,2}};

    cout << findCenter(edges1) << '\n';
    cout << findCenter(edges2) << '\n';

    return 0;
}
