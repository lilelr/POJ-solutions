// http://acm.hdu.edu.cn/showproblem.php?pid=1045
#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

vector<vector<int>> grid(6, vector<int>(6, -1)); // 记录图，-1：墙，1：炮，0：道路

int cnt;// 结果，最多可以有多少个炮点
int n; // 图的维度
string s; // 输入的每一行
int road_len; // 可以放置炮点的路径长度
struct node {
    int x; // 横坐标
    int y; // 纵坐标
};
vector<int> dx = {1, -1, 0, 0};// x方向
vector<int> dy = {0, 0, 1, -1}; // y 方向
vector<node> road; //记录dfs 的经过的节点

bool valid(int x, int y) { // 判断边界
    return x >= 0 && x < n && y >= 0 && y < n;
}


bool check(int cur) { // 判断当前的节点上下左右方向是否有炮点,没有，返回true； 有，返回false
    int x, y;
    bool flag = true;

    for (int i = 0; i < 4; i++) {
        x = road[cur].x + dx[i];
        y = road[cur].y + dy[i];

        while (valid(x, y)) {
            int t = grid[x][y];
            if (t == -1) { // 是墙
                break;
            }
            if (t == 1) { // 是炮点
                flag = false;
                return flag;
            }
            x = x + dx[i];
            y = y + dy[i];// 继续沿同一个方向伸展
        }
    }
    return flag;
}

void dfs(int cur, int turn) {
    if (turn > cnt) { // turn 表示前的炮点
        cnt = turn;
    }
    if (cur == road_len) {
        return;
    }

    dfs(cur + 1, turn);// dfs 到road末尾的节点

    if (check(cur)) {
        grid[road[cur].x][road[cur].y] = 1; // 放置炮点
        dfs(cur + 1, turn + 1); // 继续dfs
        grid[road[cur].x][road[cur].y] = 0; // 回溯

    }
}

int main() {


    while (cin >> n && n != 0) {
        road_len = 0;
        cnt = 0;
        road.clear();
        for (int j = 0; j < n; j++) {
            cin >> s;
            for (int i = 0; i < n; i++) {
                if (s[i] == '.') {
                    grid[j][i] = 0;
                    node temp;
                    temp.x = j;
                    temp.y = i;
                    road.push_back(temp); // 记录道路的节点
                    road_len++;
                } else {
                    grid[j][i] = -1;
                }
            }

//            for (int i = 0; i < road_len; i++) {
//                cout << road[i].x << " " << road[i].y << endl;
//            }
        }

        dfs(0, 0);
        cout << cnt << endl;

    }
}