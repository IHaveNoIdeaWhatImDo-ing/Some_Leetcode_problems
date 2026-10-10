class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        make_heap(nums.begin(), nums.end());

        for (uint32_t i = 0; k > 1; --k, ++i)
        {
            pop_heap(nums.begin(), nums.end() - i);
        }

        return nums[0];
    }
};

class Solution {
public:
    int partition(std::vector<int>& arr, int begin, int size)
    {
        if (size == 1)
        {
            return begin;
        }

        if (arr[begin] < arr[begin + size - 1])
        {
            std::swap(arr[begin], arr[begin + size - 1]);
        }

        int& pivot = arr[begin + size - 1];
        int left = begin;
        int right = begin + size - 1;

        for (;;)
        {
            while (arr[left]    > pivot) ++left;
            while (arr[--right] < pivot)
            {
                if (left == right)
                {
                    break;
                }
            }

            if (left >= right)
            {
                break;
            }

            std::swap(arr[left], arr[right]);
        }

        std::swap(arr[left], pivot);

        return left;
    }

    int quickselect(std::vector<int>& arr, size_t k)
    {
        int begin {};
        int size {static_cast<int>(arr.size())};
        int temp {};

        int part = partition(arr, begin, size);

        while (part ^ k)
        {
            if (part < k)
            {
                temp = begin;
                begin = part + 1;
                size -= begin - temp;
            }
            else if (part > k)
            {
                size = part - begin; 
            }

            part = partition(arr, begin, size);
        }

        return arr[part];
    }

    int findKthLargest(vector<int>& nums, int k) {
        return quickselect(nums, k - 1);
    }
};
