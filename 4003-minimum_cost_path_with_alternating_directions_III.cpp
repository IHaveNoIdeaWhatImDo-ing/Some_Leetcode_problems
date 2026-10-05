#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

/*
    You are given two integers m and n representing the number of rows
and columns of a grid. Your goal is to reach cell (m - 1, n - 1).
You are also given a 2D integer array penalty.

The cost to enter cell (i, j) is (i + 1) * (j + 1).

    You begin at cell (0, 0) and initially pay its entrance cost.
Actions performed after entering (0, 0) are numbered starting from 1.

    On each action, you may move to an adjacent cell or wait in the
current cell. A move follows the parity rule if:

    On an odd-numbered action, you move right or down.
    On an even-numbered action, you move left or up.

The cost of an action is determined as follows:

    If you move according to the parity rule, pay only the entrance
    cost of the destination cell.
    If you move in a direction that violates the parity rule, pay the
    entrance cost of the destination cell plus penalty[i][j], where
    (i, j) is the cell you move from.
    If you wait in cell (i, j), pay penalty[i][j].

    After every move or wait, the action number increases by 1.
Therefore, the required parity alternates after every action, regardless
of whether a penalty was paid.

Return the minimum total cost required to reach (m - 1, n - 1).
*/

using uint64 = unsigned long long int;

static inline int AT(int row, int col, int cols)
{
    return row * cols + col;
}

uint64 dist[100000][2];

struct Node
{
    int row;
    int col;
    uint64 weight;
    bool evenParity;

    Node(int _row = 0, int _col = 0, uint64 _weight = 0ull, bool _evenParity = false) :
        row(_row), col(_col), weight(_weight), evenParity(_evenParity)
    {}
};

struct comp
{
    bool operator() (const Node& l, const Node& r) const
    {
        return l.weight > r.weight;
    }
};

long long minCost(int m, int n, vector<vector<int>>& penalty)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    priority_queue<Node, vector<Node>, comp> pq;

    Node temp;
    uint64 currentDist;
    int index;

    memset(dist, 0xFF, m * n * 2 * sizeof(uint64));
    dist[0][0] = 1ull;

    pq.emplace(
        0, 0,
        1ull,
        false
    );

    while (!pq.empty())
    {
        temp = pq.top();
        pq.pop();

        currentDist = temp.weight + static_cast<uint64>(penalty[temp.row][temp.col]);
        index = AT(temp.row, temp.col, n);

        if (dist[index][!temp.evenParity] > currentDist)
        {
            pq.emplace(
                temp.row,
                temp.col,
                currentDist,
                !temp.evenParity
            );
        }

        if (temp.row == m - 1 && temp.col == n - 1)
        {
            break;
        }

        if (temp.row > 0)
        {
            currentDist = temp.weight + static_cast<uint64>(temp.row * (temp.col + 1));

            if (!temp.evenParity)
            {
                currentDist += static_cast<uint64>(penalty[temp.row][temp.col]);
            }

            index = AT(temp.row - 1, temp.col, n);

            if (dist[index][!temp.evenParity] > currentDist)
            {
                dist[index][!temp.evenParity] = currentDist;

                pq.emplace(
                    temp.row - 1,
                    temp.col,
                    currentDist,
                    !temp.evenParity
                );
            }
        }

        if (temp.row < m - 1)
        {
            currentDist = temp.weight + static_cast<uint64>((temp.row + 2) * (temp.col + 1));

            if (temp.evenParity)
            {
                currentDist += static_cast<uint64>(penalty[temp.row][temp.col]);
            }

            index = AT(temp.row + 1, temp.col, n);

            if (dist[index][!temp.evenParity] > currentDist)
            {
                dist[index][!temp.evenParity] = currentDist;

                pq.emplace(
                    temp.row + 1,
                    temp.col,
                    currentDist,
                    !temp.evenParity
                );
            }
        }

        if (temp.col > 0)
        {
            currentDist = temp.weight + static_cast<uint64>((temp.row + 1) * temp.col);

            if (!temp.evenParity)
            {
                currentDist += static_cast<uint64>(penalty[temp.row][temp.col]);
            }

            index = AT(temp.row, temp.col - 1, n);

            if (dist[index][!temp.evenParity] > currentDist)
            {
                dist[index][!temp.evenParity] = currentDist;

                pq.emplace(
                    temp.row,
                    temp.col - 1,
                    currentDist,
                    !temp.evenParity
                );
            }
        }

        if (temp.col < n - 1)
        {
            currentDist = temp.weight + static_cast<uint64>((temp.row + 1) * (temp.col + 2));

            if (temp.evenParity)
            {
                currentDist += static_cast<uint64>(penalty[temp.row][temp.col]);
            }

            index = AT(temp.row, temp.col + 1, n);

            if (dist[index][!temp.evenParity] > currentDist)
            {
                dist[index][!temp.evenParity] = currentDist;

                pq.emplace(
                    temp.row,
                    temp.col + 1,
                    currentDist,
                    !temp.evenParity
                );
            }
        }
    }

    return static_cast<long long>(min(dist[AT(m - 1, n - 1, n)][0], dist[AT(m - 1, n - 1, n)][1]));
}

int main()
{
    int m1 {2};
    int n1 {2};
    vector<vector<int>> penalty1 = {{5,3},{1,4}};

    int m2 {2};
    int n2 {2};
    vector<vector<int>> penalty2 = {{0,7},{3,2}};

    int m3 {2};
    int n3 {3};
    vector<vector<int>> penalty3 = {{8,0,9},{7,4,1}};

    cout << minCost(m1, n1, penalty1) << '\n';
    cout << minCost(m2, n2, penalty2) << '\n';
    cout << minCost(m3, n3, penalty3) << '\n';

    return 0;
}
