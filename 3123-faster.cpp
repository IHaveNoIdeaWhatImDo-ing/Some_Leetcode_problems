#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

/*
    You are given an undirected weighted graph of n nodes numbered from 0 to n - 1. The
graph consists of m edges represented by a 2D array edges, where edges[i] = [ai, bi, wi]
indicates that there is an edge between nodes ai and bi with weight wi.

    Consider all the shortest paths from node 0 to node n - 1 in the graph. You need to
find a boolean array answer where answer[i] is true if the edge edges[i] is part of at
least one shortest path. Otherwise, answer[i] is false.

Return the array answer.

Note that the graph may not be connected.

Constraints:

    2 <= n <= 5 * 10^4
    m == edges.length
    1 <= m <= min(5 * 10^4, n * (n - 1) / 2)
    0 <= a_i, b_i < n
    a_i != b_i
    1 <= w_i <= 10^5
    There are no repeated edges.
*/

static unsigned int dist[50000];
static bool visited[50000];

struct Node
{
    unsigned short node;
    unsigned short edgeIdx;
    unsigned int weight;

    Node(unsigned short _node = 0, unsigned short _edgeIdx = 0, unsigned int _weight = 0u) :
        node(_node), edgeIdx(_edgeIdx), weight(_weight)
    {}
};

struct comp
{
    bool operator() (const Node& l, const Node& r) const
    {
        return l.weight > r.weight;
    }
};

static vector<vector<Node>> adjList;

vector<bool> findAnswer(int n, vector<vector<int>>& edges)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t m {edges.size()};
    size_t size;
    size_t i;

    vector<bool> res(m, false);

    priority_queue<Node, vector<Node>, comp> pq;

    Node temp;
    unsigned short next;
    unsigned int currDist;

    queue<Node> bfs;

    memset(dist, 0xFF, n * sizeof(unsigned int));
    dist[0] = 0u;

    memset(visited, 0x0, n * sizeof(bool));

    adjList.clear();
    adjList.resize(n);

    for (i = 0; i < m; ++i)
    {
        adjList[edges[i][0]].emplace_back(
            static_cast<unsigned short>(edges[i][1]),
            static_cast<unsigned short>(i),
            static_cast<unsigned int>(edges[i][2])
        );
        adjList[edges[i][1]].emplace_back(
            static_cast<unsigned short>(edges[i][0]),
            static_cast<unsigned short>(i),
            static_cast<unsigned int>(edges[i][2])
        );
    }

    pq.emplace(0, 0, 0u);

    while (!pq.empty())
    {
        temp = pq.top();
        pq.pop();

        if (dist[temp.node] ^ temp.weight)
        {
            continue;
        }

        size = adjList[temp.node].size();
        for (i = 0; i < size; ++i)
        {
            next = adjList[temp.node][i].node;
            currDist = dist[temp.node] + adjList[temp.node][i].weight;

            if (dist[next] > currDist)
            {
                dist[next] = currDist;
                pq.emplace(next, adjList[temp.node][i].edgeIdx, currDist);
            }
        }
    }

    bfs.emplace(n - 1, 0, 0u);
    visited[n - 1] = true;

    while (!bfs.empty())
    {
        temp = bfs.front();
        bfs.pop();

        size = adjList[temp.node].size();
        for (i = 0; i < size; ++i)
        {
            next = adjList[temp.node][i].node;
            currDist = temp.weight + adjList[temp.node][i].weight;

            if (dist[next] + currDist != dist[n - 1])
            {
                continue;
            }

            res[adjList[temp.node][i].edgeIdx] = true;

            if (!visited[next])
            {
                visited[next] = true;
                bfs.emplace(next, 0, currDist);
            }
        }
    }

    return res;
}

static void print(const vector<bool>& vec)
{
    size_t size {vec.size()};
    for (size_t i {}; i < size; ++i)
    {
        cout << vec[i] << ' ';
    }
    cout << '\n';
}

int main()
{
    int n1 {6};
    vector<vector<int>> edges1 = {{0,1,4},{0,2,1},{1,3,2},{1,4,3},{1,5,1},{2,3,1},{3,5,3},{4,5,2}};

    int n2 {4};
    vector<vector<int>> edges2 = {{2,0,1},{0,1,1},{0,3,4},{3,2,2}};

    int n3 {7};
    vector<vector<int>> edges3 = {{2,4,4},{5,4,9},{0,2,6},{6,2,1},{3,6,3},{1,3,6},{6,0,4},{0,4,5},{1,0,1},{3,5,2}};

    int n4 {4};
    vector<vector<int>> edges4 = {{1,2,1}};

    vector<bool> res1 = findAnswer(n1, edges1);
    vector<bool> res2 = findAnswer(n2, edges2);
    vector<bool> res3 = findAnswer(n3, edges3);
    vector<bool> res4 = findAnswer(n4, edges4);

    print(res1);
    print(res2);
    print(res3);
    print(res4);

    return 0;
}
