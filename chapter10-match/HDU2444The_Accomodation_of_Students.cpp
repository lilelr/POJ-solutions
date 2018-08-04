// https://blog.csdn.net/qq_37405320/article/details/80357939
// http://acm.hdu.edu.cn/showproblem.php?pid=2444
// 二分图匹配】【匈牙利算法】【bfs判断二分图】
#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;using namespace std;
#define M(a,b) memset(a,b,sizeof(a))
const int MAXN = 210;
int link[MAXN]; // 记录匹配的边
int vis[MAXN]; // 是否访问过
int jug[MAXN]; // 两种染色，1，0
int n,m; // n 个人，m 个已经相互认识的关系
int ai,bi; // 输入的ai，bi
int ans = 0; // 答案，最大匹配的对数
vector<int>par[MAXN]; // 无向图
bool bfs()///判断二分图
{
    M(jug,-1);
    queue<int>q;
    q.push(1);
    jug[1] = 0;
    while(!q.empty())
    {
        int temp = q.front();
        for(int i =0;i<par[temp].size();i++)
        {
            if(jug[par[temp][i]]==-1)
            {
                jug[par[temp][i]]  = (jug[temp]+1)%2;///染成不同颜色
                q.push(par[temp][i]);
            }
            else
            {
                if(jug[par[temp][i]]==jug[temp])///相邻节点颜色相同
                {
                    return false;
                }
            }
        }
        q.pop();
    }
    return true;
}
bool FIND(int u)///匈牙利算法,找交替边，找到，返回true
{
    for(int i=0;i<par[u].size();i++)
    {
        int temp = par[u][i];
        if(vis[temp]) continue;
        vis[temp] = 1;
        if(link[temp]==-1||FIND(link[temp]))
        { // link[temp] =-1 ，表示找到一条交替边，从而匹配的边加一，return true
            link[temp] = u;
            return true;
        }
    }
    return false;
}
int main()
{
    while(~scanf("%d %d",&n,&m))
    {
        ans=0;
        M(link,-1);
        for(int i=1;i<=MAXN;i++) par[i].clear();///注意清空
        for(int i=0;i<m;i++)
        {
            scanf("%d %d",&ai,&bi);
            par[ai].push_back(bi);///两个关系都要计入邻接表
            par[bi].push_back(ai);
        }
        if(!bfs()) {printf("No\n");continue;}

        for(int i=1;i<=n;i++)
        {
            M(vis,0);
            if(FIND(i)) ans++;
        }
        printf("%d\n",ans/2);///结果要除2

    }
    return 0;
}
