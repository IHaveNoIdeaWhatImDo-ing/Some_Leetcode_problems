#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

/*
    You are given an integer n indicating there are n people numbered from 0 to n - 1.
You are also given a 0-indexed 2D integer array meetings where meetings[i] = [x_i, y_i, time_i]
indicates that person x_i and person y_i have a meeting at time_i. A person may attend multiple
meetings at the same time. Finally, you are given an integer firstPerson.

    Person 0 has a secret and initially shares the secret with a person firstPerson at time
0. This secret is then shared every time a meeting takes place with a person that has the
secret. More formally, for every meeting, if a person x_i has the secret at time_i, then they
will share the secret with person y_i, and vice versa.

    The secrets are shared instantaneously. That is, a person may receive the secret and
share it with people in other meetings within the same time frame.

    Return a list of all the people that have the secret after all the meetings have taken
place. You may return the answer in any order.

Constraints:

    2 <= n <= 105
    1 <= meetings.length <= 105
    meetings[i].length == 3
    0 <= x_i, y_i <= n - 1
    x_i != y_i
    1 <= time_i <= 105
    1 <= firstPerson <= n - 1

*/

struct DisjointSet
{
    int parent[100000];
    int weight[100000];

    void init(int size)
    {
        for (int i {}; i < size; ++i)
        {
            parent[i] = i;
            weight[i] = 1;
        }
    }

    int getRoot(int n)
    {
        if (parent[n] != n)
        {
            parent[n] = getRoot(parent[n]);
        }

        return parent[n];
    }

    int areInOneSet(int l, int r)
    {
        return getRoot(l) == getRoot(r);
    }

    bool unite(int l, int r)
    {
        int rootLeft {getRoot(l)};
        int rootRight {getRoot(r)};

        if (rootLeft == rootRight)
        {
            return false;
        }

        if (weight[rootLeft] < weight[rootRight])
        {
            parent[rootLeft] = rootRight;
            weight[rootRight] += weight[rootLeft];
        }
        else
        {
            parent[rootRight] = rootLeft;
            weight[rootLeft] += weight[rootRight];
        }

        return true;
    }
} ds;

static bool doesHeKnow[100000];
static int currTimeWindow[200000];
static int currTimeWindowCount {};

vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> res;

    int j;
    size_t i;
    size_t size {meetings.size()};

    int currTime;
    int knowsSecret;

    res.emplace_back(0);

    ds.init(n);
    ds.unite(0, firstPerson);

    memset(doesHeKnow, 0x0, n * sizeof(bool));
    doesHeKnow[0] = true;
    doesHeKnow[firstPerson] = true;

    currTimeWindowCount = 0;

    sort(
        meetings.begin(), meetings.end(),
        [](const vector<int>& l, const vector<int>& r)
        {
            return l[2] < r[2];
        }
    );

    currTime = meetings[0][2];
    for (i = 0; i < size; ++i)
    {
        if (currTime != meetings[i][2])
        {
            currTime = meetings[i][2];
            knowsSecret = ds.getRoot(0);
            for (j = 0; j < currTimeWindowCount; ++j)
            {
                if (knowsSecret != ds.getRoot(currTimeWindow[j]))
                {
                    ds.parent[currTimeWindow[j]] = currTimeWindow[j];
                    ds.weight[currTimeWindow[j]] = 1;
                }
                else
                {
                    doesHeKnow[currTimeWindow[j]] = true;
                }
            }

            currTimeWindowCount = 0;
        }

        ds.unite(meetings[i][0], meetings[i][1]);
        currTimeWindow[currTimeWindowCount++] = meetings[i][0];
        currTimeWindow[currTimeWindowCount++] = meetings[i][1];
    }

    knowsSecret = ds.getRoot(0);
    for (j = 0; j < currTimeWindowCount; ++j)
    {
        if (knowsSecret != ds.getRoot(currTimeWindow[j]))
        {
            ds.parent[currTimeWindow[j]] = currTimeWindow[j];
            ds.weight[currTimeWindow[j]] = 1;
        }
        else
        {
            doesHeKnow[currTimeWindow[j]] = true;
        }
    }

    for (j = 1; j < n; ++j)
    {
        if (doesHeKnow[j])
        {
            res.emplace_back(j);
        }
    }

    return res;
}

static void print(const vector<int>& vec)
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
    vector<vector<int>> meetings1 = {{1,2,5},{2,3,8},{1,5,10}};
    int firstPerson1 {1};
    
    int n2 {4};
    vector<vector<int>> meetings2 = {{3,1,3},{1,2,2},{0,3,3}};
    int firstPerson2 {3};
    
    int n3 {5};
    vector<vector<int>> meetings3 = {{3,4,2},{1,2,1},{2,3,1}};
    int firstPerson3 {1};

    vector<int> res1 = findAllPeople(n1, meetings1, firstPerson1);
    vector<int> res2 = findAllPeople(n2, meetings2, firstPerson2);
    vector<int> res3 = findAllPeople(n3, meetings3, firstPerson3);

    print(res1);
    print(res2);
    print(res3);

    return 0;
}
