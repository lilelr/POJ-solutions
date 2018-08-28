#include <bits/stdc++.h>
//https://vjudge.net/contest/68966#problem/D
// 状态DP
//题意：主人公有N门功课要做，每门功课做完需要一定的时间，而且每门功课有一个最后期限，如果该门功课延后一天交就得扣一分，而且每做一门功课主人公就一定把它做完为止，不会中途停下来再去做其他的。问怎样安排可使扣的分最少，如果有多组解，输出字典序最小的。
//
//解析：由于N很小，可以考虑dp状态压缩搜索，如果选了第i门功课，则二进制对应的位变为1，直到全部选完，更新最小值。打印时可以根据
//        dp[]保存的值去找，比如当前状态为now,第i门功课没选，如果dp[now]==dp[now+(1<<i)]+GetTime(...),则可以选它，再往下搜，直到找到所有的解。

using namespace std;
#define M(a, b) memset(a,b,sizeof(a))

// memset(a,0x3f,sizeof(a))
//memset(a,0xcf,sizeof(a))
typedef long long LL;

const int maxn = 0x3f3f3f3f;

const double eps = 0.00000001;

int N, deadline[15], days[15]; //多少门课， 期限， 每门课需要时间
vector<string> ans_name; // 保存答案
string name[15]; // 输入的科目名称
int dp[1 << 15]; // 记忆哪些课已选的状态，因为N最多是15

/**
 * 已经经过pass天后，开始完成第id门功课，计算这门课的延迟时间
 * @param id
 * @param pass
 * @return 这门课的延迟时间
 */
int Get(int id, int pass) {
    if (pass + days[id] <= deadline[id]) return 0; // 如果在期限之前完成
    return pass + days[id] - deadline[id];
}

/**
 * 记忆路径输出
 * @param pick
 * @param date
 */
void get_ans(int pick, int date) {
    if (pick == (1 << N) - 1) return;
    for (int i = 0; i < N; i++) {
        if (pick & (1 << i)) continue;
        if (dp[pick] == dp[pick + (1 << i)] + Get(i, date)) { // 根节点的值是由子节点的值赋予的，找到符合条件的
            ans_name.push_back(name[i]);
            get_ans(pick + (1 << i), date + days[i]);
            break;
        }
    }
    return;
}

/**
 * 所有状态深搜，形成一棵深度搜索树， 从dfs(0,0)开始
 * @param pick
 * @param date
 * @return 所有门课作业完成时，延迟提交的天数最小值
 */
int dfs(int pick, int date) { // pick 表示当前已选的状态，date代表现在是第几天
    if (pick == (1 << N) - 1) { // 全部选完
        return dp[pick] = 0;
    }
    int &ret = dp[pick];
    if (ret != -1) return ret; // 记忆化
    ret = maxn;
    for (int i = 0; i < N; i++) {
        if (pick & (1 << i)) continue;
        ret = min(ret, dfs(pick + (1 << i), date+days[i])+Get(i, date)); // 取最最小值
    }
    return ret; // 记得返回
}

int main() {

    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> name[i] >> deadline[i] >> days[i];
        }
        M(dp, -1);
        int ans = dfs(0, 0);
        printf("%d\n", ans);
        ans_name.clear();
        get_ans(0, 0);
        for (int i = 0; i < ans_name.size(); i++) {
            cout << ans_name[i] << endl;
        }
    }

    return 0;
}