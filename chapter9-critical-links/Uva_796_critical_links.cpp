#include <bits/stdc++.h>
//https://vjudge.net/contest/67418#problem/C
// 求无向图的桥
// 可以找出割点和桥，求删除每个点后增加的连通块
using namespace std;
#define M(a, b) memset(a,b,sizeof(a))

// memset(a,0x3f,sizeof(a))
//memset(a,0xcf,sizeof(a))
typedef long long LL;

const int maxn = 10010;

struct Edge {
    int to, next;
    bool cut; // 是否为桥的标志
} edge[maxn];

int head[maxn], tot;
int Low[maxn], DFN[maxn], Stack[maxn];

int Index, top;

bool Instack[maxn];

bool cut[maxn];
int add_block[maxn]; // 删除一个点后增加的连通块
int bridge;

void addedge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].cut = false;
    head[u] = tot++;
}

void Tarjan(int u, int pre) {
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    int son = 0;
    int pre_cnt = 0;// 处理重边，如果不需要可以去掉
    for (int i = head[u]; i != -1; i = edge[i].next) {
        v = edge[i].to;
        if (v == pre && pre_cnt == 0) {
            pre_cnt++;
            continue;
        }

        if (!DFN[v]) {
            son++;
            Tarjan(v, u);
            if (Low[u] > Low[v]) Low[u] = Low[v];
            // 桥
            // 一条无向边（u,v) 是桥，当且仅当 (u,v) 为树枝边，且满足 DFS(u)<Low(v)
            if (Low[v] > DFN[u]) {
                bridge++;
                edge[i].cut = true;
                edge[i ^ 1].cut = true;
            }
            // 割点
            // 一个顶点u是割点，当前仅当满足 （1) 或 （2）（1） u 为树根，且 u 有多于一个子树。
            // (2) u 不为树根，且满足 （u,v) 为树枝边（或称父子边， 即u 为 v 在搜索树中的父亲）
            // 使得 DFS(u) <= Low(v)

            if (u != pre && Low[v] >= DFN[u]) {
                // 不是树根
                cut[u] = true;
                add_block[u]++;
            }
        } else if (Low[u] > DFN[v]) {
            Low[u] = DFN[v];
        }
    }

    // 树枝，分支数大于1
    if (u == pre && son > 1) cut[u] = true;
    if (u == pre) add_block[u] = son - 1;
    Instack[u] = false;
    top--;
}

void solve(int N) {
    M(DFN, 0);
    M(Instack, false);
    M(add_block, 0);
    M(cut, false);

    Index = top = 0;
    bridge = 0;
    for (int i = 1; i <= N; i++) {
        if (!DFN[i]) {
            Tarjan(i, i);
        }
    }
    printf("%d critical links\n", bridge);
    vector<pair<int, int> > ans;
    for (int u = 1; u <= N; u++) {
        for (int i = head[u]; i != -1; i = edge[i].next) {
            if (edge[i].cut && edge[i].to > u) {
                ans.push_back(make_pair(u, edge[i].to));
            }
        }
    }
    sort(ans.begin(), ans.end());
    /// 按顺序输出桥
    for (int i = 0; i < ans.size(); i++) {
        printf("%d - %d\n", ans[i].first - 1, ans[i].second - 1);
    }
    printf("\n");
}

void init() {
    tot = 0;
    M(head, -1);
}

map<int, int> mapit;

inline bool isHash(int u, int v) {
    if (mapit[u * maxn + v]) return true;
    if (mapit[v * maxn + u]) return true;
    mapit[u * maxn + v] = mapit[v * maxn + u] = 1;
    return false;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1){
        init();
        int u;
        int k;
        int v;
        mapit.clear();
        for(int i=1;i<=n;i++){
            scanf("%d (%d)",&u,&k);
            u++;
            // 这样加边，要保证正边和反边是相邻的，建无向图
            while (k--){
                scanf("%d",&v);
                v++;
                if(v<=u) continue;
                addedge(u,v);
                addedge(v,u);
            }
        }
        solve(n);
    }
    return 0;
}