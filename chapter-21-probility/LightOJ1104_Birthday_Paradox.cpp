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


int main() {
    int T;
    cin >> T;
    int ca = 1;
    int days;
    while (ca <= T) {
        double diff_day_pro = 1.0;
        cin >> days;
        int n = 0;
        double same_day_pro = 1 - diff_day_pro;
        while (same_day_pro < 0.5) {
            diff_day_pro = diff_day_pro * (1 - n / (double) days);
            printf("%lf\n", diff_day_pro);
            same_day_pro = 1 - diff_day_pro;
            n++;
        }

        ca++;
        printf("Case 1: %d\n", n -1);
    }
    return 0;
}