// http://acm.hdu.edu.cn/showproblem.php?pid=1083
// 二分图匹配】【基于dfs匈牙利算法】 套 二分图模板
#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;
#define M(a, b) memset(a,b,sizeof(a))
const int MAXN = 305;
int uN, vN;
int g[MAXN][MAXN];
int linker[MAXN];

bool used[MAXN];

bool dfs(int u) {
    for (int v = 1; v <= vN; v++) {
        if (g[u][v] && !used[v]) {
            used[v] = true;
            if (linker[v] == -1 || dfs(linker[v])) {
                linker[v] = u;
                return true;
            }
        }
    }
    return false;
}

int hungary() {
    int res = 0;
    M(linker, -1);
    for (int u = 1; u <= uN; u++) {
        M(used, false);
        if (dfs(u)) res++;
    }
    return res;
}

int t, p, n;
int c, a;

int main() {
    cin >> t;
    while (t--) {
        cin >> p >> n;
        uN = n;
        vN = p;
        M(g,0);
        for (int i = 1; i <= p; i++) { //i从1
            cin >> c;
            for (int j = 1; j <= c; j++) {
                cin >> a;
                g[a][i] = 1;// 建图，有向图
//                g[i][a] = 1;
            }
        }
        int ans = hungary();
//        cout<<ans<<endl;
        if(ans == vN){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;

        }

    }

    return 0;
}
