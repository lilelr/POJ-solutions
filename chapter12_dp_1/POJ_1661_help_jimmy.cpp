// 模拟+dp + 逆序遍历
//https://blog.csdn.net/u013167299/article/details/45564531
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
typedef long long LL;

const int maxn = 1005;
const int INF = 0x3f3f3f3f;
#define M(a, b) memset(a,b,sizeof(a))

struct PlatForm {
    PlatForm() {};

    PlatForm(int l, int r, int h) {
        left = l;
        right = r;
        high = h;
    }

    int left, right, high;
} pfs[maxn];

bool compare(const PlatForm &l, const PlatForm &r) {
    return l.high < r.high;
}

int n, x, y, ma; // n个平台， x,y 初始点坐标， ma 跳的高度极限
int dp[maxn][2];  //dp[i][0] 第i个平台左边端点跳下去的最小高度值 [1]右边

void cal_left(int i) {
    int k = i - 1;
    while (k > 0 && pfs[i].high - pfs[k].high <= ma) {
        if (pfs[i].left >= pfs[k].left && pfs[i].left <= pfs[k].right) {
            // 找到i层平台下面一个合适的平台，动态规划方程
            dp[i][0] = pfs[i].high - pfs[k].high +
                       min(dp[k][0] + pfs[i].left - pfs[k].left, dp[k][1] + pfs[k].right - pfs[i].right);
            break;

        } else {
            // k-- 继续找
            k--;
        }

        if (pfs[i].high - pfs[k].high > ma) { // 超出跳的极限，不能跳
            dp[i][0] = INF;
        } else if (k == 0) { // k ==0 ,到地板了
            dp[i][0] = pfs[i].high;
        }
    }
}

void cal_right(int i) {
    int k = i - 1;
    while (k > 0 && pfs[i].high - pfs[k].high <= ma) {
        if (pfs[i].right >= pfs[k].left && pfs[i].right <= pfs[k].right) {
            // 找到i层平台下面一个合适的平台，动态规划方程
            dp[i][1] = pfs[i].high - pfs[k].high +
                       min(dp[k][0] + pfs[i].right - pfs[k].left, dp[k][1] + pfs[k].right - pfs[i].right);
            break;
        } else {
            // k-- 继续找
            k--;
        }

        if (pfs[i].high - pfs[k].high > ma) { // 超出跳的极限，不能跳
            dp[i][1] = INF;
        } else if (k == 0) { // k ==0 ,到地板了
            dp[i][1] = pfs[i].high;
        }
    }
}


int main() {
    int T;
    cin >> T;
    int ca = 1;
    while (ca <= T) {
        scanf("%d%d%d%d", &n, &x, &y, &ma);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d", &pfs[i].left, &pfs[i].right, &pfs[i].high);
        }
        pfs[n + 1].left = x;
        pfs[n + 1].right = x;
        pfs[n + 1].high = y;
        sort(pfs + 1, pfs + 2 + n, compare); // 按高度从小到大排序，从底部往顶部动态规划

        for (int i = 1; i <= n + 1; i++) {
            cal_left(i);
            cal_right(i);
        }
        int ans = min(dp[n + 1][0], dp[n + 1][1]);

        ca++;
        printf("Case 1: %d\n", ans);
    }
}