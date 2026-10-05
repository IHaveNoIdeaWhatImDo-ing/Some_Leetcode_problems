#include <vector>
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

void print(vector<int>& vec)
{
    for (int num : vec)
    {
        cout << num << ' ';
    }
    cout << '\n';
}

vector<int> maxSubsequence(vector<int>& nums, int k)
{
    auto comp = greater{};
    vector<int> res {nums};

    int to_remove = nums.size() - k;
    int i {};

    make_heap(res.begin(), res.end(), comp);

    for (; i < to_remove; ++i)
    {
        pop_heap(res.begin(), res.end(), comp);
        res.pop_back();
    }

    unordered_map<int, short> to_inlude {};
    for (int num : res)
    {
        ++to_inlude[num];
    }

    i = 0;
    for (int num : nums)
    {
        if (to_inlude[num]-- > 0)
        {
            res[i++] = num;
        }
    }

    return res;
}

int main()
{
    vector<int> nums1 = {2,1,3,3};
    int k1 = 2;
    
    vector<int> nums2 = {-1,-2,3,4};
    int k2 = 3;
    
    vector<int> nums3 = {3,4,3,3};
    int k3 = 2;

    vector<int> res1 = maxSubsequence(nums1, k1);
    print(res1);

    vector<int> res2 = maxSubsequence(nums2, k2);
    print(res2);

    vector<int> res3 = maxSubsequence(nums3, k3);
    print(res3);

    return 0;
}
