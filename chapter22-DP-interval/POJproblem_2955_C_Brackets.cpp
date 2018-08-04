
#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;
//http://poj.org/problem?id=2955
#define M(a,b) memset(a,b,sizeof(a))

const int maxn=105;
int dp[maxn][maxn];

bool match(char a, char b){// 匹配返回，true
    return (a=='(' && b==')') || (a=='[' && b==']');
}

//经典的区间DP
//
//        dp[i][j]代表i->j区间内最多的合法括号数
//        状态转移方程：
//if(s[i]=='('&&s[j]==')'||s[i]=='['&&s[j]==']')
//dp[i][j]=dp[i+1][j-1]+2;
//dp[i][j]=max{dp[i][k]+dp[k+1][j]};
int main() {
    string s;
    while (cin>>s && s!="end"){
        M(dp,0);
        int len = s.length();
        int ans;
        for(int k=1;k<len;k++){ // k 为区间长度
            for(int i=0,j=k;j<len;i++,j++){ // i,j 为区间两端指针
                if(match(s[i],s[j])){
                    dp[i][j] = 2 + dp[i+1][j-1];
                }
                for(int x=i;x<j;x++){ // 区间最值合并 如：（[])] i=0,j=4, dp[0][4] = max(dp[0][4], dp[0][3]+dp[4][4]
                    dp[i][j] = max(dp[i][j],dp[i][x]+dp[x+1][j]);
                }
            }
        }
         ans = dp[0][len-1];
        cout<<ans<<endl;
    }
}