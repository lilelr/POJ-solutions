#include <bits/stdc++.h>
using namespace std;
#define M(a, b) memset(a,b,sizeof(a))

// memset(a,0x3f,sizeof(a))
//memset(a,0xcf,sizeof(a))
typedef long long LL;

const int maxn = 0x3f3f3f3f;




int main() {
   int n;
    int a;
    while (cin>>n){
        int pre_num,cnt;
        for(int i=1;i<=n;i++){
            cin>>a;
            if(i==1){
                pre_num = a;
                cnt=1;
            }else{
                if(cnt == 0){
                    pre_num = a;
                    cnt = 1;
                }else{
                    cnt--;
                }
            }
        }
        cout<<pre_num<<endl;
    }

    return 0;
}