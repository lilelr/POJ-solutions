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

int gold[102];
double dp[102];

int main() {
    int T;
    cin >> T;
    int n;
    int ca = 1;
    while (ca <= T) {
        cin >> n;
        M(dp, 0);
        for (int i = 1; i <= n; i++) {
            cin >> gold[i];
        }
        dp[n] = gold[n];
        for (int i = n - 1; i >= 1; i--) {
            dp[i] += gold[i];
            int len = min(6, n - i);
            for (int j = i + 1; j <= i + len; j++) {
                dp[i] += dp[j] / len;
            }
        }

        printf("Case %d: %lf\n", ca,dp[1]);

        ca++;
    }
}
//
//printf()函数和浮点数
//2017年06月29日 11:42:32
//阅读数：513
//printf()函数和浮点数
//
//        举例：
//void main()
//{
//    float x = (float)102.1;
//    printf("%6.2f\n", x);
//    printf("%6.2f%6.2f\n", x,x);
//    printf("%9.2f%9.2f\n", x,x);
//    printf("%-9.2f%-9.2f\n", x,x);
//    printf("%09.2f\n", x);
//    printf("%09.2f%09.2f\n", x,x);
//
//    getchar();
//}
//
//结果：
//102.10
//102.10102.10
//102.10 102.10
//102.10 102.10
//000102.10
//000102.10000102.10