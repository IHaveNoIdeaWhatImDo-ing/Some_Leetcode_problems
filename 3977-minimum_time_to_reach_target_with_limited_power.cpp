#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

/*
You are given a directed weighted graph with n nodes labeled from 0 to n - 1.

    The graph is represented by a 2D integer array edges, where
edges[i] = [ui, vi, ti] indicates a directed edge from node ui to node vi that
takes ti seconds to traverse.

    You are also given an integer power representing the initial available power,
and an integer array cost of length n, where cost[u] represents the power required
to forward the signal from node u through any one of its outgoing edges.

You are given two integers source and target.

    The signal starts at source at time 0 with power units of power and follows
these rules:

    - The signal may traverse a directed edge from node u only if the remaining
    power is at least cost[u].
    - No power is consumed when the signal arrives at a node, unless it later leaves
    that node by traversing another edge.
    - When the signal is forwarded from node u, the remaining power is decreased by
    cost[u] units.
    - Traversing an edge edges[i] = [ui, vi, ti] increases the total time by ti
    seconds.

Return an integer array answer of size 2, where:

    answer[0] is the minimum time required for the signal to reach node target.
    answer[1] is the maximum remaining power among all paths that achieve answer[0].

If the signal cannot reach target, return [-1, -1].

Constraints:
    1 <= n <= 1000
    0 <= edges.length <= 1000
    edges[i] = [u_i, v_i, t_i]
    0 <= u_i, v_i <= n - 1
    1 <= t_i <= 10^9
    1 <= power <= 1000
    cost.length == n
    1 <= cost[i] <= 2000
    0 <= source, target <= n - 1
*/

using uint64 = unsigned long long;

static uint64 dist[1000][1001]; // distance and power left

static constexpr uint64 maxULL {~0ull};

struct Node
{
    unsigned short node;
    unsigned short power;
    uint64 time;

    Node(unsigned short _node = 0, unsigned short _power = 0, uint64 _time = 0ull) :
        node(_node), power(_power), time(_time)
    {}
};

struct AdjNode
{
    unsigned short node;
    unsigned int time;

    AdjNode(unsigned short _node = 0, unsigned int _time = 0u) :
        node(_node), time(_time)
    {}
};

struct comp
{
    bool operator() (const Node& l, const Node& r) const
    {
        return l.time > r.time;
    }
};

struct compPower
{
    bool operator() (const AdjNode& l, const AdjNode& r) const
    {
        return l.time > r.time;
    }
};

static vector<vector<AdjNode>> adjList;

vector<long long> minTimeMaxPower(
    int n,
    vector<vector<int>>& edges,
    int power,
    vector<int>& cost,
    int source,
    int target
)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<long long> res(2, -1ll);

    size_t size {edges.size()};
    size_t i;

    priority_queue<Node, vector<Node>, comp> pq;

    Node temp;
    unsigned short next;
    unsigned short nextPower;
    uint64 currDist;

    bool shortestPath {false};

    memset(dist, 0xFF, n * 1001 * sizeof(uint64));
    dist[source][0] = 0ull;

    adjList.clear();
    adjList.resize(n);

    for (i = 0; i < size; ++i)
    {
        if (cost[edges[i][0]] > power)
        {
            continue;
        }
        else if (cost[edges[i][0]] == power)
        {
            if (edges[i][0] != source || edges[i][1] != target)
            {
                continue;
            }
        }

        adjList[edges[i][0]].emplace_back(
            static_cast<unsigned short>(edges[i][1]),
            static_cast<unsigned int>(edges[i][2])
        );
    }

    pq.emplace(source, 0, 0ull);

    while (!pq.empty())
    {
        temp = pq.top();
        pq.pop();

        if (temp.node == target)
        {
            if (!shortestPath)
            {
                res[0] = temp.time;
                shortestPath = true;
            }

            continue;
        }

        nextPower = temp.power + cost[temp.node];
        if (temp.node == target || nextPower > power || dist[temp.node][temp.power] < temp.time)
        {
            continue;
        }

        size = adjList[temp.node].size();
        for (i = 0; i < size; ++i)
        {
            next = adjList[temp.node][i].node;
            currDist = dist[temp.node][temp.power] + adjList[temp.node][i].time;

            if (dist[next][nextPower] > currDist)
            {
                dist[next][nextPower] = currDist;
                pq.emplace(
                    next,
                    nextPower,
                    currDist
                );
            }
        }
    }

    if (res[0] == -1ll)
    {
        return res;
    }

    size = static_cast<size_t>(power);
    for (i = 0; i <= power; ++i)
    {
        if (dist[target][i] == static_cast<uint64>(res[0]))
        {
            res[1] = power - i;
            break;
        }
    }

    return res;
}

int main()
{
    int n1 {3};
    vector<vector<int>> edges1 = {{1,0,9},{1,2,1},{0,1,3},{0,0,2}};
    int power1 {1};
    vector<int> cost1 = {1,1,1};
    int source1 {1};
    int target1 {0};
    
    int n2 {10};
    vector<vector<int>> edges2 = {{8,1,27},{1,0,10},{9,2,22},{0,8,28},{6,7,97},{9,3,36},{3,7,33},{8,7,35},{5,3,79},{9,7,62},{1,2,17},{6,4,48},{4,1,32},{1,2,73},{2,4,12},{6,1,41},{6,0,92},{0,1,48},{5,2,39},{5,9,47},{2,6,26},{6,7,100},{8,3,63},{9,5,43},{1,7,34},{4,0,61},{2,9,36},{4,4,57},{6,1,49},{2,6,79},{1,2,100},{1,1,18},{9,4,67},{9,5,54},{4,1,98},{7,5,23},{9,5,12},{5,5,13},{6,9,48},{8,7,29},{9,4,61},{7,4,80},{4,2,37},{7,8,70},{7,2,95},{0,1,11},{0,9,74},{3,0,16},{4,3,22},{1,0,97},{5,5,98},{6,9,24},{6,4,79},{2,2,72},{0,8,43},{2,5,57},{8,7,69},{3,1,29},{8,2,97},{0,9,97},{3,7,38},{6,8,50},{7,4,75},{6,9,13},{1,1,51},{1,6,29},{0,9,67},{3,2,76},{1,9,32},{2,3,85},{6,4,45},{8,6,44},{9,4,70}};
    int power2 {58};
    vector<int> cost2 = {3,6,66,2,9,6,20,6,15,9};
    int source2 {8};
    int target2 {0};

    vector<long long> res1 = minTimeMaxPower(n1, edges1, power1, cost1, source1, target1);
    vector<long long> res2 = minTimeMaxPower(n2, edges2, power2, cost2, source2, target2);

    cout << res1[0] << ' ' << res1[1] << '\n';
    cout << res2[0] << ' ' << res2[1] << '\n';

    return 0;
}
