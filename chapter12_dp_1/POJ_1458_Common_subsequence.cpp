#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
#include <stack>
#include <cstring>
// 最长公共子序列长度
using namespace std;
#define M(a, b) memset(a,b,sizeof(a))


int main() {
    string x, z;
    while (cin >> x && cin >> z) {
        int m = x.length();
        int n = z.length();

        x.insert(x.begin(),'0');
        z.insert(z.begin(),'0');
//        cout<<x<<endl;
//        cout<<z<<endl;
        int dp[m + 1][n + 1];
        M(dp,0);
//        for(int i=0;i<=m;i++){
//            for(int j=0;j<=n;j++){
//                cout<<dp[i][j]<<endl;
//            }
//        }
        for (int i = 1; i <= m; i++) {
//            cout<<x[i]<<endl;
            if (x[i] == z[1]) {
                dp[i][1] = 1;
            }
        }
        for (int i = 1; i <= n; i++) {
            if (z[i] == x[1]) {
                dp[1][i] = 1;
            }
        }
//        for(int i=0;i<=m;i++){
//            for(int j=0;j<=n;j++){
//                cout<<dp[i][j]<<endl;
//            }
//        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
//                cout<<"i:"<<i<<"j: "<<j<< " dp[i - 1][j - 1]"<<dp[i - 1][j - 1]<<endl;
                if (x[i] == z[j]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
//                cout<<dp[i][j]<<endl;

            }
        }
        int ans = dp[m][n];
        printf("%d\n", ans);

    }
}