#include <bits/stdc++.h>
using namespace std;
#define M(a, b) memset(a,b,sizeof(a))
// https://vjudge.net/contest/68966#problem/E
// 简单min-max dp:dp[i] = max(dp[i],dp[j] + a[i]);

// memset(a,0x3f,sizeof(a))
//memset(a,0xcf,sizeof(a))
typedef long long LL;

const int maxn = 0x3f3f3f3f;

int n;
LL a[1004];
LL dp[1004];
int main() {
    while (cin>>n && n!=0){
        a[0]=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        M(dp,0);
        dp[1] = a[1];
        LL ans=dp[1];
        for(int i=1;i<=n;i++){
            for(int j=0;j<i;j++){
                if(a[i] > a[j]){
                    dp[i] = max(dp[i],dp[j] + a[i]);
                    ans = max(ans, dp[i]);
                }
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}