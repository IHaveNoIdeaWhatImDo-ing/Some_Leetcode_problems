#include <queue>
#include <vector>
#include <cstdint>
#include <iostream>

using namespace std;

/*
    You are given an integer n, the number of nodes in a directed graph where the nodes are labeled from 0 to n - 1.
Each edge is red or blue in this graph, and there could be self-edges and parallel edges.

You are given two arrays redEdges and blueEdges where:

    redEdges[i] = [ai, bi] indicates that there is a directed red edge from node ai to node bi in the graph, and
    blueEdges[j] = [uj, vj] indicates that there is a directed blue edge from node uj to node vj in the graph.

    Return an array answer of length n, where each answer[x] is the length of the shortest path from node 0 to
node x such that the edge colors alternate along the path, or -1 if such a path does not exist.
*/

inline void print(const vector<int>& arr)
{
    unsigned char i {};
    unsigned char size {static_cast<unsigned char>(arr.size())};

    for (; i < size; ++i)
    {
        cout << arr[i] << ' ';
    }
    cout << '\n';
}

struct Edge
{
    uint8_t dest;
    bool colour;

    Edge(uint8_t dest = 0, bool colour = false) :
        dest(dest), colour(colour)
    {}
};

struct NodeClrs
{
    bool visitedRed;
    bool visitedBlue;

    NodeClrs(bool visitedRed = false, bool visitedBlue = false) :
        visitedRed(visitedRed), visitedBlue(visitedBlue)
    {}
};

void bfsCrazyStyle
(
    vector<int>& res,
    const vector<vector<Edge>>& edgeList,
    vector<NodeClrs>& visited,
    bool clr = false
)
{
    uint8_t temp {};
    int len {};
    size_t size {};
    size_t fringeSize {1};
    queue<uint8_t> fringe {};
    fringe.emplace(0);

    while (!fringe.empty())
    {
        temp = fringe.front();
        fringe.pop();
        --fringeSize;

        if
        (
            !clr && !visited[temp].visitedRed ||
             clr && !visited[temp].visitedBlue
        )
        {
            if (!clr)
            {
                visited[temp].visitedRed = true;
            }
            else
            {
                visited[temp].visitedBlue = true;
            }

            if (res[temp] > len)
            {
                res[temp] = len;
            }

            size = edgeList[temp].size();

            for (size_t i = 0; i < size; ++i)
            {
                if (edgeList[temp][i].colour == clr)
                {
                    fringe.emplace(edgeList[temp][i].dest);
                }
            }
        }

        if (!fringeSize)
        {
            fringeSize = fringe.size();
            ++len;
            clr = !clr;
        }
    } 
}

vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges)
{
    int intMax = static_cast<int>(~0u >> 1);
    vector<int> res (n, intMax);

    uint16_t i {};
    uint16_t sizeRed  {static_cast<uint16_t>(redEdges.size())};
    uint16_t sizeBlue {static_cast<uint16_t>(blueEdges.size())};
    vector<vector<Edge>> edgeList (n);
    vector<NodeClrs> visited (n);

    for (; i < sizeRed; ++i)
    {
        edgeList[redEdges[i][0]].emplace_back
        (
            static_cast<uint8_t>(redEdges[i][1]), false
        );
    }

    for (i = 0; i < sizeBlue; ++i)
    {
        edgeList[blueEdges[i][0]].emplace_back
        (
            static_cast<uint8_t>(blueEdges[i][1]), true
        );
    }

    bfsCrazyStyle(res, edgeList, visited);

    for (i = 0; i < n; ++i)
    {
        visited[i].visitedRed  = false;
        visited[i].visitedBlue = false;
    }

    bfsCrazyStyle(res, edgeList, visited, true);

    for (i = 0; i < n; ++i)
    {
        if (res[i] == intMax)
        {
            res[i] = -1;
        }
    }

    return res;
}

int main()
{
    int n1 = 3;
    vector<vector<int>> redEdges1 = {{0,1},{1,2}};
    vector<vector<int>> blueEdges1 = {};
    
    int n2 = 3;
    vector<vector<int>> redEdges2 = {{0,1}};
    vector<vector<int>> blueEdges2 = {{2,1}};
    
    int n3 = 3;
    vector<vector<int>> redEdges3 = {{0,1},{0,2}};
    vector<vector<int>> blueEdges3 = {{1,0}};
    
    int n4 = 3;
    vector<vector<int>> redEdges4 = {{0,1}};
    vector<vector<int>> blueEdges4 = {{1,2}};
    
    int n5 = 5;
    vector<vector<int>> redEdges5 = {{0,1},{1,2},{2,3},{3,4}};
    vector<vector<int>> blueEdges5 = {{1,2},{2,3},{3,1}};
    
    int n6 = 5;
    vector<vector<int>> redEdges6 = {{2,2},{0,1},{0,3},{0,0},{0,4},{2,1},{2,0},{1,4},{3,4}};
    vector<vector<int>> blueEdges6 = {{1,3},{0,0},{0,3},{4,2},{1,0}};
    
    int n7 = 5;
    vector<vector<int>> redEdges7 = {{3,2},{4,1},{1,4},{2,4}};
    vector<vector<int>> blueEdges7 = {{2,3},{0,4},{4,3},{4,4},{4,0},{1,0}};
    
    int n8 = 5;
    vector<vector<int>> redEdges8 = {{2,2},{0,4},{4,2},{4,3},{2,4},{0,0},{0,1},{2,3},{1,3}};
    vector<vector<int>> blueEdges8 = {{0,4},{1,0},{1,4},{0,0},{4,0}};

    vector<int> res1 = shortestAlternatingPaths(n1, redEdges1, blueEdges1);
    print(res1);

    vector<int> res2 = shortestAlternatingPaths(n2, redEdges2, blueEdges2);
    print(res2);

    vector<int> res3 = shortestAlternatingPaths(n3, redEdges3, blueEdges3);
    print(res3);

    vector<int> res4 = shortestAlternatingPaths(n4, redEdges4, blueEdges4);
    print(res4);
    
    vector<int> res5 = shortestAlternatingPaths(n5, redEdges5, blueEdges5);
    print(res5);

    vector<int> res6 = shortestAlternatingPaths(n6, redEdges6, blueEdges6);
    print(res6);

    vector<int> res7 = shortestAlternatingPaths(n7, redEdges7, blueEdges7);
    print(res7);

    vector<int> res8 = shortestAlternatingPaths(n8, redEdges8, blueEdges8);
    print(res8);

    return 0;
}
