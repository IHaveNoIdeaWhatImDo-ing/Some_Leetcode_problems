#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

/*
    There is a country of n cities numbered from 0 to n - 1 where all the cities are connected
by bi-directional roads. The roads are represented as a 2D integer array edges where
edges[i] = [xi, yi, timei] denotes a road between cities xi and yi that takes timei minutes to
travel. There may be multiple roads of differing travel times connecting the same two cities,
but no road connects a city to itself.

    Each time you pass through a city, you must pay a passing fee. This is represented as a
0-indexed integer array passingFees of length n where passingFees[j] is the amount of dollars
you must pay when you pass through city j.

    In the beginning, you are at city 0 and want to reach city n - 1 in maxTime minutes or less.
The cost of your journey is the summation of passing fees for each city that you passed through
at some moment of your journey (including the source and destination cities).

    Given maxTime, edges, and passingFees, return the minimum cost to complete your journey,
or -1 if you cannot complete it within maxTime minutes.
*/

static constexpr unsigned short maxUINT16 {static_cast<unsigned short>(~0u)};

static unsigned int dist[1000][1001]; // first are nodes, then time

struct Node
{
    short node;
    unsigned int cost;
    short time;

    Node(short _node = 0, unsigned int _cost = 0u, short _time = 0) :
        node(_node), cost(_cost), time(_time)
    {}
};

struct comp
{
    bool operator() (const Node& l, const Node& r) const
    {
        return l.cost > r.cost;
    }
};

struct AdjNode
{
    short node;
    short time;

    AdjNode(short _node = 0, short _time = 0) :
        node(_node), time(_time)
    {}
};

static vector<vector<AdjNode>> adjList;

int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n {passingFees.size()};

    size_t size {edges.size()};
    size_t i;

    priority_queue<Node, vector<Node>, comp> pq;

    Node temp;
    unsigned int currCost;
    short currTime;

    adjList.clear();
    adjList.resize(n);

    memset(dist, 0xFF, n * 1001 * sizeof(unsigned int));
    dist[0][0] = passingFees[0];

    pq.emplace(0, passingFees[0], 0);

    for (i = 0; i < size; ++i)
    {
        adjList[edges[i][0]].emplace_back(
            static_cast<short>(edges[i][1]),
            static_cast<short>(edges[i][2])
        );
        adjList[edges[i][1]].emplace_back(
            static_cast<short>(edges[i][0]),
            static_cast<short>(edges[i][2])
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
            currCost = temp.cost + passingFees[adjList[temp.node][i].node];
            currTime = temp.time + adjList[temp.node][i].time;

            if (
                currTime <= maxTime &&
                dist[adjList[temp.node][i].node][currTime] > currCost
            )
            {
                dist[adjList[temp.node][i].node][currTime] = currCost;

                pq.emplace(
                    adjList[temp.node][i].node,
                    currCost,
                    currTime
                );
            }
        }
    }

    currCost = ~0u;
    for (i = 0; i <= maxTime; ++i)
    {
        if (currCost > dist[n - 1][i])
        {
            currCost = dist[n - 1][i];
        }
    }

    return static_cast<int>(currCost);
}

int main()
{
    int maxTime1 {30};
    vector<vector<int>> edges1 = {{0,1,10},{1,2,10},{2,5,10},{0,3,1},{3,4,10},{4,5,15}};
    vector<int> passingFees1 = {5,1,2,20,20,3};
    
    int maxTime2 {29};
    vector<vector<int>> edges2 = {{0,1,10},{1,2,10},{2,5,10},{0,3,1},{3,4,10},{4,5,15}};
    vector<int> passingFees2 = {5,1,2,20,20,3};
    
    int maxTime3 {25};
    vector<vector<int>> edges3 = {{0,1,10},{1,2,10},{2,5,10},{0,3,1},{3,4,10},{4,5,15}};
    vector<int> passingFees3 = {5,1,2,20,20,3};

    cout << minCost(maxTime1, edges1, passingFees1) << '\n';
    cout << minCost(maxTime2, edges2, passingFees2) << '\n';
    cout << minCost(maxTime3, edges3, passingFees3) << '\n';
}
