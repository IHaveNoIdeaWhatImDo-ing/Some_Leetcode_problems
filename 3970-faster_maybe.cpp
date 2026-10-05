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

using uint64 = unsigned long long int;

unsigned int dist[50000][50];

struct comp
{
    bool operator() (uint64 l, uint64 r) const
    {
        return (l & 0xFFFFFFFF) > (r & 0xFFFFFFFF);
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

    int edge;
    vector<vector<unsigned int>> adjList(n);

    priority_queue<uint64, vector<uint64>, comp> pq;

    uint64 temp;
    unsigned short currentNode;
    short currentRepeats;
    int currentDist;

    unsigned short nextNode;
    int nextWeight;

    short nextRepeats;
    int nextDist;

    memset(dist, 0xFF, n * 50 * sizeof(unsigned int));
    dist[0][0] = 0u;

    --k;

    pq.emplace(0ull);

    for (i = 0; i < size; ++i)
    {
        edge =  static_cast<unsigned int>(edges[i][1]) << 16;
        edge += static_cast<unsigned int>(edges[i][2]);

        adjList[edges[i][0]].emplace_back(edge);
    }

    while (!pq.empty())
    {
        temp = pq.top();
        pq.pop();

        currentNode = static_cast<unsigned short>(temp >> 48);
        currentRepeats = static_cast<short>((temp & 0xFFFF00000000) >> 32);
        currentDist = static_cast<int>(temp & 0xFFFFFFFF);

        if (currentNode == n - 1)
        {
            break;
        }

        size = adjList[currentNode].size();

        for (i = 0; i < size; ++i)
        {
            nextNode = static_cast<unsigned short>(adjList[currentNode][i] >> 16);
            nextWeight = static_cast<int>(adjList[currentNode][i] & 0xFFFF);

            nextRepeats = labels[currentNode] == labels[nextNode] ? currentRepeats + 1 : 0;
            nextDist = static_cast<int>(currentDist) + nextWeight;

            if (
                nextRepeats <= k &&
                dist[nextNode][nextRepeats] > nextDist
            )
            {
                dist[nextNode][nextRepeats] = nextDist;

                temp =  static_cast<uint64>(nextNode) << 48;
                temp += static_cast<uint64>(nextRepeats) << 32;
                temp += static_cast<uint64>(nextDist);

                pq.emplace(temp);
            }
        }
    }

    size = static_cast<size_t>(k + 1);

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
