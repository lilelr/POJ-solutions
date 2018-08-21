#include <bits/stdc++.h>
https://blog.csdn.net/chenzhenyu123456/article/details/47720573
using namespace std;
#define M(a, b) memset(a,b,sizeof(a))

// memset(a,0x3f,sizeof(a))
//memset(a,0xcf,sizeof(a))
typedef long long LL;

//思路：设花费时间 出迷宫的期望为E。
//
//每个选择只有两种情况——设当前门花费时间的绝对值为 T
//
//一：选择的门可以直接把你传送出去，期望为1 / N * T。
//二：选择的门把你传送到原来的位置，期望为1 / N * T，又回到初始状态，则出去的期望为1 / N * (T + E)。
//
//
//设所有可以将你传送出去的门的时间值 总和为sum1，所有可以将你传送回去的门的时间值 总和为sum2。
//设所有可以将你传送出去的门的数目为door1，所有可以将你传送回去的门的数目为door2。
//得到等式
//
//        E = 1 / N * (sum1)  + 1 / N * (sum2 + door2 * E)。
//
//化简得 E = (sum1 + sum2) / (N-door2); 当然若door2等于N，说明不可能出迷宫。

const int maxn = 0x3f3f3f3f;

int GCD(int a, int b) {
    return b == 0 ? a : GCD(b, a % b);
}


int doors[102];

int main() {
    int T;
    cin >> T;
    int n;
    int a;
    int positive_sum = 0;
    int positive_cnt = 0;
    int negative_sum = 0;
    int negative_cnt = 0;
    int ca = 1;
    while (ca <= T) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a;
            if (a < 0) {
                negative_cnt++;
                negative_sum += (-a);
            } else {
                positive_cnt++;
                positive_sum += a;
            }
        }

        int up = positive_sum + negative_sum;
        int down = n - negative_cnt;
        if (down == 0) {
            printf("Case %d: inf\n", ca);
        } else {
            printf("Case %d: %d/%d\n", ca, up / GCD(up, down), down / GCD(up, down));

        }

    }

    return 0;
}