// max_flow.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;
struct Node {
    int endNode;
    int flow;
    int cap;
};

int START = 0, END = 0, NON = -1;

void printGraph(vector<vector<Node>>& graph, bool isResudual = false) {
    if (isResudual) std::cout << "resudual graph:\n";
    else std::cout << "graph:\n";
    int nodeNum = graph.size() - 1;
    for (int i = 1; i <= nodeNum; ++i) {
        for (int e = 0; e < graph[i].size(); ++e) {
            std::cout << i << "->" << graph[i][e].endNode << " : " << graph[i][e].flow << "/" << graph[i][e].cap<<"\n";
        }
        //std::cout << "\n";
    }
}

void printPath(vector<pair<int, int>>& pre) {
    // print pre
    int cur = END;
    int minFlowInPath = pre[cur].second;
    std::cout << "path:\n";
    while (pre[cur].first != NON) {
        std::cout << cur << "->" << pre[cur].first << " : " << pre[cur].second << "\n";
        minFlowInPath = min(minFlowInPath, pre[END].second);
        cur = pre[cur].first;
    }
}

int getFlow(vector<vector<Node>>& graph) {
    int flow = 0;
    int target = START;
    for (const auto& e : graph[target]) {
        flow += e.flow;
    }
    for (auto& cluster : graph) {
        for (auto& e : cluster) {
            if (e.endNode == target) {
                flow -= e.flow;
            }
        }
    }
    return flow;
}

vector<vector<Node>> getResidualNet(vector<vector<Node>>& graph) {
    int nodeNum = graph.size() - 1;
    vector<vector<Node>> residualGraph(nodeNum + 1);
    for (int i = 0; i < nodeNum; ++i) {
        for (int e = 0; e < graph[i].size(); ++e) {
            int startNode = i;
            int endNode = graph[i][e].endNode;
            int flow = graph[i][e].flow;
            int cap = graph[i][e].cap;

            if (flow < cap) {
                int left = cap - flow;
                Node posEdge;
                posEdge.endNode = endNode;
                posEdge.flow = left;
                posEdge.cap = -1;
                residualGraph[startNode].push_back(posEdge);
            }

            if (flow > 0) {
                Node negEdge;
                negEdge.endNode = startNode;
                negEdge.flow = flow;
                negEdge.cap = -1;
                residualGraph[endNode].push_back(negEdge);
            }
        }
    }
    return residualGraph;
}

bool findAugmentPathBFS(vector<vector<Node>>& graph, vector<pair<int, int>>& pre) {
    vector<vector<Node>> residualNet = getResidualNet(graph);
    
    int nodeNum = graph.size() - 1;
    vector<bool> visited(graph.size(), false);
    // first: node, second: flow
    pre.resize(graph.size());
    queue<int> q;
    q.push(START);
    visited[START] = true;
    pre[START].first = NON;
    pre[START].second = -1;

    bool suc = false;

    // BFS
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto& connect : residualNet[cur]) {
            int next = connect.endNode;
            int flow = connect.flow;
            int cap = connect.cap;

            if (!visited[next]) {
                pre[next].first = cur;
                pre[next].second = flow;
                q.push(next);
                visited[next] = true;
            }
            if (next == END) {
                suc = true;
                break;
            }
        }
    }

    if (suc) {
        printPath(pre);
    }
    return suc;
}

bool findAugmentPathDFS(vector<vector<Node>>& graph, vector<pair<int, int>>& pre) {
    vector<vector<Node>> residualNet = getResidualNet(graph);

    int nodeNum = graph.size() - 1;
    vector<bool> visited(graph.size(), false);
    // first: node, second: flow
    pre.resize(graph.size());
    queue<int> q;
    q.push(START);
    visited[START] = true;
    pre[START].first = NON;
    pre[START].second = -1;

    bool suc = false;

    // BFS
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto& connect : residualNet[cur]) {
            int next = connect.endNode;
            int flow = connect.flow;
            int cap = connect.cap;

            if (!visited[next]) {
                pre[next].first = cur;
                pre[next].second = flow;
                q.push(next);
                visited[next] = true;
            }
            if (next == END) {
                suc = true;
                break;
            }
        }
    }

    if (suc) {
        printPath(pre);
    }
    return suc;
}

int getMaxFlow(vector<vector<Node>>& graph) {
    while (true) {
        vector<pair<int, int>> pre;
        bool suc = findAugmentPathBFS(graph, pre);
        if (!suc) break;

        int minFlowInPath = pre[END].second;
        int cur = END;
        while (pre[cur].first != NON) {
            minFlowInPath = min(minFlowInPath, pre[cur].second);
            cur = pre[cur].first;
        }
        std::cout << "aug added:" << minFlowInPath << "\n";

        cur = END;
        while (pre[cur].first != NON) {
            int start = pre[cur].first;
            int end = cur;

            bool edgeIsGraph = false;
            for (auto& e : graph[start]) {
                if (e.endNode == end) {
                    edgeIsGraph = true;
                    e.flow += minFlowInPath;
                }
            }

            if (!edgeIsGraph) {
                bool check = false;
                for (auto& e : graph[end]) {
                    if (e.endNode = start) {
                        check = true;
                        e.flow -= minFlowInPath;
                    }
                }
                assert(check);
            }
            cur = pre[cur].first;
        }
        // printGraph(graph);
        std::cout << "cur flow : " << getFlow(graph) << "\n\n";
    }
    return getFlow(graph);
}

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
    vector<vector<Node>> graph(edgeNum + 1);
    START = 1, END = nodeNum;
    for (int i = 0; i < edgeNum; ++i) {
        int start, end, cap;
        cin >> start >> end >> cap;
        Node node;
        node.endNode = end;
        node.flow = 0;
        node.cap = cap;
        graph[start].push_back(node);
    }

    std::cout << "\n";

    std::cout << "max flow : " << getMaxFlow(graph);
}


