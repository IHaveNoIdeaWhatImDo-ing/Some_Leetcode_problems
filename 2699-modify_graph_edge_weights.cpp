struct Node
{
    short node;
    unsigned int weight;

    Node(short _node = 0, unsigned int _weight = 0u) :
        node(_node), weight(_weight)
    {}
};

struct comp
{
    bool operator() (const Node& l, const Node& r) const
    {
        return l.weight > r.weight;
    }
};

static int adjMat[100][100];

static unsigned int dist[100];

static constexpr unsigned int maxUINT {~0u};

class Solution {
public:
    void dijkstra(int src, int dest, int n, const vector<vector<int>>& edges)
    {
        size_t size;
        size_t i;

        priority_queue<Node, vector<Node>, comp> pq;

        Node temp;
        unsigned int pathLen;

        memset(adjMat, 0x0, n * 100 * sizeof(int));

        size = edges.size();
        for (i = 0; i < size; ++i)
        {
            if (edges[i][2] == -1)
            {
                continue;
            }

            adjMat[edges[i][0]][edges[i][1]] = edges[i][2];
            adjMat[edges[i][1]][edges[i][0]] = edges[i][2];
        }

        memset(dist, 0xFF, n * sizeof(unsigned int));
        dist[src] = 0u;

        pq.emplace(static_cast<short>(src), 0);

        size = static_cast<size_t>(n);
        
        while (!pq.empty())
        {
            temp = pq.top();
            pq.pop();

            if (temp.node == dest)
            {
                break;
            }

            for (i = 0; i < size; ++i)
            {
                if (!adjMat[temp.node][i])
                {
                    continue;
                }

                pathLen = dist[temp.node] + adjMat[temp.node][i];

                if (dist[i] > pathLen)
                {
                    dist[i] = pathLen;
                    pq.emplace(static_cast<short>(i), pathLen);
                }
            }
        }
    }

    void addEdge(size_t edge, short dest, int n, const vector<vector<int>>& edges)
    {
        if (dist[edges[edge][0]] == maxUINT && dist[edges[edge][1]] == maxUINT)
        {
            return;
        }

        short node;
        
        size_t size {static_cast<size_t>(n)};
        size_t i;

        priority_queue<Node, vector<Node>, comp> pq;

        Node temp;
        unsigned int pathLen;

        if (dist[edges[edge][0]] < dist[edges[edge][1]])
        {
            node = static_cast<short>(edges[edge][0]);
        }
        else
        {
            node = static_cast<short>(edges[edge][1]);
        }

        pq.emplace(node, dist[node]);

        while (!pq.empty())
        {
            temp = pq.top();
            pq.pop();

            if (temp.node == dest)
            {
                break;
            }

            for (i = 0; i < size; ++i)
            {
                if (!adjMat[temp.node][i])
                {
                    continue;
                }

                pathLen = dist[temp.node] + adjMat[temp.node][i];

                if (dist[i] > pathLen)
                {
                    dist[i] = pathLen;
                    pq.emplace(static_cast<short>(i), pathLen);
                }
            }
        }
    }

    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target)
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);

        size_t size;
        size_t i;

        bool hasNegativeEdges {};

        size = edges.size();
        dijkstra(source, destination, n, edges);

        for (i = 0; i < size; ++i)
        {
            if (edges[i][2] == -1)
            {
                hasNegativeEdges = true;
                break;
            }
        }

        // if target is unachieavable
        if (dist[destination] < target)
        {
            return vector<vector<int>>();
        }
        else if (dist[destination] != target && !hasNegativeEdges)
        {
            return vector<vector<int>>();
        }

        for (i = 0; i < size; ++i)
        {
            if (edges[i][2] != -1)
            {
                continue;
            }

            if (dist[destination] == target)
            {
                edges[i][2] = 1000000005;
                adjMat[edges[i][0]][edges[i][1]] = edges[i][2];
                adjMat[edges[i][1]][edges[i][0]] = edges[i][2];
                continue;
            }

            edges[i][2] = 1;
            adjMat[edges[i][0]][edges[i][1]] = edges[i][2];
            adjMat[edges[i][1]][edges[i][0]] = edges[i][2];

            addEdge(i, static_cast<short>(destination), n, edges);

            if (dist[destination] < target)
            {
                // runs only once
                edges[i][2] += target - dist[destination];
                adjMat[edges[i][0]][edges[i][1]] = edges[i][2];
                adjMat[edges[i][1]][edges[i][0]] = edges[i][2];
            }
        }

        dijkstra(source, destination, n, edges);
        return dist[destination] == target ? vector<vector<int>>(edges) : vector<vector<int>>();
    }
};