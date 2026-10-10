#include <cmath>
#include <cstdint>
#include <utility>
#include <iostream>
#include <algorithm>
#include <string_view>

using namespace std;

string reorganizeString(string s)
{
    pair<char, uint16_t> uset[26] {make_pair('a', 0)};
    string out {""};
    string word {""};
    uint16_t word_window {0};

    for (char letter : s)
    {
        ++uset[letter - 'a'].second;
    }

    const pair<char, uint16_t>* big = uset;
    uint16_t sum = 0;
    string big_word;

    for (uint8_t i = 0; i < 26; ++i)
    {
        uset[i].first = 'a' + i;

        if (big->second < uset[i].second)
        {
            big = uset + i;
        }

        sum += uset[i].second;
    }

    if (sum - big->second + 1 < big->second)
    {
        return "";
    }

    if (big->second == 1)
    {
        return s;
    }

    for (uint8_t i = 0; i < 26; ++i)
    {
        if (uset[i].second)
        {
            if (uset[i].second != big->second)
            {
                word += uset[i].first;
            }
            else 
            {
                big_word += uset[i].first;
            }
        }
    }

    sort(word.begin(), word.end(), [&uset](char l, char r)
    {
        return uset[l - 'a'].second > uset[r - 'a'].second;
    });

    word_window = min(word.size(), (size_t)ceil((sum - big->second) / (big->second - 1.0)));

    cout << word_window << ' ' << word << ' ' << big_word << "\n\n";

    for (uint16_t i = 0; i < big->second - 1; ++i)
    {
        string_view word_view(word.c_str() + word.size() - word_window);

        out += big_word;
        out += word_view;
        
        for (char chr : word_view)
        {
            --uset[chr - 'a'].second;
        }

        while (!word.empty() && uset[word.back() - 'a'].second == 0)
        {
            word.pop_back();
        }
    }
    out += big_word;

    return out;
}

int main()
{   
    cout << reorganizeString("aab") << "\n---------\n";
    cout << reorganizeString("aaab") << "\n---------\n";
    cout << reorganizeString("vvvlo") << "\n---------\n";
    cout << reorganizeString("asdfgh") << "\n---------\n";
    cout << reorganizeString("ihvuaidggs") << "\n---------\n";
    cout << reorganizeString("aaaabbbbccccdddd") << "\n---------\n";
    cout << reorganizeString("aaaabbbbccccddddd") << "\n---------\n";
    cout << reorganizeString("ogccckcwmbmxtsbmozli") << "\n---------\n";

    return 0;
}
