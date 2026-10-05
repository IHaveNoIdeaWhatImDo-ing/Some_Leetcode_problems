#include <vector>
#include <cstddef>
#include <iostream>
#include <algorithm>

using namespace std;

void print(const vector<int>& arr)
{
    for (int num : arr)
    {
        cout << num << ' ';
    }
    cout << '\n';
}

/*
vector<int> numberGame(vector<int>& nums)
{
    vector<int> arr (static_cast<int>(nums.size()));

    auto comp = std::greater<int>{};
    unsigned char i {1};
    unsigned char size {static_cast<unsigned char>(nums.size())};

    make_heap(nums.begin(), nums.end(), comp);

    for (unsigned char count {}; i < size; i += 2)
    {
        arr[i] = nums[0];

        pop_heap(nums.begin(), nums.end() - count++, comp);

        arr[i - 1] = nums[0];
        
        pop_heap(nums.begin(), nums.end() - count++, comp);
    }

    return arr;
}
*/

vector<int> numberGame(vector<int>& nums)
{
    sort(nums.begin(), nums.end());

    unsigned char i {};
    unsigned char size {static_cast<unsigned char>(nums.size())};

    for (; i < size; i += 2)
    {
        nums[i] ^= nums[i + 1];
        nums[i + 1] ^= nums[i];
        nums[i] ^= nums[i + 1];
    }

    return nums;
}

int main()
{
    vector<int> nums1 = {5,4,2,3};
    vector<int> nums2 = {2,5};

    vector<int> res1 = numberGame(nums1);
    vector<int> res2 = numberGame(nums2);

    print(res1);
    print(res2);

    return 0;
}
