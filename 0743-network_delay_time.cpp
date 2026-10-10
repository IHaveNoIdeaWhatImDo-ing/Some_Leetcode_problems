#include <queue>
#include <vector>
#include <cstdint>
#include <iostream>

using namespace std;

/*
    You are given a network of n nodes, labeled from 1 to n. You are also given times,
a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node,
vi is the target node, and wi is the time it takes for a signal to travel from source to target.

    We will send a signal from a given node k. Return the minimum time it takes for all the n
nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.
*/

struct Edge
{
    uint8_t dest;
    uint8_t weight;

    Edge (uint8_t dest = 0, uint8_t weight = 0) :
        dest(dest), weight(weight)
    {}
};

struct NodeLen
{
    uint8_t node;
    uint32_t len;

    NodeLen (uint8_t node = 0, uint32_t len = 0) :
        node(node), len(len)
    {}
};

/*
void printEdgeList(const vector<vector<Edge>>& edgeList)
{
    size_t i {};
    size_t j {};
    size_t size {edgeList.size()};
    size_t ddz {};

    for (; i < size; ++i)
    {
        cout << i << " -> ";

        ddz = edgeList[i].size();
        for (j = 0; j < ddz; ++j)
        {
            cout << static_cast<int>(edgeList[i][j].dest) << "," << static_cast<int>(edgeList[i][j].weight) << "  ";
        }

        cout << '\n';
    }
}
*/

int networkDelayTime(vector<vector<int>>& times, int n, int k)
{
    vector<vector<Edge>> edgeList (n);

    int res {};
    size_t i {};
    size_t size {times.size()};
    NodeLen temp {};

    vector<bool> visited (n);

    auto comp = [](const NodeLen& l, const NodeLen& r)
    {
        return l.len > r.len;
    };

    priority_queue<NodeLen, vector<NodeLen>, decltype(comp)> djikstra (comp);
    djikstra.emplace(k - 1, 0);

    for (; i < size; ++i)
    {
        edgeList[times[i][0] - 1].emplace_back(
            static_cast<uint8_t>(times[i][1] - 1),
            static_cast<uint8_t>(times[i][2])
        );
    }

    //printEdgeList(edgeList);

    while (!djikstra.empty())
    {
        temp = djikstra.top();
        djikstra.pop();

        //cout << "node: " << static_cast<int>(temp.node) << ", len = " << temp.len << '\n';

        if (!visited[temp.node])
        {
            visited[temp.node] = true;

            res = temp.len;

            size = edgeList[temp.node].size();
            for (i = 0; i < size; ++i)
            {
                djikstra.emplace(
                    edgeList[temp.node][i].dest, 
                    temp.len + edgeList[temp.node][i].weight
                );
            }
        }
    }

    size = visited.size();
    for (i = 0; i < size; ++i)
    {
        if (!visited[i])
        {
            return -1;
        }
    }

    return res;
}

int main()
{
    vector<vector<int>> times1 = {{2,1,1},{2,3,1},{3,4,1}};
    int n1 = 4;
    int k1 = 2;
    
    vector<vector<int>> times2 = {{1,2,1}};
    int n2 = 2;
    int k2 = 1;
    
    vector<vector<int>> times3 = {{1,2,1}};
    int n3 = 2;
    int k3 = 2;
    
    vector<vector<int>> times4 = {{1,2,1},{2,3,2},{1,3,4}};
    int n4 = 3;
    int k4 = 1;

    cout << networkDelayTime(times1, n1, k1) << '\n';
    cout << networkDelayTime(times2, n2, k2) << '\n';
    cout << networkDelayTime(times3, n3, k3) << '\n';
    cout << networkDelayTime(times4, n4, k4) << '\n';

    return 0;
}
