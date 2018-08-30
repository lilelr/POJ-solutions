#include <bits/stdc++.h>

using namespace std;
#define M(a, b) memset(a,b,sizeof(a))

// memset(a,0x3f,sizeof(a))
//memset(a,0xcf,sizeof(a))
typedef long long LL;

const int maxn = 1002;


int dp[maxn][maxn];
int dp_v[maxn];
vector<string> str(maxn);

//int main() {
//    int n;
//    while (cin >> n && n != 0) {
//        for (int i = 1; i <= n; i++) {
//            cin >> str[i];
//            str[i].insert(str[i].begin(),'0');
////            cout << str[i] << endl;
//        }
//        for (int i = 1; i <= n; i++) {
//            for (int j = 1; j <= n; j++) {
//                dp[i][j] = 1;
//                dp_v[i] = 1;
////                cout<<dp[i][j]<<endl;
//            }
//        }
//        int res = 1;
//        for (int i = 1; i <= n; i++) {
//            for (int j = n; j >= 1; j--) {
//                int pre_i = i - 1;
//                int pre_j = j + 1;
//                if (pre_i >= 1 && pre_i <= n && pre_j >= 1 && pre_j <= n) {
//                    int pre_val = dp[pre_i][pre_j];
//                    int t_i = i - 1;
//                    int t_j = j + 1;
//                    int cur_val = 1;
//                    while (cur_val <= pre_val  && str[t_i][j] == str[i][t_j]) {
//                        t_i--;
//                        t_j++;
//                        cur_val++;
//                    }
//                    dp[i][j] = cur_val;
//
////                    res = max(res, dp[i][j]);
//                }
//            }
//        }
//        printf("%d\n", res);
//
//
//    }
//    return 0;
//}
//

int main() {
    int n;
    while (cin >> n && n != 0) {
        for (int i = 1; i <= n; i++) {
            cin >> str[i];
            str[i].insert(str[i].begin(),'0');
//            cout << str[i] << endl;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = 1;
                dp_v[i] = 0;
//                cout<<dp[i][j]<<endl;
            }
        }
        int res = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = n; j >= 1; j--) {
                int pre_i = i - 1;
                int pre_j = j + 1;
                if (pre_i >= 1 && pre_i <= n && pre_j >= 1 && pre_j <= n) {
                    int pre_val = dp_v[pre_j];
                    int t_i = i - 1;
                    int t_j = j + 1;
                    int cur_val = 1;
                    while (cur_val <= pre_val  && str[t_i][j] == str[i][t_j]) {
                        t_i--;
                        t_j++;
                        cur_val++;
                    }
                    dp_v[j] = cur_val;

                    res = max(res, dp_v[j]);
                }
            }
        }
        printf("%d\n", res);


    }
    return 0;
}