// 去重全排列.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
using namespace std;

int ans = 0;

void rankAll(vector<int>& nums, vector<bool>& used, vector<int>& path, int depth) {
    if (depth == nums.size()) {
        // get one path
        for (auto item : path) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        ++ans;
    }
    for (int i = 0; i < nums.size(); ++i) {
        if (used[i]) continue;
        used[i] = true;
        path[depth] = nums[i];
        rankAll(nums, used, path, depth + 1);
        used[i] = false;
    }
}

int main()
{
    vector<int> nums = { 1, 2, 3, 4 };
    int n = nums.size();
    vector<bool> used(n, false);
    vector<int> path(n, -1);
    rankAll(nums, used, path, 0);
    std::cout << "total : " << ans << std::endl;
}