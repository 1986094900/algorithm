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
	
	typedef pair<int, int> PII;
	set<PII> mergeInternal(vector<PII>& internals) {
        set<PII> segs(internals.begin(), internals.end());
        set<PII>::iterator cur = segs.begin();
        while (cur != segs.end()) {
            int end = cur->second;
            int arr = end;
            auto del = cur;
            ++del;
            while (del != segs.end() && del->first <= arr) {
                arr = std::max(arr, del->second);
                segs.erase(del++);
            }
            if (arr > end) {
                PII new_pair = {cur->first, arr};
                segs.erase(cur);
                segs.insert(new_pair);
                cur = segs.find(new_pair);
            }
            ++cur;
        }
        return segs;
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

