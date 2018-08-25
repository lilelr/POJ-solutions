
#include <bits/stdc++.h>

#define N 1000005

#define INF 0x7fffffff
using namespace std;
int a[N];
int n, m;   // dp[i][j] 表示 用前j 个数组成的i 组数据 的最大值
            // 所以，dp[i][j-1] 表示用前 j-1 个数组成组数据，第j个数a[j]加入到最后一组数据
           // max(dp[i-1][t]) + a[j],  1<=t <= (j-1）表示用 前 t 个数组成i-1组数据，第j个数a[j] 独立成 第i组
int dp[N]; // dp[i][j] = max(d[i][j-1] + a[j], max(dp[i-1][t]) + a[j] )  1<=t <= (j-1）
            //   第一项         第二项
           // 由于第一项和第二项都与i关联，如果以i 开始循环，i已知，不必用二维数组表示，直接用一维数组表示
          // 综上，会有三从循环，i,j,t 复杂度为n^3, 数据量太大，会超时，继续优化，到n^2
int pre_max[N];//用来j-1的位置用来存储 pre_max[j-1]= max(dp[i-1][t]) 1<=t<=(j-1) 保存上一组数据 用t个数组成i-1 组时的最大值，优化到n^2
// 所以最后的动态规划方程变为：  dp[j] = max(dp[j - 1] + a[j], pre_max[j - 1] + a[j])
int main() {
    while (scanf("%d%d", &m, &n) != EOF) {
        memset(dp, 0, sizeof(dp));
        memset(pre_max, 0, sizeof(pre_max)); // 初始化为0， 前i个数组成0组，当前结果为0
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        /*
            dp[i][j]=max( dp[i][j-1]+a[j] , max(dp[i-1][t])+a[j])
        */
        int res = -INF;

        for (int i = 1; i <= m; i++) {//遍历字段
            res = -INF;
            int tmp = 0;
            for (int k = 1; k <= i; ++k) {
                tmp += a[k];
            }
            dp[i] = tmp;
            // j 从i+1 遍历开始，前面的i个数组成的i组
            for (int j = i + 1; j <= n; j++) {
//                printf("i:%d j:%d dp[j-1]:%d pre_max[j-1]:%d\n", i,j, dp[j - 1],pre_max[j - 1] );
                dp[j] = max(dp[j - 1] + a[j], pre_max[j - 1] + a[j]);
//                printf("dp[i]:%d, a[j]: %d dp[j - 1] + a[j]: %d pre_max[j - 1] + a[j]: %d:\n",dp[i],a[j],dp[j - 1] + a[j],pre_max[j - 1] + a[j]);
                pre_max[j - 1] = res; // 仅更新自己关联的元素下标 j-1, 所以不会不会用到上一次循环的结果
                res = max(dp[j], res);
            }
        }
        printf("%d\n",res);
    }
    return 0;
}