#ifndef _TRIE_H_
#define _TRIE_H_

#define TRIE_NODE_CHILDREN 26

#include <string.h>

class Trie
{
    class TrieNode
    {
    public:
        friend class Trie;

        TrieNode(bool _isWord = false, bool _isLeaf = false) :
            isWord(_isWord), isLeaf(_isLeaf)
        {
            for (int i {}; i < TRIE_NODE_CHILDREN; ++i)
            {
                children[i] = nullptr;
            }
        }

    private:
        TrieNode* children [TRIE_NODE_CHILDREN];

        bool isWord;
        bool isLeaf;
    };

    TrieNode* copyRoot(const TrieNode* otherRoot);
    void free(TrieNode* node);

public:
    Trie();
    Trie(const Trie& other);
    Trie& operator=(const Trie& other);

    Trie(Trie&& other) noexcept;
    Trie& operator=(Trie&& other) noexcept;

    ~Trie();

    bool insert(const std::string& str);
    bool insert(const char* str);

    bool remove(const std::string& str);
    bool remove(conts char* str);

    bool search(const std::string& str) const;
    bool search(const char* str) const;

private:
    TrieNode* root;
};

#endif
