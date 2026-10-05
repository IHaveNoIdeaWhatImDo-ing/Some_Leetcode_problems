#include <vector>
#include <cstddef>
#include <iostream>
#include <algorithm>

using namespace std;

void print(vector<int>& vec)
{
    for (int num : vec)
    {
        cout << num << ' ';
    }
    cout << '\n';
}

/*
Example 1:

Input: piles = [5,4,9], k = 2
Output: 12
Explanation: Steps of a possible scenario are:
- Apply the operation on pile 2. The resulting piles are [5,4,5].
- Apply the operation on pile 0. The resulting piles are [3,4,5].
The total number of stones in [3,4,5] is 12.

Example 2:

Input: piles = [4,3,6,7], k = 3
Output: 12
Explanation: Steps of a possible scenario are:
- Apply the operation on pile 2. The resulting piles are [4,3,3,7].
- Apply the operation on pile 3. The resulting piles are [4,3,3,4].
- Apply the operation on pile 0. The resulting piles are [2,3,3,4].
The total number of stones in [2,3,3,4] is 12.
*/

int minStoneSum(vector<int>& piles, int k)
{
    size_t size = piles.size();
    make_heap(piles.begin(), piles.end());

    for (int i {0}; i < k; ++i)
    {
        piles[0] -= piles[0] / 2;
        pop_heap(piles.begin(), piles.end());
        push_heap(piles.begin(), piles.end());
    }

    int sum {0};

    for (int i {0}; i < size; ++i)
    {
        sum += piles[i];
    }

    return sum;
}

// MAKE A FASTER ONE!!!!

int main()
{
    vector<int> pile1 = {5, 4, 9};
    int k1 = 2;

    vector<int> pile2 = {4, 3, 6, 7};
    int k2 = 3;

    vector<int> pile3 = {1391, 5916};
    int k3 = 3;

    cout << minStoneSum(pile1, k1) << '\n';
    cout << minStoneSum(pile2, k2) << '\n';
    cout << minStoneSum(pile3, k3) << '\n';

    return 0;
}