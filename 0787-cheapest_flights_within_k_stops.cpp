#include <queue>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

/*
    There are n cities connected by some number of flights. You are given an
array flights where flights[i] = [fromi, toi, pricei] indicates that there is
a flight from city fromi to city toi with cost pricei.

    You are also given three integers src, dst, and k, return the cheapest
price from src to dst with at most k stops. If there is no such route, return -1.
*/

struct Edge
{
    unsigned int weight;
    unsigned char node;

    Edge(unsigned char node = 0, unsigned int weight = 0) :
        node(node), weight(weight)
    {}
};

struct EdgeDepth
{
    unsigned int weight;
    unsigned char node;
    unsigned char depth;

    EdgeDepth(unsigned char node = 0, unsigned int weight = 0, unsigned char depth = 0) :
        node(node), weight(weight), depth(depth)
    {}
};

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
{
    constexpr unsigned int maxPrice {100 * 1000 + 1};

    vector<vector<Edge>> adjList(n);
    vector<unsigned int> price(n, maxPrice);

    size_t i {};
    size_t size {flights.size()};

    queue<EdgeDepth> q {};
    EdgeDepth temp {};

    unsigned int tempPrice {};

    for (; i < size; ++i)
    {
        adjList[flights[i][0]].emplace_back(
            static_cast<unsigned char>(flights[i][1]),
            static_cast<unsigned int> (flights[i][2])
        );
    }

    price[src] = 0;

    q.emplace(static_cast<unsigned char>(src), 0, 0);

    while (!q.empty())
    {
        temp = q.front();
        q.pop();

        if (temp.depth > k)
        {
            continue;
        }

        size = adjList[temp.node].size();

        for (i = 0; i < size; ++i)
        {
            tempPrice = temp.weight + adjList[temp.node][i].weight;
            if (tempPrice < price[adjList[temp.node][i].node])
            {
                price[adjList[temp.node][i].node] = tempPrice;
                q.emplace(
                    adjList[temp.node][i].node,
                    tempPrice,
                    temp.depth + 1
                );
            }
        }
    }

    return price[dst] ^ maxPrice ? price[dst] : -1;
}

int main()
{
    /*
    */
    int n1 {4};
    vector<vector<int>> flights1 = {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
    int src1 {0};
    int dst1 {3};
    int k1 {1};

    int n2 {3};
    vector<vector<int>> flights2 = {{0,1,100},{1,2,100},{0,2,500}};
    int src2 {0};
    int dst2 {2};
    int k2 {1};

    int n3 {3};
    vector<vector<int>> flights3 = {{0,1,100},{1,2,100},{0,2,500}};
    int src3 {0};
    int dst3 {2};
    int k3 {0};

    int n4 {5};
    vector<vector<int>> flights4 = {{1,0,5},{2,1,5},{3,0,2},{1,3,2},{4,1,1},{2,4,1}};
    int src4 {2};
    int dst4 {0};
    int k4 {2};

    int n5 {5};
    vector<vector<int>> flights5 = {{0,1,5},{1,2,5},{0,3,2},{3,1,2},{1,4,1},{4,2,1}};
    int src5 {0};
    int dst5 {2};
    int k5 {2};

    /*
    */
    cout << findCheapestPrice(n1, flights1, src1, dst1, k1) << '\n';
    cout << findCheapestPrice(n2, flights2, src2, dst2, k2) << '\n';
    cout << findCheapestPrice(n3, flights3, src3, dst3, k3) << '\n';
    cout << findCheapestPrice(n4, flights4, src4, dst4, k4) << '\n';
    cout << findCheapestPrice(n5, flights5, src5, dst5, k5) << '\n';

    return 0;
}
