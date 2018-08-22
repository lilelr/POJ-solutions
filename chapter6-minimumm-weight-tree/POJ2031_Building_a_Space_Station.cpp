// http://poj.org/problem?id=2031 Kruskal 算法
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
using namespace std;
const int M = 105;
int father[M];

struct node{
    double x,y,z,r;
}V[M]; // 顶点集，从1开始

struct edge{
    int start,end;
    double dis; // 权重
}E[M*M]; // 边集， 从1开始

int m,n;

double between( node v1 , node v2 )
{
    double tmp;
    tmp = sqrt(  (v1.x-v2.x)*(v1.x-v2.x) + (v1.y-v2.y)*(v1.y-v2.y) +
                 (v1.z-v2.z)*(v1.z-v2.z) ) - v1.r - v2.r;
    if( tmp < 0 )
        return 0; /**如果两个圆相交,则定义距离为 0 */
    else
        return tmp;
}

bool cmp( edge a , edge b )
{
    return a.dis < b.dis; /** 把边按照长度从小到大排序 */
}

int find( int x ) /** 并查集find*/
{
    return x == father[x] ? x : father[x] = find(father[x]);
}

bool merge( int a , int b )
{
    int x,y;
    x = find(a);/**找祖宗*/
    y = find(b);
    if( x == y )  /**祖宗相同, 属于同一连通分量*/
        return true;
    else/**属于不同联通分量, 合并*/
        father[x] = y;
    return false;
}

void Kruskal( )
{
    for( int i=1 ; i<=n ; i++ )
        father[i] = i;  /** 初始化并查集,自己是自己的祖宗*/
    sort( E+1 , E+1+m , cmp );
    double ans = 0;
    for( int i=1 ; i<=m ; i++ ){/*排序后遍历的边一定是从小到大的*/
        if( merge( E[i].start , E[i].end ) )
            continue;
        else
            ans += E[i].dis;
    }
    printf("%.3f\n",ans);
}

int main()
{
    while( scanf("%d",&n) == 1 && n ){
        m = 0;
        for( int i=1 ; i<=n ; i++ ){
            scanf("%lf%lf%lf%lf",&V[i].x,&V[i].y,&V[i].z,&V[i].r);
            for( int j=1 ; j<i ; j++ ){
                E[++m].start = j;
                E[m].end = i;
                E[m].dis = between( V[i] , V[j] );
            }
        }
        //for( int i=1 ; i<=m ; i++ )
        //	printf("%d->%d=%.3lf\n",E[i].start,E[i].end,E[i].dis);
        Kruskal( );
    }
    return 0;
}
