#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
    You are given two 0-indexed strings source and target, both of
length n and consisting of lowercase English characters. You are also
given two 0-indexed string arrays original and changed, and an integer
array cost, where cost[i] represents the cost of converting the string
original[i] to the string changed[i].

    You start with the string source. In one operation, you can pick a
substring x from the string, and change it to y at a cost of z if there
exists any index j such that cost[j] == z, original[j] == x, and
changed[j] == y. You are allowed to do any number of operations, but
any pair of operations must satisfy either of these two conditions:

    - The substrings picked in the operations are source[a..b] and
      source[c..d] with either b < c or d < a. In other words, the
      indices picked in both operations are disjoint.
    - The substrings picked in the operations are source[a..b] and
      source[c..d] with a == c and b == d. In other words, the indices
      picked in both operations are identical.

    Return the minimum cost to convert the string source to the string
target using any number of operations. If it is impossible to convert
source to target, return -1.

    Note that there may exist indices i, j such that
original[j] == original[i] and changed[j] == changed[i].
*/

using uint64 = unsigned long long int;

static constexpr uint64 maxULL {~0ull};

static constexpr int childrenCount {26};

uint64 adjMat[200][200];

uint64 dist[1001];

struct TrieNode
{
    TrieNode* children[childrenCount];
    int id;
};

static constexpr int trieNodeSize {200000}; // 2 * 100 words * 1000 characters
static int lastNode {};
static int nodeID {};

static TrieNode nodePool[trieNodeSize];

struct Trie
{
    Trie() : root(nullptr)
    {
        root = &nodePool[lastNode++];
        memset(root->children, 0x0, childrenCount * sizeof(TrieNode*));
        root->id = -1;
    }

    void insert(const char* str)
    {
        char currChar {*str};
        TrieNode* currNode {root};
        int idx;

        while (currChar)
        {
            idx = currChar - 'a';

            if (!currNode->children[idx])
            {
                currNode->children[idx] = &nodePool[lastNode++];
                memset(currNode->children[idx], 0x0, childrenCount * sizeof(TrieNode*));
                currNode->children[idx]->id = -1;
            }

            currNode = currNode->children[idx];
            currChar = *(++str);
        }

        if (currNode->id == -1)
        {
            currNode->id = nodeID++;
        }
    }

    int searchID (const char* str)
    {
        char currChar {*str};
        TrieNode* currNode {root};
        int idx;

        while (currChar && currNode->children[idx = currChar - 'a'])
        {
            currNode = currNode->children[idx];
            currChar = *(++str);
        }

        return currNode->id;
    }

    TrieNode* root;
};

long long minimumCost(const string& source, const string& target, vector<string>& original, vector<string>& changed, vector<int>& cost)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    //uint64 res {0ull};

    size_t size {original.size()};

    size_t k;
    size_t i;
    size_t j;

    TrieNode* srcPtr;
    TrieNode* trgPtr;

    // resetting the node pool
    lastNode = 0;
    nodeID = 0;

    Trie trie;
    
    // assigning indices to all unique strings in original and changed
    for (i = 0; i < size; ++i)
    {
        trie.insert(original[i].c_str());
    }

    for (i = 0; i < size; ++i)
    {
        trie.insert(changed[i].c_str());
    }

    // initiating and adjacency matrix for floyd-warshall
    memset(adjMat, 0xFF, nodeID * 200 * sizeof(uint64));
    
    memset(dist, 0xFF, (source.size() + 1) * sizeof(uint64));
    dist[0] = 0ull;

    size = static_cast<size_t>(nodeID);
    for (i = 0; i < size; ++i)
    {
        adjMat[i][i] = 0ull;
    }

    size = original.size();
    for (i = 0; i < size; ++i)
    {
        // j and k are row and column here
        j = static_cast<size_t>(trie.searchID(original[i].c_str()));
        k = static_cast<size_t>(trie.searchID(changed[i].c_str()));

        if (adjMat[j][k] > static_cast<uint64>(cost[i]))
        {
            adjMat[j][k] = static_cast<uint64>(cost[i]);
        }
    }

    // floyd-warshall
    size = static_cast<size_t>(nodeID);
    for (k = 0; k < size; ++k)
    {
        for (i = 0; i < size; ++i)
        {
            for (j = 0; j < size; ++j)
            {
                if (adjMat[i][k] == maxULL || adjMat[k][j] == maxULL)
                {
                    continue;
                }

                if (adjMat[i][j] > adjMat[i][k] + adjMat[k][j])
                {
                    adjMat[i][j] = adjMat[i][k] + adjMat[k][j];
                }
            }
        }
    }

    size = source.size();
    for (i = 0; i < size; ++i)
    {
        if (dist[i] == maxULL)
        {
            continue;
        }

        if (source[i] == target[i])
        {
            dist[i + 1] = min(dist[i + 1], dist[i]);
        }

        srcPtr = trie.root;
        trgPtr = trie.root;

        for (j = i; j < size; ++j)
        {
            srcPtr = srcPtr->children[source[j] - 'a'];
            trgPtr = trgPtr->children[target[j] - 'a'];

            if (!srcPtr || !trgPtr)
            {
                break;
            }

            if
            (
                srcPtr && trgPtr &&
                srcPtr->id != -1 &&
                trgPtr->id != -1
            )
            {
                if (adjMat[srcPtr->id][trgPtr->id] < maxULL)
                {
                    dist[j + 1] = min(dist[j + 1], dist[i] + adjMat[srcPtr->id][trgPtr->id]);
                }
            }
        }
    }

    return static_cast<long long>(dist[size]);
}

int main()
{
    string source1("abcd");
    string target1("acbe");
    vector<string> original1 {"a","b","c","c","e","d"};
    vector<string> changed1 {"b","c","b","e","b","e"};
    vector<int> cost1 {2,5,5,1,2,20};
    
    string source2("abcdefgh");
    string target2("acdeeghh");
    vector<string> original2 {"bcd","fgh","thh"};
    vector<string> changed2 {"cde","thh","ghh"};
    vector<int> cost2 {1,3,5};
    
    string source3("abcdefgh");
    string target3("addddddd");
    vector<string> original3 {"bcd","defgh"};
    vector<string> changed3 {"ddd","ddddd"};
    vector<int> cost3 {100,1578};
    
    string source4("abbbeebebehbbhhhbeab");
    string target4("aehebehebaeaebbaahhb");
    vector<string> original4 {"b","b","e","e","h","h","h","b","e","a"};
    vector<string> changed4 {"e","h","b","a","e","b","a","a","h","h"};
    vector<int> cost4 {10,2,9,10,7,8,10,10,6,9};

    cout << minimumCost(source1, target1, original1, changed1, cost1) << '\n';
    cout << minimumCost(source2, target2, original2, changed2, cost2) << '\n';
    cout << minimumCost(source3, target3, original3, changed3, cost3) << '\n';
    cout << minimumCost(source4, target4, original4, changed4, cost4) << '\n';

    return 0;
}
