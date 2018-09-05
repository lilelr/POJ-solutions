//https://blog.csdn.net/helloworld10086/article/details/40052601 bfs + 遍历起点
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
const int INF = 0x3f3f3f3f;
const int N = 20;

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

struct Node {
    int r, c, dis;

    Node() {}

    Node(int _r, int _c, int _dis):r(_r),c(_c),dis(_dis) {

    }
};

char grid[N][N];
int vis[N][N];
int n, m;
bool ok, flag;

bool full() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#' && !vis[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int bfs(int x1, int y1, int x2, int y2) {
    vis[x1][y1] = vis[x2][y2] = true;
    if (full()) {
        flag = true;
        ok = true;
        return 0;
    }

    queue<Node> que;
    que.push(Node(x1, y1, 0));
    que.push(Node(x2, y2, 0));

    int r, c, dis;
    while (!que.empty()) {
        Node front = que.front();
        que.pop();
        for (int i = 0; i < 4; i++) {
            r = front.r + dr[i];
            c = front.c + dc[i];
            if (r < 0 || r >= n || c < 0 || c >= m) {
                continue;
            }

            if (grid[r][c] == '#' && !vis[r][c]) {
                dis = front.dis + 1;
                vis[r][c] = true;
                que.push(Node(r, c, dis));
                if (full()) {
                    flag = true;
                    ok = true;
                    return dis;
                }
            }
        }
    }
    return 0;
}


int main() {

    int t, ka = 1;
    scanf("%d", &t);
    while (t--) {
        M(grid, 0);
        scanf("%d%d", &n, &m);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            scanf("%s", grid[i]);
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '#') {
                    cnt++;
                }
            }
        }

        if (cnt == 1) {
            printf("Case %d: 0\n", ka++);
        }

        ok = false;
        int t_min = INF;
        for (int x1 = 0; x1 < n; ++x1) {
            for (int y1 = 0; y1 < m; ++y1) {
                if (grid[x1][y1] != '#') {
                    continue;
                }
                for (int x2 = x1; x2 < n; x2++) {
                    for (int y2 = 0; y2 < m; y2++) {
                        if (grid[x2][y2] != '#' || (x2 == x1 && y2 == y1)) {
                            continue;
                        }
                        flag = false;
                        M(vis, 0);
                        int res = bfs(x1, y1, x2, y2);
                        if (flag) {
                            t_min = min(t_min, res);
                        }
                    }
                }
            }
        }

        if (ok) {
            printf("Case %d: %d\n", ka++, t_min);
        } else {
            printf("Case %d: -1\n", ka++, t_min);

        }
    }
    return 0;
}