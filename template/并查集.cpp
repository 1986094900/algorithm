// 并查集.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
using namespace std;

vector<int> parent;

void init() {
    int n = parent.size();
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
}

int find(int a) {
    if (parent[a] == a) return a;
    return parent[a] = find(parent[a]);
}

void join(int a, int b) {
    int pa = find(a);
    int pb = find(b);
    if (pa != pb) {
        if (pa < pb) parent[pb] = pa;
        else         parent[pa] = pb;
    }
}

int main()
{
    
}

