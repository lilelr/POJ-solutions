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
#define M(a, b) memset(a,b,sizeof(a))

// http://poj.org/problem?id=1651
int n;
const int maxn = 102;
const int INF = 100000000;
int nums[maxn];
int dp[maxn][maxn];

int main() {
    cin >> n;
//    M(dp, INF);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            dp[i][j]  = INF;
        }
    }
    M(nums, -1);
    for (int i = 0; i < n; i++) {
        cout<<nums[i]<<endl;
        cin >> nums[i];
    }

    for (int k = 2; k < n; k++) { // 区间长度
        for (int left = 0; left < n - k; left++) {
            int right = left + k;
            for (int i = left + 1; i < right; i++) {
                if(i==left+1) {
                    dp[left][i] = 0;
                }
                if(right == i+1){
                    dp[i][right] = 0;
                }
                int product = nums[left] * nums[i] * nums[right];
//                cout<<left << " :"<<right<<endl;
//                cout<<dp[left][right]<<endl;
                dp[left][right] = min(dp[left][right], dp[left][i] + product + dp[i][right]);
            }
        }
    }


    int ans = dp[0][n-1];
    cout<<ans<<endl;
}