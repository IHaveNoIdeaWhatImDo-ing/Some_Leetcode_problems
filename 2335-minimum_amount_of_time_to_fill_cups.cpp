#include <vector>
#include <cstddef>
#include <iostream>
#include <algorithm>

using namespace std;

/*
amount[0] - cold water cups,
amount[1] - warm water cups,
amount[2] - hot water cups
*/
int fillCups(vector<int>& amount)
{
    int res {};
    int diff {};

    if (amount[0] > amount[1])
    {
        amount[0] ^= amount[1];
        amount[1] ^= amount[0];
        amount[0] ^= amount[1];
    }
    if (amount[1] > amount[2])
    {
        amount[1] ^= amount[2];
        amount[2] ^= amount[1];
        amount[1] ^= amount[2];
    }
    if (amount[0] > amount[1])
    {
        amount[0] ^= amount[1];
        amount[1] ^= amount[0];
        amount[0] ^= amount[1];
    }
    
    if (amount[0] + amount[1] <= amount[2])
    {
        return amount[2];
    }

    res = amount[2];
    diff = amount[0] + amount[1] - amount[2];

    return res + (diff - min(diff / 2, amount[0]));
}

int main()
{
    vector<int> amount1 = {1, 4, 2};
    vector<int> amount2 = {5, 4, 4};
    vector<int> amount3 = {0, 5, 0};
    vector<int> amount4 = {5, 7, 8};

    cout << fillCups(amount1) << '\n';
    cout << fillCups(amount2) << '\n';
    cout << fillCups(amount3) << '\n';
    cout << fillCups(amount4) << '\n';

    return 0;
}
