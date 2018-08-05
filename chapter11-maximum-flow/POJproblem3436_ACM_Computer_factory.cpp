/*
POJ 3436
*/
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<queue>

using namespace std;

//****************************************************
//最大流模板
//初始化：g[][],start,myend
//******************************************************
const int MAXN = 110;
const int INF = 0x3fffffff;
int g[MAXN][MAXN];//存边的容量，没有边的初始化为0
int path[MAXN], flow[MAXN], start, myend;
int n;//点的个数，编号0-n.n包括了源点和汇点。

queue<int> q;

// bfs搜索，返回可以增加的流量
int bfs() {
    int i, t;
    while (!q.empty())q.pop();//把清空队列
    memset(path, -1, sizeof(path));//每次搜索前都把路径初始化成-1
    path[start] = 0;
    flow[start] = INF;//源点可以有无穷的流流进
    q.push(start);
    while (!q.empty()) {
        t = q.front();
        q.pop();
        if (t == myend) break;
        //枚举所有的点，如果点的编号起始点有变化可以改这里
        for (i = 0; i <= n; i++) {
            if (i != start && path[i] == -1 && g[t][i]) {
                flow[i] = flow[t] < g[t][i] ? flow[t] : g[t][i];
                q.push(i);
                path[i] = t;
            }
        }
    }
    if (path[myend] == -1)return -1;//即找不到汇点上去了。找不到增广路径了
    return flow[myend];
}

// 最大流和最小割：Edmonds_Karp算法 https://blog.csdn.net/z6491679/article/details/46609501
int Edmonds_Karp() {
    int max_flow = 0;
    int step, now, pre;
    while ((step = bfs()) != -1) {
        max_flow += step;
        now = myend;
        while (now != start) {
            pre = path[now];
            g[pre][now] -= step; // 减去这次 bfs 获得的流量
            g[now][pre] += step;  // 反向流量增加
            now = pre;
        }
    }
    return max_flow;
}

int backup[MAXN][MAXN];//备份图
int in[MAXN][20];//输入信息
int Line[MAXN][4];

int main() {
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    int p;
    int N;
    while (scanf("%d%d", &p, &N) != EOF) {
        memset(g, 0, sizeof(g));
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < 2 * p + 1; j++)
                scanf("%d", &in[i][j]);
        }
        for (int i = 1; i <= N; i++)//拆点
        {
            g[2 * i - 1][2 * i] = in[i][0];
        }
        n = 2 * N + 1;
        start = 0;//源点
        myend = n;//汇点
        for (int i = 1; i <= N; i++) {
            bool flag_s = true;
            bool flag_t = true;
            for (int j = 0; j < p; j++) {
                if (in[i][j + 1] == 1)flag_s = false;//不能有1， 全是 0或者2
                if (in[i][j + 1 + p] == 0)flag_t = false; // 连接汇点，不能是0， 全是1 或者 2
            }
            if (flag_s)g[0][2 * i - 1] = INF;// 连接源点
            if (flag_t)g[2 * i][n] = INF;  // 连接汇点
            for (int j = 1; j <= N; j++) // 遍历每个机器节点
                if (i != j) {
                    bool flag = true;
                    for (int k = 0; k < p; k++)
                        if ((in[i][k + p + 1] == 0 && in[j][k + 1] == 1) || (in[i][k + p + 1] == 1 && in[j][k + 1] ==
                                                                                                      0)) { // i机器不能生产出的p部分，j机器需要p部分； 第二，i机器能生产出p部分，但j机器不需要
                            flag = false;
                            break;
                        }
                    if (flag)g[2 * i][2 * j - 1] = min(in[i][0], in[j][0]); // 边之间流量的限制，容量
                }

        }
        memcpy(backup, g, sizeof(g));//先把图备份下来
        // 求解最大流
        printf("%d ", Edmonds_Karp());
        // 求解之后，g[2*i][2*j-1] 记录的是该边需要反向流过的流量
        int tol = 0;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++) {
                if (g[2 * i][2 * j - 1] < backup[2 * i][2 * j - 1]) {
                    Line[tol][0] = i;
                    Line[tol][1] = j;
//                    cout<< backup[2*i][2*j-1] << " "<< g[2*i][2*j-1]<<endl;
                    Line[tol][2] = backup[2 * i][2 * j - 1] - g[2 * i][2 * j - 1];
                    tol++;
                }
            }
        printf("%d\n", tol);
        for (int i = 0; i < tol; i++) {
            printf("%d %d %d\n", Line[i][0], Line[i][1], Line[i][2]);
        }
    }
    return 0;
}