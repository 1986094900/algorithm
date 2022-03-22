// 字符串匹配_字符串哈希.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

// unsigned long long自动取模
typedef unsigned long long ULL;
ULL code = 37;

// 寻找重复的DNA序列
vector<string> findRepeatedDnaSequences(string s) {
    int n = s.length();
    vector<ULL> preSum(n + 1);
    vector<ULL> db(n + 1);
    preSum[0] = 0;
    db[0] = 1;
    for (int i = 1; i <= n; ++i) {
        preSum[i] = preSum[i - 1] * code + s[i - 1];
        db[i] = db[i - 1] * code;
    }
    std::vector<string> vec;
    std::unordered_set<ULL> store;
    std::unordered_set<ULL> ansHash;

    int len = 10;
    for (int i = 1; i + len - 1 <= n; ++i) {
        int x = i, y = i + len - 1;
        ULL cur = preSum[y] - preSum[x - 1] * db[len];
        if (store.count(cur)) {
            if (ansHash.count(cur) == 0) {
                vec.push_back(s.substr(i - 1, len));
                ansHash.insert(cur);
            }
        }
        else {
            store.insert(cur);
        }
    }
    return vec;
}
int main()
{
    string DNA = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
    vector<string> ans = findRepeatedDnaSequences(DNA);
    for (auto& item : ans) {
        std::cout << item << std::endl;
    }
}

