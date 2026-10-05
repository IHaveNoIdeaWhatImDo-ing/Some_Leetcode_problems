#include <queue>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

/*
    You are given an integer n, the number of nodes in a directed graph where
the nodes are labeled from 0 to n - 1. Each edge is red or blue in this graph,
and there could be self-edges and parallel edges.

You are given two arrays redEdges and blueEdges where:

    - redEdges[i] = [ai, bi] indicates that there is a directed red edge from node ai to node bi in the graph, and
    - blueEdges[j] = [uj, vj] indicates that there is a directed blue edge from node uj to node vj in the graph.

    Return an array answer of length n, where each answer[x] is the length of the shortest
path from node 0 to node x such that the edge colors alternate along the path, or -1 if such a path does not exist.
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

inline void print(const vector<vector<pair<unsigned char, bool>>>& arr)
{
    unsigned short i {};
    unsigned short j {};
    unsigned short size {static_cast<unsigned char>(arr.size())};
    unsigned short ddz {};

    for (; i < size; ++i)
    {
        cout << i << " -> ";

        ddz = static_cast<unsigned char>(arr[i].size());
        for (j = 0; j < ddz; ++j)
        {
            cout << '(' << static_cast<int>(arr[i][j].first) << ' ' << arr[i][j].second << ") ";
        }

        cout << '\n';
    }
}

void bfsCrazyStyle(
    vector<int>& res,
    vector<vector<pair<unsigned char, bool>>>& edgeList,
    bool clr = false
)
{
    int len {};
    int temp {};
    short i {};
    short size {};
    short fringeSize {1};

    queue<unsigned char> fringe {};
    fringe.emplace(0);

    while (!fringe.empty())
    {
        temp = fringe.front();
        //cout << "len: " << len << ", node: " << temp << ", clr: " << static_cast<int>(clr) << '\n';
        fringe.pop();

        --fringeSize;
        size = static_cast<unsigned short>(edgeList[temp].size());

        if (res[temp] > len)
        {
            res[temp] = len;
        }

        for (i = size - 1; i >= 0; --i)
        {
            if (edgeList[temp][i].second == clr)
            {
                fringe.emplace(edgeList[temp][i].first);
                swap(edgeList[temp][i], edgeList[temp][--size]);
                edgeList[temp].pop_back();
            }
        }

        if (!fringeSize)
        {
            fringeSize = static_cast<short>(fringe.size());
            ++len;
            clr = !clr;
        }
    }
}

vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges)
{
    int intMax = ~0u >> 1;

    vector<int> res(n, intMax);

    unsigned short i {};
    unsigned short size_r {static_cast<unsigned short>(redEdges.size())};
    unsigned short size_b {static_cast<unsigned short>(blueEdges.size())};

    // false => red, true => blue
    vector<vector<pair<unsigned char, bool>>> edgeList(n);
    vector<vector<pair<unsigned char, bool>>> edgeListCopy;

    for (; i < size_r; ++i)
    {
        edgeList[redEdges[i][0]].emplace_back(
            pair<unsigned char, bool> (
                static_cast<unsigned char>(redEdges[i][1]), false
            )
        );
    }

    for (i = 0; i < size_b; ++i)
    {
        edgeList[blueEdges[i][0]].emplace_back(
            pair<unsigned char, bool> (
                static_cast<unsigned char>(blueEdges[i][1]), true
            )
        );
    }

    edgeListCopy = edgeList;

    bfsCrazyStyle(res, edgeList, false); // starting with red edges

    edgeList = edgeListCopy;

    bfsCrazyStyle(res, edgeList, true);  // starting with blue edges

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
