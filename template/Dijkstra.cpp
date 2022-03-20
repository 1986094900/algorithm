// Dijkstra.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;

int START = 0, END = 0, NON = -1;

/**
9 6
1 2 16
1 3 13
3 2 4
2 4 12
4 3 9
3 5 14
5 4 7
5 6 4
4 6 20
4 6 20
*/

int main()
{
    int edgeNum = 0, nodeNum = 0;
    cin >> edgeNum >> nodeNum;
    vector<vector<pair<int, int>>> graph(nodeNum + 1);
    START = 1, END = nodeNum;
    for (int i = 0; i < edgeNum; ++i) {
        int start, end, val;
        cin >> start >> end >> val;
        pair<int, int> edge = std::make_pair(val, end);
        graph[start].push_back(edge);
    }

    std::cout << "graph:\n";
    for (int n = 1; n <= nodeNum; ++n) {
        for (auto& e : graph[n]) {
            std::cout << n << "->" << e.first << " : " << e.second << "\n";
        }
    }
    std::cout << "\n";

    vector<int> dis(nodeNum + 1, INT_MAX);
    vector<int> parent(nodeNum + 1, NON);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(std::make_pair(0, START));
    dis[START] = 0;

    while (!pq.empty()) {
        auto item = pq.top();
        pq.pop();
        int cur = item.second;
        int curDisFromSource = item.first;

        if (curDisFromSource > dis[cur]) continue;

        for (auto& e : graph[cur]) {
            int next = e.second;
            int edgeCost = e.first;
            int nextDisFromSource = curDisFromSource + edgeCost;
            if (nextDisFromSource < dis[next]) {
                dis[next] = nextDisFromSource;
                pq.push(std::make_pair(nextDisFromSource, next));
                parent[next] = cur;
            }
        }
    }

    std::cout << "\n";
    std::cout << "dis of each node\n";
    for (int i = START; i <= END; ++i) {
        std::cout << i << " : " << dis[i] << "\n";
    }

    std::cout << "\n";
    std::cout << "path:\n";
    int cur = END;
    while (cur != NON) {
        std::cout << cur << ":" << dis[cur] <<"\n";
        cur = parent[cur];
    }
}


