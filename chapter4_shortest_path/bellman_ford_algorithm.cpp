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

int dist[maxn];

struct Edge{
    int u,v;
    int cost;
    Edge(int _u=0,int _v=0,int _cost=0):u(_u),v(_v),cost(_cost){}
};

vector<Edge> E; // 先 E.clear() 初始化，然后加入所有边
// 点的编号从1开始
// 单源最短路 复杂度O(VE)
bool bellman_ford(int start, int n){
    for(int i=1;i<=n;i++) dist[i] = INF;
    dist[start] = 0;
    // 最多做 n-1 次
    for(int i=1;i<n;i++){
        bool flag = false;
        for(int j=0;j<E.size();j++){
            int u = E[j].u;
            int v = E[j].v;
            int cost = E[j].cost;
            if(dist[v] > dist[u] + cost){
                dist[v]  = dist[u]+cost;
                flag = true;
            }
        }
        if(!flag) return true; // 没有负环回路
    }

    for(int j=0;j<E.size();j++){
        if(dist[E[j].v] > dist[E[j].u]+E[j].cost){
            return false; // 有负环回路
        }
    }
    return true;  // 没有负环回路
}
int main() {

    return 0;
}