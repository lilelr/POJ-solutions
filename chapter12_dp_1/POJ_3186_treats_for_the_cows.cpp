//题意
//        给长度为n的序列，每次只能从首或尾取一个数，第i次取的数权值为(数值*i)，求取完所有的数可以达到的最大权值。
//
//思路
//        dp[i][j]表示左边取了i个数，右边取了j个数
//        故
//dp[i][j] = max(dp[i-1][j] + a[i]* (i+j), dp[i][j-1] + a[n-j+1]*(i+j));
//注意当ij为0的边界判断即可。

#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
#include <stack>
#include <cstring>

using namespace std;
const int maxn = 2009;
const int INF = 0x3f3f3f3f;
#define M(a, b) memset(a,b,sizeof(a))

int dp[maxn][maxn];
int a[maxn];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j + i <= n; j++) {
            if (i == 0 && j == 0) {
                dp[0][0] = 0;
            } else if (j == 0) {
                dp[i][j] = dp[i - 1][0] + a[i] * (i + j);
            } else if (i == 0) {
                dp[i][j] = dp[0][j-1] + a[n - j + 1] * (i + j);
            } else {
                dp[i][j] = max(dp[i - 1][j] + a[i] * (i + j), dp[i][j - 1] + a[n - j + 1] * (i + j));
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, dp[i][n - i]);
    }
    cout << ans << endl;
    return 0;
}