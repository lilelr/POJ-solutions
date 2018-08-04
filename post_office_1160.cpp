#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>

#include <cstring>
// https://blog.csdn.net/u011470356/article/details/18553635
using namespace std;
const int MAX = 305;
const int INF = 10000000;
int dp[MAX][MAX];
int position[MAX];
int sum[MAX][MAX];

int main() {
    int v, p;
    while (cin >> v >> p) {
        for (int i = 1; i <= v; i++) {
            cin >> position[i];
        }

        memset(sum, 0, sizeof(sum));
        for (int i = 1; i <= v; i++) {
            for (int j = i + 1; j <= v; j++) {
                sum[i][j] = sum[i][j - 1] + position[j] - position[(i + j) / 2];

//                cout<<" i:"<<i<<" j:"<<j<<" sum[i][j]: "<<sum[i][j]<<" ";
            }
        }

        for (int i = 1; i <= v; i++) {
            dp[i][i] = 0;
            dp[i][1] = sum[1][i];
        }

        for (int j = 2; j <= p; j++) {
            for (int i = 1; i <= v; i++) {

                dp[i][j] = INF;
                if(j>=i){
                    dp[i][j] = 0;
                }
                for (int k = 1; k < i; k++) {
//                    cout<<"k:"<<k<<" j-1:"<<j-1<<" dp[k][j-1]： "<<dp[k][j-1]<<endl;
//                    if(i==v && j==p){
//                        int testA=1;
//                        cout<< dp[k][j - 1] << " "<<sum[k + 1][i]<<endl;
//                    }

                    dp[i][j] = min(dp[i][j], dp[k][j - 1] + sum[k + 1][i]);
//                    dp[3][2] = min(dp[3][2],dp[1][1]+sum[2][3]);
                }
            }
        }
        int res = dp[v][p];
        cout<<res<<endl;

    }
    return 0;
}