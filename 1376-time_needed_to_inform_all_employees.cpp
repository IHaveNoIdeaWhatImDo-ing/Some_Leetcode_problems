#include <queue>
#include <vector>
#include <iostream>

using namespace std;

/*
    A company has n employees with a unique ID for each employee from 0 to n - 1. The head of
the company is the one with headID.

    Each employee has one direct manager given in the manager array where manager[i]
is the direct manager of the i-th employee, manager[headID] = -1. Also, it is guaranteed that
the subordination relationships have a tree structure.

    The head of the company wants to inform all the company employees of an urgent piece of news.
He will inform his direct subordinates, and they will inform their subordinates, and so on until
all employees know about the urgent news.

    The i-th employee needs informTime[i] minutes to inform all of his direct subordinates
(i.e., After informTime[i] minutes, all his direct subordinates can start spreading the news).

    Return the number of minutes needed to inform all the employees about the urgent news.
*/

void printEdges(const vector<vector<int>>& el)
{
    for (int i = 0, size = el.size(); i < size; ++i)
    {
        cout << i << " -> ";

        for (int j = 0, kur = el[i].size(); j < kur; ++j)
        {
            cout << el[i][j] << ' ';
        }

        cout << '\n';
    }
}

int dfs(const vector<vector<int>>& edgeList, int node, const vector<int>& informTime, int path = 0)
{
    if (edgeList[node].empty())
    {
        return path;
    }
    
    int maximum {};

    for (int i {}, size {static_cast<int>(edgeList[node].size())}; i < size; ++i)
    {
        maximum = max(maximum, dfs(edgeList, edgeList[node][i], informTime, path + informTime[node]));
    }

    return maximum;
}

int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime)
{
    vector<vector<int>> edgeList(n);

    int i {};

    for (; i < n; ++i)
    {
        if (!(manager[i] ^ -1))
        {
            continue;
        }

        edgeList[manager[i]].emplace_back(i);
    }

    //printEdges(edgeList);
    //cout << '\n';

    return dfs(edgeList, headID, informTime);
}

// ---------------- MAKE THIS INLINE WITH BREADTH-FIRST SEARCH, INSTEAD OF DEPTH-FIRST SEARCH WITH RECURSION ----------------

int main()
{
    int n1 = 1;
    int headID1 = 0;
    vector<int> manager1 = {-1};
    vector<int> informTime1 = {0};
    
    int n2 = 6;
    int headID2 = 2;
    vector<int> manager2 = {2,2,-1,2,2,2};
    vector<int> informTime2 = {0,0,1,0,0,0};
    
    int n3 = 15;
    int headID3 = 0;
    vector<int> manager3 = {-1,0,0,1,1,2,2,3,3,4,4,5,5,6,6};
    vector<int> informTime3 = {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0};
    
    int n4 = 10;
    int headID4 = 3;
    
    vector<int> manager4 = {8,9,8,-1,7,1,2,0,3,0};
    vector<int> informTime4 = {224,943,160,909,0,0,0,643,867,722};

    cout << numOfMinutes(n1, headID1, manager1, informTime1) << '\n';
    cout << numOfMinutes(n2, headID2, manager2, informTime2) << '\n';
    cout << numOfMinutes(n3, headID3, manager3, informTime3) << '\n';
    cout << numOfMinutes(n4, headID4, manager4, informTime4) << '\n';

    return 0;
}
