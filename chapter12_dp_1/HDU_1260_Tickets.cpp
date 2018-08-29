
#include <bits/stdc++.h>
//https://vjudge.net/contest/68966#problem/H
// 单状态跳转dp, 一次跳一步，也可以一次跳两步 dp[i] = min(dp[i - 1] + single[i], dp[i - 2] + dou[i - 1]);

using namespace std;
#define M(a, b) memset(a,b,sizeof(a))

// memset(a,0x3f,sizeof(a))
//memset(a,0xcf,sizeof(a))
typedef long long LL;

const int maxn = 4000;

int dou[maxn];
int single[maxn];
int dp[maxn];
int t, m;

int main() {
    scanf("%d",&t);
    while (t--) {
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%d", &single[i]);
        }
        for (int i = 1; i <= m - 1; i++) {
            scanf("%d", &dou[i]);
        }
        M(dp, 0);
        dp[1] = single[1];
        dp[2] = min(dp[1] + single[2], dou[1]);
        for (int i = 3; i <= m; i++) {
            dp[i] = min(dp[i - 1] + single[i], dp[i - 2] + dou[i - 1]);
        }
        int ans = dp[m];

        int minutes = 0;
        int seconds = 0;
        int hours = 0;
        while (ans >= 60) {
            ans -= 60;
            minutes++;
        }
        while (minutes >= 60) {
            minutes -= 60;
            hours++;
        }

        if (hours > 5) {
            printf("%02d:", hours + 8 - 12);
        } else {
            printf("%02d:", hours + 8);
        }
        printf("%02d:", minutes);
        if (hours > 5) {
            printf("%02d pm\n", ans);
        } else {
            printf("%02d am\n", ans);

        }

    }
    return 0;
}