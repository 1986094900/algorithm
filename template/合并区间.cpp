// 合并区间.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <set>

using namespace std;

class CountIntervals {
public:
    int sum = 0;
    set<pair<int, int>> segs;
    CountIntervals() {}

    void add(int left, int right) {
        int L = left, R = right;
        auto it = segs.lower_bound({ left - 1, 0 });
        while (it != segs.end()) {
            if (it->second > right + 1) break;
            L = min(L, it->second);
            R = max(R, it->first);
            sum -= it->first - it->second + 1;
            it = segs.erase(it);
        }
        sum += R - L + 1;
        segs.insert({ R, L });
    }

    int count() {
        return sum;
    }
};

int main()
{
    CountIntervals ci;
    ci.add(0, 10);
    ci.add(5, 19);
    std::cout << "len : " << ci.count() << std::endl;
    return 0;
}

