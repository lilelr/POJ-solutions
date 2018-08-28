#include <bits/stdc++.h>
// 完全背包问题
using namespace std;
#define M(a, b) memset(a,b,sizeof(a))

// memset(a,0x3f,sizeof(a))
//memset(a,0xcf,sizeof(a))
typedef long long LL;

const int maxn = 0x3f3f3f3f;


int N, E, F, T;
int P[502], W[502];
int dp[502];

int main() {
    cin >> T;
    while (T--) {
        cin >> E >> F;
        F = F -E;
        cin >> N;
        for (int i = 1; i <= N; i++) {
            cin >> P[i] >> W[i];
        }
        M(dp, maxn);
        dp[0] = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = W[i]; j <= F; j++) {
                dp[j] = min(dp[j - W[i]] + P[i], dp[j]);
//                printf("j:%d, dp[j]:%d ",j,dp[j]);
            }
//            printf("\n");
        }
        int ans = dp[F];
        if (ans != maxn) {
            printf("The minimum amount of money in the piggy-bank is %d.\n", ans);
        } else {
            printf("This is impossible.\n");
        }
    }
    return 0;
}