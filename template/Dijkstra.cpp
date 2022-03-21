// Dijkstra.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

/**
9 6
0 1 16
0 2 13
2 1 4
1 3 12
3 2 9
2 4 14
4 3 7
4 5 4
3 5 20
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;

typedef std::pair<int, int> PII;
int START = 0, END = 0, NON = -1;

vector<int> dijkstra(vector<vector<PII>>& graph, int start) {
    int n = graph.size();
    vector<int> dis(n, INT_MAX);
    vector<int> parent(n, -1);
    dis[start] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.push({ 0, start });
    while (!pq.empty()) {
        // auto [cost, cur] = pq.top();
        auto& curPair = pq.top();
        int cost = curPair.first;
        int cur = curPair.second;
        pq.pop();
        if (cost > dis[cur]) continue;
        for (auto& e : graph[cur]) {
            int edgeCost = e.first;
            int to = e.second;
            if (cost + edgeCost < dis[to]) {
                dis[to] = cost + edgeCost;
                pq.push({ dis[to], to });
                parent[to] = cur;
            }
        }
    }
    return dis;
}

int main()
{
    int edgeNum = 0, nodeNum = 0;
    cin >> edgeNum >> nodeNum;
    vector<vector<PII>> graph(nodeNum);
    START = 0, END = nodeNum - 1;
    for (int i = 0; i < edgeNum; ++i) {
        int start, end, val;
        cin >> start >> end >> val;
        graph[start].push_back({ val, end });
    }

    std::cout << "graph:\n";
    for (int n = 0; n < nodeNum; ++n) {
        for (auto& e : graph[n]) {
            std::cout << n << "->" << e.first << " : " << e.second << "\n";
        }
    }
    vector<int> dis = dijkstra(graph, 0);
    std::cout << "dis of each node\n";
    for (int i = START; i <= END; ++i) {
        std::cout << i << " : " << dis[i] << "\n";
    }
}