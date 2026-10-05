#include <iostream>
#include <vector>

void print(int* arr, size_t size)
{
    if (!arr || !size)
        return;

    for (size_t i = 0; i < size; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

/*
int partition(int* arr, size_t size)
{
    if (size == 1)
    {
        return 0;
    }

    if (arr[0] > arr[size - 1])
    {
        std::swap(arr[0], arr[size - 1]);
    }

    int& pivot = arr[size - 1];

    int left = 0;
    int right = size - 1;

    for (;;)
    {
        while (arr[left]    < pivot) ++left;
        while (arr[--right] > pivot)
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

int quickselect(int* arr, size_t size, size_t k)
{
    if (!arr || !size || k >= size)
    {
        return -1;
    }
    
    int part = partition(arr, size);

    while (part ^ k)
    {
        if (part < k)
        {
            arr  += part + 1;
            size -= part + 1;
            k    -= part + 1;
        }
        else if (part > k)
        {
            size = part; 
        }

        part = partition(arr, size);
    }

    return arr[part];
}
*/

int partition(std::vector<int>& arr, int begin, int size)
{
    if (size == 1)
    {
        return begin;
    }

    if (arr[begin] > arr[begin + size - 1])
    {
        std::swap(arr[begin], arr[begin + size - 1]);
    }

    int& pivot = arr[begin + size - 1];
    int left = begin;
    int right = begin + size - 1;

    for (;;)
    {
        while (arr[left]    < pivot) ++left;
        while (arr[--right] > pivot)
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

int main()
{
    /*
    //int arr[] = {5, 10, 4, 3, 6, 12, 7, 8, 2, 9, 11, 1};
    //int arr[] = {3, 2, 1, 5, 6, 4};
    //int arr[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int arr[] = {3, 2, 3, 1, 6, 4, 5, 5, 2};
    //int arr[] = {3, 2, 3};

    print(arr, 9);
    std::cout << quickselect(arr, 9, 7) << '\n';
    print(arr, 9);
    */

    //std::vector<int> nums = {3, 2, 3, 1, 6, 4, 5, 5, 2};
    //std::vector<int> nums = {3, 2, 3};
    //std::vector<int> nums = {2, 3};
    std::vector<int> nums = {3, 2, 3, 1, 2, 4, 5, 5, 6};

    std::cout << quickselect(nums, 2) << '\n';
    print(nums.data(), nums.size());

    return 0;
}
