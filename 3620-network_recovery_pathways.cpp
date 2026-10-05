#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

/*
    You are given a directed acyclic graph of n nodes numbered from 0 to n − 1. This is
represented by a 2D array edges of length m, where edges[i] = [ui, vi, costi] indicates
a one‑way communication from node ui to node vi with a recovery cost of costi.

    Some nodes may be offline. You are given a boolean array online where
online[i] = true means node i is online. Nodes 0 and n − 1 are always online.

A path from 0 to n − 1 is valid if:

    All intermediate nodes on the path are online.
    The total recovery cost of all edges on the path does not exceed k.

For each valid path, define its score as the minimum edge‑cost along that path.

    Return the maximum path score (i.e., the largest minimum-edge cost) among all valid
paths. If no valid path exists, return -1.
*/

static unsigned long long dist[50000];

struct Node
{
    unsigned int node;
    unsigned long long cost;

    Node(unsigned int _node = 0u, unsigned long long _cost = 0ull) :
        node(_node), cost(_cost)
    {}
};

struct AdjNode
{
    unsigned int node;
    unsigned int cost;

    AdjNode(unsigned int _node = 0u, unsigned int _cost = 0u) :
        node(_node), cost(_cost)
    {}
};

static vector<vector<AdjNode>> adjList;

static unsigned int incommingEdges[50000];

static unsigned short topoSort[50000];
static unsigned short tSortLen;

void kahnTopologicalSort(const vector<bool>& online)
{
    size_t n {adjList.size()};
    size_t i;
    size_t j;
    size_t size;

    queue<unsigned short> bfs;

    unsigned short temp;
    unsigned short next;

    memset(incommingEdges, 0x0, n * sizeof(unsigned int));
    tSortLen = 0;

    for (i = 0; i < n; ++i)
    {
        size = adjList[i].size();
        for (j = 0; j < size; ++j)
        {
            ++incommingEdges[adjList[i][j].node];
        }
    }

    for (i = 0; i < n; ++i)
    {
        if (!incommingEdges[i] && online[i])
        {
            topoSort[tSortLen++] = i;
            bfs.emplace(i);
        }
    }

    while (!bfs.empty())
    {
        temp = bfs.front();
        bfs.pop();

        size = adjList[temp].size();
        for (i = 0; i < size; ++i)
        {
            next = adjList[temp][i].node;

            --incommingEdges[next];
            if (!incommingEdges[next])
            {
                topoSort[tSortLen++] = next;
                bfs.emplace(next);
            }
        }
    }
}

bool isTraversable(
    const vector<bool>& online,
    unsigned long long k,
    unsigned int minCost
)
{
    unsigned short j;
    unsigned int n {static_cast<unsigned int>(online.size())};
    size_t size;
    size_t i;

    unsigned long long currDist;
    unsigned int next;

    memset(dist, 0xFF, n * sizeof(unsigned long long));
    dist[0] = 0ull;

    for (j = 0; j < tSortLen; ++j)
    {
        if (dist[topoSort[j]] == ~0ull)
        {
            continue;
        }

        size = adjList[topoSort[j]].size();
        for (i = 0; i < size; ++i)
        {
            next = adjList[topoSort[j]][i].node;
            currDist = dist[topoSort[j]] + static_cast<unsigned long long>(adjList[topoSort[j]][i].cost);

            if (
                adjList[topoSort[j]][i].cost >= minCost &&
                dist[next] > currDist &&
                currDist <= k
            )
            {
                dist[next] = currDist;
            }
        }
    }

    return dist[n - 1] != ~0ull;
}

int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int res {-1};

    size_t n {online.size()};
    size_t size {edges.size()};

    int left {1000000000};
    int right {};
    int mid;

    bool possible;

    adjList.clear();
    adjList.resize(n);

    for (size_t i {}; i < size; ++i)
    {
        if (right < edges[i][2])
        {
            right = edges[i][2];
        }
        if (left > edges[i][2])
        {
            left = edges[i][2];
        }

        if (!online[edges[i][0]] || !online[edges[i][1]])
        {
            continue;
        }

        adjList[edges[i][0]].emplace_back(
            static_cast<unsigned int>(edges[i][1]),
            static_cast<unsigned int>(edges[i][2])
        );
    }

    kahnTopologicalSort(online);

    while (left <= right)
    {
        mid = (left + right) >> 1;
        possible = isTraversable(
            online,
            static_cast<unsigned long long>(k),
            mid
        );

        if (possible)
        {
            left = mid + 1;
            res = mid;
        }
        else
        {
            right = mid - 1;
        }
    }

    return res;
}

int main()
{
    vector<vector<int>> edges1 = {{0,1,5},{1,3,10},{0,2,3},{2,3,4}};
    vector<bool> online1 = {true,true,true,true};
    int k1 {10ll};
    
    vector<vector<int>> edges2 = {{0,1,7},{1,4,5},{0,2,6},{2,3,6},{3,4,2},{2,4,6}};
    vector<bool> online2 = {true,true,true,false,true};
    int k2 {12ll};

    cout << findMaxPathScore(edges1, online1, k1) << '\n';
    cout << findMaxPathScore(edges2, online2, k2) << '\n';

    return 0;
}
