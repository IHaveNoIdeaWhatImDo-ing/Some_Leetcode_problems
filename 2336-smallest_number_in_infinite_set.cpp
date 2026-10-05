#include <queue>
#include <vector>
#include <cstddef>
#include <iostream>
#include <algorithm>

using namespace std;

class SmallestInfiniteSet
{
    unsigned short lower_end = 1U;
    priority_queue<unsigned short, vector<unsigned short>, greater<unsigned short>> removed_added_back;
    bool elems[1000] {0};

public:
    SmallestInfiniteSet() {}
    
    int popSmallest()
    {
        unsigned int res;

        if (!removed_added_back.empty())
        {
            res = removed_added_back.top();
            removed_added_back.pop();
            elems[res - 1] = false;
        }
        else
        {
            res = lower_end++;
        }

        return static_cast<int>(res);
    }
    
    void addBack(int num)
    {
        if (num < lower_end && !elems[num - 1])
        {
            elems[num - 1] = true;
            removed_added_back.push(num);
        }
    }
};

int main()
{
    SmallestInfiniteSet* obj = new SmallestInfiniteSet();
    int param_1 = obj->popSmallest();
    obj->addBack(1);
    int param_2 = obj->popSmallest();
    int param_3 = obj->popSmallest();
    int param_4 = obj->popSmallest();
    obj->addBack(2);
    obj->addBack(3);
    int param_5 = obj->popSmallest();
    int param_6 = obj->popSmallest();

    cout << param_1 << ' ' << param_2 << ' ' << param_3 << ' ' << param_4 << ' ' << param_5 << ' ' << param_6;

    delete obj;

    return 0;
}
