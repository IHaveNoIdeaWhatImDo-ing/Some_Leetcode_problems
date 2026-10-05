#include <queue>
#include <vector>
#include <iotsream>

using namespace std;

/*
    There is a directed weighted graph that consists of n nodes numbered
from 0 to n - 1. The edges of the graph are initially represented by the
given array edges where edges[i] = [fromi, toi, edgeCosti] meaning that
there is an edge from fromi to toi with the cost edgeCosti.

Implement the Graph class:

    Graph(int n, int[][] edges) initializes the object with n nodes and
    the given edges.

    addEdge(int[] edge) adds an edge to the list of edges where edge =
    [from, to, edgeCost]. It is guaranteed that there is no edge between
    the two nodes before adding this one.

    int shortestPath(int node1, int node2) returns the minimum cost of a
    path from node1 to node2. If no path exists, return -1. The cost of a
    path is the sum of the costs of the edges in the path.
*/

struct Edge
{
    unsigned int node;
    unsigned int weight;

    Edge(
        unsigned int _node = 0u,
        unsigned int _weight = 0u
    ) :
        node(_node), weight(_weight)
    {}
};

struct comp
{
    bool operator() (const Edge& l, const Edge& r) const
    {
        return l.weight > r.weight;
    }
};

vector<vector<Edge>> adjList;

unsigned int dist[100];

class Graph {
    int n;

public:
    Graph(int n, vector<vector<int>>& edges) : n(n) {
        size_t i;
        size_t size {edges.size()};
        
        adjList.clear();
        adjList.resize(n);
        
        for (i = 0; i < size; ++i)
        {
            adjList[edges[i][0]].emplace_back(
                static_cast<unsigned int>(edges[i][1]),
                static_cast<unsigned int>(edges[i][2])
            );
        }
    }
    
    void addEdge(vector<int> edge) {
        adjList[edge[0]].emplace_back(
            static_cast<unsigned int>(edge[1]),
            static_cast<unsigned int>(edge[2])
        );
    }
    
    int shortestPath(int node1, int node2) {
        priority_queue<Edge, vector<Edge>, comp> pq;

        size_t i;
        size_t size;

        Edge temp;
        unsigned int sum;

        memset(dist, -1, n * sizeof(unsigned int));
        dist[node1] = 0u;

        pq.emplace(node1, 0);

        while (!pq.empty())
        {
            temp = pq.top();
            pq.pop();

            if (temp.weight > dist[temp.node])
            {
                continue;
            }

            if (temp.node == node2)
            {
                break;
            }

            size = adjList[temp.node].size();

            for (i = 0; i < size; ++i)
            {
                sum = dist[temp.node] + adjList[temp.node][i].weight;

                if (dist[adjList[temp.node][i].node] <= sum)
                {
                    continue;
                }

                dist[adjList[temp.node][i].node] = sum;

                pq.emplace(
                    adjList[temp.node][i].node,
                    sum
                );
            }
        }

        if (dist[node2] ^ static_cast<unsigned int>(-1))
        {
            return dist[node2];
        }

        return -1;
    }
};

int main()
{


    return 0;
}
