//https://vjudge.net/contest/68966#problem/J
// 最长公共子序列， pre[i] = j 记录路径
// #include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
int dp[1005], pre[1005], ans[1005];
struct node {
    int w, s, id;
} a[1005];

bool cmp(node a, node b) {
    return a.w < b.w || a.w == b.w && a.s > b.s;
}

int main() {
    int cnt = 0;
    memset(pre, 0, sizeof(pre));
    while (~scanf("%d%d", &a[cnt].w, &a[cnt].s)) {
        a[cnt].id = cnt + 1;
        cnt++;
    }
    int res = 0;

    sort(a, a + cnt, cmp);
    int idex = 0;
    for (int i = 0; i < cnt; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++)
            if (a[j].w < a[i].w && a[j].s > a[i].s) {
                if (dp[i] < dp[j] + 1) {
                    pre[i] = j; // 记录路径
                    dp[i] = dp[j] + 1;
                }
            }
        if (res < dp[i]) {
            res = dp[i];
            idex = i; // idex 记录最后路径的下标i
        }
    }
    printf("%d\n", res);
    int kase = 0;
    while (idex != 0) { // 从路径末尾返回，记录路径，注意是 逆序增长
        ans[kase++] = idex;
        idex = pre[idex];
    }
    if (res == 1) printf("%d\n", dp[0]);
    while (kase > 0) {
        kase--;  // 路径顺序输出
        printf("%d\n", a[ans[kase]].id);
    }
    return 0;
}
