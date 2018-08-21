#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
#include <stack>
#include <cstring>
#include <cmath>
//https://vjudge.net/problem/LightOJ-1038
//
//题目描述：
//
//　　给出一个数D，每次可以选择数D的一个因子，用数D除上这个因子得到一个新的数D，为数D变为1的操作次数的期望为多少？
//
//解题思路：
//
//　　概率DP咯，对于只知道期望是：E(X) = X1*p(X1) + X2*p(X2) + …… + Xn*p(Xn)的窝，拿这个题目没有一点办法。然后看了讨论版，发现总会有一些神人存在。
//
//　　求操作次数的期望时，先设定第i个因子给期望的贡献为Ti，那么有：E = (T1 + T2 + T3 + ...... + Tn)  / n;
//
//　　根据期望的定理：从当前位置移动到目的地的平均步数。所以可得到：E50 = (E1+1)/6 + (E2+1)/6 + (E5+1)/6 + (E10+1)/6 + (E25+1)/6 + (E50+1)/6;
//
//　　E1 == 0，然后先后依次递推就好啦。


//Sample Input
//3
//
//1
//
//2
//
//50
//
//Sample Output
//Case 1: 0
//
//Case 2: 2.00
//
//Case 3: 3.0333333333
using namespace std;
#define M(a, b) memset(a,b,sizeof(a))

const int maxn = 1e5 + 1;
double dp[maxn];

int main() {
    int T;
    cin >> T;
    int ca = 1;
    int n;
    while (ca <= T) {
        cin >> n;
        M(dp, 0);
        double ans = 0;
        for (int i = 2; i <= n; i++) {
            int cnt = 2;// 因数个数，包括1和本身 dp[i] = Ei
            double temp_sum = 0; // E10 = 1/4 * [ (1+E1) + (1+E2) + (1+E5) + (1+E10) ]
            int sqrt_int = (int) (sqrt(i));
            for (int j = 2; j <= sqrt_int; j++) { // 求因数
                if (i % j == 0) {
                    cnt++;
                    temp_sum += dp[j];
                    int quotient = i / j;
                    if (j != quotient) { // 如 25 = 5 * 5 ,5 不能再加一次
                        cnt++;
                        temp_sum += dp[quotient];
                    }
                }
            }
            printf("%d\n", cnt);
            dp[i] = (cnt + (double) temp_sum) / (cnt - 1);
            printf("dp[%d]: %f\n", i, dp[i]);
        }
        ans = dp[n];
        ca++;
        printf("Case 1: %lf\n", ans);
    }
    return 0;
}