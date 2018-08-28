//bug http://acm.hdu.edu.cn/showproblem.php?pid=1176
#include <bits/stdc++.h>
using namespace std;
#define M(a, b) memset(a,b,sizeof(a))

// memset(a,0x3f,sizeof(a))
//memset(a,0xcf,sizeof(a))
typedef long long LL;
//分析：
//设a[i][j]为第i秒的j位置掉下的馅饼数量，f[i][j]为第i秒在j位置接馅饼最多可以接到的最多馅饼数量。由于每秒只能移动一个位置，因此这一状态可能由三种情况达到：
//
//f[i - 1][j - 1]
//f[i - 1][j]
//f[i - 1][j + 1]
//这三种情况中的最大值加上当前位置可以接到的馅饼数即是当前位置可以接到的最大馅饼数量：
//
//DP为： f [ i ] [ j ] = max ( f [ i - 1 ] [ j - 1 ] , f [ i - 1 ] [ j ] , f [ i - 1 ] [ j + 1 ] ) + a [ i ] [ j ] ;
const int INF=0xcfcfcfcf;
const int maxn = 1e5+2;

int a[maxn][13];
int f[maxn][13];
int main() {
    int n;
    int end_sec=-maxn;
    int t_s, t_p;
    cout<<maxn<<endl;
    while (scanf("%d",&n) && n!=0){
        M(a,0);
        M(f,0xcf);
        for(int i=0;i<n;i++){
            scanf("%d%d",&t_s,&t_p);
            ++a[t_s][t_p];
            printf("%d\n",a[t_s][t_p]);
            if(t_s > end_sec){
                end_sec = t_s;
            }
        }
        f[1][4]= a[1][4];
        f[1][5] = a[1][5];
        f[1][6] = a[1][6];
        int res =INF;
        printf("%d\n",res);
        for(int i=2;i<=end_sec;i++){
            for(int j=1;j<=10;j++){
//                printf("%d\n",a[i][j]);

                f[i][j] = f[i-1][j];
                if(j==1){
                    f[i][j] = max(f[i-1][2],f[i][j])+a[i][j];
                }else if(j==10){
                    f[i][j]= max(f[i-1][9],f[i][j])+a[i][j];
                }else{
                    f[i][j] = max(f[i-1][j+1],max(f[i][j],f[i-1][j-1]))+a[i][j];
                }
                res = max(res, f[i][j]);
            }
        }
        printf("%d\n",res);

    }
    return 0;
}