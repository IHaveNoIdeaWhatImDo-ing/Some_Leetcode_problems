#include <vector>
#include <cstring>
#include <iostream>

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

#define AT(row, col, n) ((row) * n + col)

constexpr unsigned int nodeCount {100};
constexpr unsigned int maxCost {static_cast<unsigned int>(-1)};

unsigned int adjMat [nodeCount * nodeCount];

class Graph {
    int n;

public:
    Graph(int n, vector<vector<int>>& edges) : n(n) {
        int k;
        int i;
        int j;

        int left;
        int right;
        int current;

        memset(adjMat, maxCost, n * n * sizeof(unsigned int));

        for (i = 0; i < n; ++i)
        {
            adjMat[AT(i, i, n)] = 0u;
        }

        k = static_cast<int>(edges.size());
        for (i = 0; i < k; ++i)
        {
            adjMat[AT(edges[i][0], edges[i][1], n)] = edges[i][2];
        }

        for (k = 0; k < n; ++k)
        {
            for (i = 0; i < n; ++i)
            {
                for (j = 0; j < n; ++j)
                {
                    left = AT(i, k, n);
                    right = AT(k, j, n);
                    current = AT(i, j, n);

                    if (adjMat[left] == maxCost || adjMat[right] == maxCost)
                    {
                        continue;
                    }

                    if (adjMat[current] > adjMat[left] + adjMat[right])
                    {
                        adjMat[current] = adjMat[left] + adjMat[right];
                    }
                }
            }
        }
    }
    
    void addEdge(vector<int> edge) {
        int idx {AT(edge[0], edge[1], n)};

        if (edge[2] >= adjMat[idx])
        {
            return;
        }

        adjMat[idx] = edge[2];

        int i;
        int j;

        int left;
        int right;
        int current;

        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                left = AT(i, edge[0], n);
                right = AT(edge[1], j, n);
                current = AT(i, j, n);

                if (adjMat[left] == maxCost || adjMat[right] == maxCost)
                {
                    continue;
                }

                if (adjMat[current] > adjMat[left] + adjMat[right] + edge[2])
                {
                    adjMat[current] = adjMat[left] + adjMat[right] + edge[2];
                }
            }
        }
    }
    
    int shortestPath(int node1, int node2) {
        int idx {AT(node1, node2, n)};

        if (adjMat[idx] ^ maxCost)
        {
            return adjMat[idx];
        }

        return -1;
    }
};

int main()
{


    return 0;
}
