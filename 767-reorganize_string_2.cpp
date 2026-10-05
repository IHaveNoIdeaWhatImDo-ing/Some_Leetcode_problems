#include <cmath>
#include <array>
#include <cstdint>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

static void print(const array<pair<char, int16_t>, 26>& arr)
{
    for (const pair<char, int16_t>& p : arr)
    {
        cout << p.first << ": " << p.second << '\n';
    }
    cout << "--------\n";
}

string reorganizeString(string s)
{
    array<pair<char, int16_t>, 26> uset;
    int16_t size {0};

    string out {""};

    for (uint8_t i = 0; i < 26; ++i)
    {
        uset[i] = move(pair<char, uint16_t>('a' + i, 0));
    }

    for (char letter : s)
    {
        ++uset[letter - 'a'].second;
    }


    for (uint8_t i = 0; i < 26; ++i)
    {
        if (uset[i].second)
        {
            ++size;
        }
    }

    cout << "size = " << size << '\n';
    print(uset);

    sort(uset.begin(), uset.end(),
    [](const pair<char, int16_t>& l, const pair<char, int16_t>& r)
    {
        return l.second > r.second;
    });

    print(uset);

    int8_t head = 0;

    while (size)
    {
        while (uset[head].second > 0)
        {
            out += uset[head].first;
            --uset[head].second;

            if (size > 1)
            {
                out += uset[head + size - 1].first;
                --uset[head + size - 1].second;

                if (uset[head + size - 1].second < 1)
                {
                    --size;
                }
            }
        }

        cout << out << '\n';

        ++head;
        --size;
    }

    return out;
}

int main()
{   
    cout << reorganizeString("aab") << "\n|-----------|\n";
    //cout << reorganizeString("aaab") << "\n|-----------|\n";
    cout << reorganizeString("vvvlo") << "\n|-----------|\n";
    cout << reorganizeString("asdfgh") << "\n|-----------|\n";
    cout << reorganizeString("ihvuaidggs") << "\n|-----------|\n";
    cout << reorganizeString("aaaabbbbccccdddd") << "\n|-----------|\n";
    cout << reorganizeString("aaaabbbbccccddddd") << "\n|-----------|\n";
    cout << reorganizeString("ogccckcwmbmxtsbmozli") << "\n|-----------|\n";

    return 0;
}
