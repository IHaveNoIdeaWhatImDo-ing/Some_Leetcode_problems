#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    There are n rooms labeled from 0 to n - 1 and all the rooms are locked except for room 0. 
Your goal is to visit all the rooms. However, you cannot enter a locked room without having its key.

    When you visit a room, you may find a set of distinct keys in it. Each key has a number on it,
denoting which room it unlocks, and you can take all of them with you to unlock the other rooms.

    Given an array rooms where rooms[i] is the set of keys that you can obtain if you visited room i,
return true if you can visit all the rooms, or false otherwise.
*/

bool canVisitAllRooms(vector<vector<int>>& rooms)
{
    vector<bool> visited(rooms.size());

    int i {};
    int size {};
    int current {};

    queue<int> fringe {};
    fringe.push(0);

    while (!fringe.empty())
    {
        current = fringe.front();
        fringe.pop();

        if (!visited[current])
        {
            visited[current] = true;

            size = static_cast<int>(rooms[current].size());
            for (i = 0; i < size; ++i)
            {
                fringe.push(rooms[current][i]);
            }
        }
    }

    size = static_cast<int>(rooms.size());
    for (i = 0; i < size; ++i)
    {
        if (!visited[i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    vector<vector<int>> rooms1 = {{1},{2},{3},{}};
    vector<vector<int>> rooms2 = {{1,3},{3,0,1},{2},{0}};

    cout << boolalpha << canVisitAllRooms(rooms1) << '\n';
    cout << boolalpha << canVisitAllRooms(rooms2) << '\n';

    return 0;
}
