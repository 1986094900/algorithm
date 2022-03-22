// 字符串匹配_KMP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// learn from [https://www.cnblogs.com/yjiyjige/p/3263858.html]
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 经典版本
std::vector<int> getNext1(const string& pat) {
    int n = pat.length();
    std::vector<int> next(n);
    next[0] = -1;
    int k = -1;
    int j = 0;
    // next[j] : pat中，在j之前(不包含j)的子串里，前缀 == 后缀 的最长的长度
    // pat = "ABCDEABCDF123456", j = 9, pat[j] = 'F', j之前的子串是"ABCDEABCD", 前缀 == 后缀 最长是"ABCD"
    // "ABCD"长度 = 4, next[9] = 4
    while (j < n - 1) {
        if (k == -1 || pat[j] == pat[k]) {
            next[++j] = ++k;
        }
        else {
            k = next[k];
        }
    }
    return next;
}

// 优化版本, 不优化也是正确的
std::vector<int> getNext2(const string& pat) {
    int n = pat.length();
    std::vector<int> next(n);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < n - 1) {
        if (k == -1 || pat[j] == pat[k]) {
            // 遇到相同的字符跳过
            if (pat[++j] == pat[++k]) {
                next[j] = next[k];
            }
            else {
                next[j] = k;
            }
        }
        else {
            k = next[k];
        }
    }
    return next;
}
int KMP(const std::string& txt, const std::string& pat, const std::vector<int>& next) {
    int i = 0, j = 0;
    int txtLen = txt.length(), patLen = pat.length();
    while (i < txtLen && j < patLen) {
        if (j == -1 || txt[i] == pat[j]) {
            ++i, ++j;
        }
        else {
            //i不动, 只回溯j
            j = next[j];
        }
    }
    if (j == pat.length()) {
        // 返回第一个匹配的下标
        return i - j;
    }
    return -1;
}
int main()
{
    std::string txt = "123ABCDEFABCDGHABGABCDEFABCDGHABG7518";
    std::string pat = "ABCDEFABCDGHABG";
    std::vector<int> next = getNext1(pat);
    int match = KMP(txt, pat, next);
    std::cout << "match : " << match << std::endl;
}
