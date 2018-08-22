//http://poj.org/problem?id=1287
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

typedef long long LL;

const int INF = 0x3f3f3f3f;
const int maxn = 110;
bool vis[maxn];
int lowc[maxn]; //T:当前生成树的顶点集合 T1:不属于当前生成树的顶点集合 存放顶点集合T1 内各顶点到顶点集合T 内各顶点权值最小边的权值

/**
 *
 * @param cost 邻接矩阵 ，边表示权值，初始化，无限大
 * @param n n 顶点数
 * @return 最小生成树权值和
 */
int prim(int cost[][maxn], int n) {
    int ans = 0;
    M(vis, false);
    vis[0] = true;
    for (int i = 1; i < n; i++) lowc[i] = cost[0][i];
    for (int i = 1; i < n; i++) {
        int minc = INF;
        int p = -1;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && minc > lowc[j]) {
                minc = lowc[j];
                p = j;
            }
        }
        if (minc == INF) return -1;// 原图不连通
        ans += minc;
        vis[p] = true;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && lowc[j] > cost[p][j]) {
                lowc[j] = cost[p][j];
            }
        }
    }
    return ans;
}

int convert(char a) {
    return a - 'A';
}

int main() {
    char vec;
    int edges;
    int n;
    int cost[maxn][maxn];
    int edges_cnt;
    int v,n_v, w;
    while (cin >> n && n != 0) {
        M(cost, INF);
        cin>>edges_cnt;
        for(int i=1;i<=edges_cnt;i++){
            cin>>v>>n_v>>w;
            v--;
            n_v--;
            cost[v][n_v] = min(cost[v][n_v],w);// 多条重复路径选权重最小的
//            cost[v][n_v] = w;
           cost[n_v][v] = cost[v][n_v] ; // 无向图
        }
//        for (int i = 1; i <= n - 1; i++) {
//            cin >> vec >> edges;
//            int cur_vec = convert(vec);
//            char link_v;
//            int edge_v;
//            for (int j = 1; j <= edges; j++) {
//                cin >> link_v >> edge_v;
//                int cur_link_v = convert(link_v);
//                cost[cur_vec][cur_link_v] = edge_v; // 无向图
//                cost[cur_link_v][cur_vec] = edge_v;
//
//            }
//        }
        int ans = prim(cost, n);
        cout << ans << endl;
    }
}