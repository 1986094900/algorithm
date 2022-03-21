// 按空格分割字符串.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
using namespace std;

vector<string> split(const string& str) {
    vector<string> vec;
    int len = str.length();
    for (int i = 0; i < len; ++i) {
        if (str[i] == ' ') continue;
        else {
            int cur = i;
            int subLen = 0;
            int num = 0;
            while (cur < len && str[cur] != ' ') {
                ++cur;
                ++subLen;
            }
            vec.push_back(str.substr(i, subLen));
            i = cur;
        }
    }
    return vec;
}

int main()
{
    auto res = split("123  456  789 abc   def   ");
    for (auto item : res) {
        std::cout << item << std::endl;
    }
}