#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
#include <stack>
#include <cstring>
// https://vjudge.net/contest/76505#problem/D
// dp + 概率 0-1 背包问题
using namespace std;
#define M(a, b) memset(a,b,sizeof(a))

int mi[102];
double pro[102];
double dp[102];

int main() {
    int T;
    cin >> T;
    int ca = 1;
    double success_p;
    int n;
    while (ca <= T) {
        cin >> success_p >> n;
        success_p = 1 - success_p; // 至少的逃跑的概率 = 1 - 被抓的概率
        int sum_million = 0;
        for (int i = 1; i <= n; i++) {
            cin >> mi[i] >> pro[i];
            sum_million += mi[i];
            pro[i] = 1 - pro[i]; // 逃跑的概率 = 1 - 被抓的概率
        }
        M(dp, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) { // 偷窃第i家银行
            for (int j = sum_million; j >= mi[i]; j--) { // 只偷取一次，逆序
                dp[j] = max(dp[j], dp[j - mi[i]] * pro[i]); // j 取固定金额情况下，偷取哪几家银行的总逃跑概率最高
            }
        }

        for (int j = sum_million; j >= 0; j--) { // 逆序输出能偷到的最多钱
            if (dp[j] > success_p) {
                printf("Case %d: %d\n", ca, j);
                break;
            }
        }

        ca++;
    }
}