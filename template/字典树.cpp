// 字典树.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
using namespace std;

class Trie {
public:
    Trie() {
        memset(children, 0, sizeof children);
        isEnd = false;
    }

    void insert(const string& word) {
        Trie* cur = this;
        for (auto ch : word) {
            if (cur->children[ch - 'a'] == NULL) {
                cur->children[ch - 'a'] = new Trie();
            }
            cur = cur->children[ch - 'a'];
        }
        cur->isEnd = true;
    }

    bool search(const string& word) {
        Trie* cur = this;
        for (auto ch : word) {
            cur = cur->children[ch - 'a'];
            if (cur == NULL) {
                return false;
            }
        }
        return cur->isEnd;
    }

    bool startsWith(const string& prefix) {
        Trie* cur = this;
        for (auto ch : prefix) {
            cur = cur->children[ch - 'a'];
            if (cur == NULL) {
                return false;
            }
        }
        return true;
    }
private:
    Trie* children[26];
    bool isEnd;
};

int main()
{
    Trie tree;
    string list[5] = { "aaa", "aab", "aac", "abb", "abc" };
    for (int i = 0; i < 5; ++i) {
        tree.insert(list[i]);
    }
}