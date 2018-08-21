//https://blog.csdn.net/u010579068/article/details/47297051
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
    int year, month, day;
    while (T--) {
        cin >> year >> month >> day;
        if ((month + day) % 2 == 0) {
            printf("YES\n");
        } else if ((month == 9 || month == 11) && day == 30) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}