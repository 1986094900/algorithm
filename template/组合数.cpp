// 求组合数.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
using namespace std;

// 单个求 m中选n个的数量
int permutation(int m, int n) {
    return n == 0 ? 1 : permutation(m, n - 1) * (m - n + 1);
}


void com(int m, int n) {
    // 批量求 m中选n个的数量
    vector<vector<int>> comb(m, vector<int>(n));
    comb[0][0] = 1;
    for (int i = 1; i <= m; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j <= n; ++j) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }
}

int main()
{
    
}