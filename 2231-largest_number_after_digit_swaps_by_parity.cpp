#include <vector>
#include <cstddef>
#include <iostream>
#include <algorithm>

using namespace std;

int intlen(int num)
{
    int len {};

    while (num)
    {
        ++len;
        num /= 10;
    }

    return len;
}

int largestInteger(int num)
{
    char i {};
    char j {};
    char count {};
    unsigned char digit {};
    int num_temp {};

    int res {};

    vector<bool> digit_parity(intlen(num));
    unsigned char digits[10]     {0};
    unsigned char res_digits[10] {0};

    for (num_temp = num, i = digit_parity.size() - 1; num_temp; num_temp /= 10, --i)
    {
        digit = (num_temp % 10);

        digit_parity[i] = digit % 2;

        ++digits[digit];
    }

    i = 9;
    j = 8;
    for (bool is_odd : digit_parity)
    {
        if (is_odd)
        {
            for (; i > 0; i -= 2)
            {
                if (digits[i])
                {
                    res_digits[count++] = i;
                    --digits[i];
                    break;
                }
            }
        }
        else
        {   
            for (; j >= 0; j -= 2)
            {
                if (digits[j])
                {
                    res_digits[count++] = j;
                    --digits[j];
                    break;
                }
            }
        }
    }

    for (i = 0; i < count; ++i)
    {
        res = res * 10 + res_digits[i];
    }

    return res;
}

int main()
{
    int num1 = 1234;
    int num2 = 65875;
    int num3 = 1;
    int num4 = 12;
    int num5 = 21;
    int num6 = 35980387;
    int num7 = 60;

    cout << largestInteger(num1) << '\n';
    cout << largestInteger(num2) << '\n';
    cout << largestInteger(num3) << '\n';
    cout << largestInteger(num4) << '\n';
    cout << largestInteger(num5) << '\n';
    cout << largestInteger(num6) << '\n';
    cout << largestInteger(num7) << '\n';

    return 0;
}
