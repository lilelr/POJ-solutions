#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
#include <stack>
#include <cstring>
// HDU 4283 You Are the One(区间dp)
// http://acm.hdu.edu.cn/showproblem.php?pid=4283
using namespace std;
#define M(a, b) memset(a,b,sizeof(a))
typedef long long LL;
const int INF = 0x3f3f3f3f;
//const int INF = 100000;
int t;
int n;
const int maxn = 103;
int dp[maxn][maxn];   // dp[i][j] 表示区间[i,j] 的最小unhappiness 值
int sum[maxn][maxn]; // sum[i][j] 记录 nums[i]到nums[j] 的和
int nums[maxn]; //保存数据

void mem(int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INF;
        }
    }
}

int main() {
    scanf("%d",&t);
    int ca = 1;
    while (t--) {
        mem(maxn, maxn);
        M(nums, 0);
        M(sum, 0);
//        cin >> n;
        scanf("%d",&n);
        for (int i = 1; i <= n; i++) {
//            cin >> nums[i];

            scanf("%d",&nums[i]);
        }

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                sum[i][j] = sum[i][j - 1] + nums[j];
                if (i == j) {
                    dp[i][j] = 0;
                }
                if (j == i + 1) {
                    dp[i][j] = min(nums[i], nums[j]);
                }

            }
        }


        for (int i = 2; i <= n; i++) { // i 表示区间长度
            for (int left = 1; left <= n - i; left++) {
                int right = left + i;
                dp[left][right] = min(dp[left][right], dp[left][right - 1] + i * nums[right]);
                for (int k = left; k < right; k++) {
                    if(k==left) {
                        dp[left][k-1] = 0;
                    }

                    int temp = dp[left][k - 1] + (k - left) * sum[k + 1][right] + dp[k + 1][right] + i * nums[k];
                    if (dp[left][right] > temp) {
                        dp[left][right] = temp;
                    }
                }

            }
        }


        int ans = dp[1][n];

        printf("Case #%d: %d\n", ca, ans);
        ca++;

    }
}