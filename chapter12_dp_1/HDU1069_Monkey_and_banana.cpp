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

// memset(a,0x3f,sizeof(a))
//memset(a,0xcf,sizeof(a))
typedef long long LL;

const int maxn = 0x3f3f3f3f;
struct Block {
    int x;
    int y;
    int h;
    int area; // 面积
    int total_height;

//    Block(int _x,int _y,int _h):x(_x),y(_y),h(_h){}
};

bool compare(const Block& l, const Block& r){
    // 先按面积从从大到小排序，再按x大小排序

    if(l.area != r.area){
        return l.area> r.area;
    }else {
        return l.x > r.x;
    }
}

void my_swap(int &x, int &y) {
    int t = x;
    x = y;
    y = t;
}
// 按  x>=y  >= z 排序
void swap_three(int &x, int &y, int &z) {
    if (x < y) {
        my_swap(x, y);
    }
    if (x < z) {
        my_swap(x, z);
    }
    if (y < z) {
        my_swap(y, z);
    }
}

int main() {
    int n;
    int tx, ty, th;
    int cake=1;
    while (cin >> n && n != 0) {
        int res=-1;

        Block blocks[3 * n + 1];
        int p=1;
        for (int i = 1; i <= n; i++) {
            cin >> tx >> ty >> th;
            swap_three(tx, ty, th);

            blocks[p].x = tx;
            blocks[p].y = ty;
            blocks[p].h = th;
            blocks[p].area = tx * ty;
            blocks[p].total_height = 0;

            p++;
            blocks[p].x = tx;
            blocks[p].y = th;
            blocks[p].h = ty;
            blocks[p].area = tx * th;
            blocks[p].total_height = 0;

            p++;
            blocks[p].x = ty;
            blocks[p].y = th;
            blocks[p].h = tx;
            blocks[p].area = ty * th;
            blocks[p].total_height = 0;
            p++;

        }
        // 先按面积从从大到小排序，再按x大小排序
        sort(blocks+1,blocks+3*n+1,compare);

        for(int i=1;i<=3*n;i++){

            for(int j=1;j<i;j++){
                if(blocks[j].x > blocks[i].x && blocks[j].y > blocks[i].y){
                    // 动态规划方程
                    blocks[i].total_height = max(blocks[i].total_height, blocks[j].total_height);
                }
            }

            blocks[i].total_height += blocks[i].h;
            res = max(res, blocks[i].total_height);
        }
        printf("Case %d: maximum height = %d\n",cake++,res);
    }
    return 0;
}