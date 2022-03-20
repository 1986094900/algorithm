/*---------------------------------
 *File name: 最小费用最大流.cpp
 *Creation date: 2020-05-20 11:56
test case
4 5 3 2
3 1 30 2
3 2 20 3
1 2 20 1
1 0 30 9
0 2 40 5
*-------------------------------*/
#include<queue>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

class Edge {
public:
	Edge(int to, int flow, int cost) : to_(to), flow_(flow), cost_(cost) {}
public:
	int to_;
	int cost_;
	int flow_;
};

class MaxFlow {
public:
	MaxFlow(int node_num, int edge_num, int start, int end) {
		node_num_ = node_num;
		edge_num_ = edge_num;
		start_ = start;
		end_ = end;
		edge_id_ = 0;
		vis_.resize(node_num);
		flow_.resize(node_num);
		cost_.resize(node_num);
		pre_node_.resize(node_num);
		from_edge_.resize(node_num);
		graph_.resize(node_num);
		edges_.reserve((edge_num << 1));
	}

	void addEdge(int u, int v, int f, int c) {
		graph_[u].push_back(static_cast<int>(edges_.size()));
		edges_.emplace_back(v, f, c);
	}

	bool SPFA() {
		for (int i = 0; i < node_num_; ++i) {
			vis_[i] = false;
			flow_[i] = cost_[i] = INF;
		}
		queue<int> q;
		q.push(start_);
		vis_[start_] = 1, cost_[start_] = 0, pre_node_[end_] = -1;//标记start_入队
		while (!q.empty()) {
			int cur = q.front(); q.pop();
			vis_[cur] = 0;//标记cur出队
			for (auto edge_id : graph_[cur]) {
				int to = edges_[edge_id].to_;
				//残量大于0且满足松弛条件
				if (edges_[edge_id].flow_ > 0 && cost_[to] > cost_[cur] + edges_[edge_id].cost_) {
					cost_[to] = cost_[cur] + edges_[edge_id].cost_;
					pre_node_[to] = cur;     //to的前驱结点更新为cur
					from_edge_[to] = edge_id;//连接cur与to的边的序号为i
					flow_[to] = min(flow_[cur], edges_[edge_id].flow_);//更新流量,取这条path上flow_的最小值 
					if (!vis_[to]) {
						vis_[to] = 1;
						q.push(to);
					}
				}
			}
		}
		bool res = (pre_node_[end_] != -1);
		return res;
	}

	bool BFS() {
		for (int i = 0; i < node_num_; ++i) {
			vis_[i] = false;
			flow_[i] = INF;
		}
		pre_node_[end_] = -1;
		pre_node_[start_] = start_;
		queue<int> q;
		q.push(start_);
		vis_[start_] = true;
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			bool isEnd = false;
			for (auto edge_id : graph_[cur]) {
				if (edges_[edge_id].flow_ == 0) continue;
				int next = edges_[edge_id].to_;
				if (vis_[next]) continue;
				pre_node_[next] = cur;
				from_edge_[next] = edge_id;
				flow_[next] = std::min(flow_[cur], edges_[edge_id].flow_);
				q.push(next);
				vis_[next] = true;
				if (next == end_) {
					isEnd = true;
					break;
				}
			}
			if (isEnd) break;
		}
		return pre_node_[end_] != -1;
	}

	std::pair<int, int> minCostMaxFlow() {
		int maxFlow = 0, minCost = 0;
		while (SPFA()) {
			int cur = end_;
			maxFlow += flow_[end_];
			minCost += flow_[end_] * cost_[end_];
			while (cur != start_) {//从end_点回溯更新残量
				edges_[from_edge_[cur]].flow_ -= flow_[end_];
				edges_[from_edge_[cur] ^ 1].flow_ += flow_[end_];
				cur = pre_node_[cur];
			}
		}
		printf("%d %d\n", maxFlow, minCost);
		return { maxFlow, minCost };
	}

	int minCutMaxFlow() {
		int maxFlow = 0;
		while (BFS()) {
			int cur = end_;
			maxFlow += flow_[end_];
			while (cur != start_) {//从end_点回溯更新残量
				edges_[from_edge_[cur]].flow_ -= flow_[end_];
				edges_[from_edge_[cur] ^ 1].flow_ += flow_[end_];
				cur = pre_node_[cur];
			}
		}
		printf("%d\n", maxFlow);
		return maxFlow;
	}
private:
	std::vector<bool> vis_;               //vis_[i]:节点i是否访问过
	std::vector<int> flow_;		         //flow_[i]:从源点到i的流量
	std::vector<int> cost_;		         //cost_[i]:从源点到i的总花费
	std::vector<int> pre_node_;	         //pre_node_[i]:值为点，代表i点的前驱点
	std::vector<int> from_edge_;	         //from_edge_[i]:值为边号，连接pre_node_[i]和i的边的序号
	std::vector<std::vector<int>> graph_; //node连接的edge_id
	std::vector<Edge> edges_;
	int edge_num_;
	int node_num_;
	int start_;
	int end_;
	int edge_id_;
	const int INF = 0x3f3f3f3f;
};

int main() {
	int node_num, edge_num, start, end;
	std::cin >> node_num >> edge_num >> start >> end;
	MaxFlow maxFlow(node_num, edge_num, start, end);
	for (int i = 0; i < edge_num; ++i) {
		int u, v, w, c;
		std::cin >> u >> v >> w >> c;
		maxFlow.addEdge(u, v, w, c);
		maxFlow.addEdge(v, u, 0, -c);
	}
	maxFlow.minCostMaxFlow();
	//maxFlow.minCutMaxFlow();
	return 0;
}