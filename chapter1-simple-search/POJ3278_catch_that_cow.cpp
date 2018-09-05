# include <stdio.h>
# include <string.h>
# include <queue>
//https://blog.csdn.net/super604zong/article/details/60322828
using namespace std;
//这是一道典型的广搜题，核心是使用一个一维数组，用它的下标记录农民所在位置，用它下标所对应的值来记录它所花费的时间，将每次的下标入队这里不用循环是因为农民三次的移动判断条件互不相同，每到一个位置，就将上个位置所有的时间加1赋值给它。
int n, m, ans;

int num[100005];

int main() {
    while (~scanf("%d%d", &n, &m)) {
        queue<int> que;

        que.push(n);
        num[n] = 1;
        while (!que.empty()) {
            int c = que.front();
            if (c == m) {
                ans = num[c];
                break;
            }

            que.pop();
            if (!num[c - 1] && c - 1 >= 0) {
                num[c - 1] = num[c] + 1;
                que.push(c - 1);
            }

            if (!num[c + 1] && c + 1 <= 100000) {
                num[c + 1] = num[c] + 1;
                que.push(c + 1);
            }

            if (!num[c * 2] && c * 2 <= 100000) {
                num[c * 2] = num[c] + 1;
                que.push(c * 2);
            }
        }
        ans = ans - 1;
        printf("%d", ans);
    }
}