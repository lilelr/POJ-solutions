//http://poj.org/problem?id=2387  Dijkstra
#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
#include <stack>
#include <cstring>

using namespace std;
#define M(a, b) memset(a,b,sizeof(a))
const int INF = 0x3f3f3f3f;
const int maxn = 110;

struct qnode { // 顶点
    int v; // 顶点编号，从1开始
    int c;  // 表示距离

    qnode(int _v = 0, int _c = 0) : v(_v), c(_c) {}

    bool operator<(const qnode &r) const {
        return c > r.c; // 注意是优先队列的比较
    }
};

struct Edge { // 边
    int v; // 边连接的末端点
    int cost; // 边的权值

    Edge(int _v = 0, int _cost = 0) : v(_v), cost(_cost) {}
};

vector<Edge> E[maxn]; //只需初始化边即可
bool vis[maxn];
int dist[maxn]; // 从每个顶点出发，到达终点n最短距离, 顶点编号，从1开始

/**
 * 使用优先队列优化 复杂度O(ElogE)
 * 注意对 vector<Edge> E[maxn] 进行初始化后加边
 * @param n 顶点数
 * @param start 开始的顶点
 */
int Dijkstra(int n, int start) {
    M(vis, false);
    for (int i = 1; i <= n; i++)dist[i] = INF;
    priority_queue<qnode> que;
    dist[start] = 0;
    que.push(qnode(start, 0));
    qnode tmp;
    while (!que.empty()) {
        tmp = que.top();
        que.pop();
        int u = tmp.v; // 取出当前顶点
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = 0; i < E[u].size(); i++) { // 遍历当前顶点的边
            int v = E[tmp.v][i].v;
            int cost = E[u][i].cost;
            if (!vis[v] && dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost; // 更新到 v 的距离
                que.push(qnode(v, dist[v]));
            }
        }
    }
    return dist[1];
}

void add_edge(int u, int v, int w) {
    E[u].push_back(Edge(v, w));
}

int main() {
    int T, N;
    cin >> T >> N;
    int v, l_v, w;
    for (int i = 1; i <= T; i++) {
        cin >> v >> l_v >> w;
        Edge edge(l_v, w);
        E[v].push_back(edge);
        Edge edge2(v, w);
        E[l_v].push_back(edge2); // 无向图
    }
    int ans = Dijkstra(N, N);
    cout << ans << endl;
    return 0;
}