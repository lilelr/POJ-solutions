#include <bits/stdc++.h>
using namespace std;
#define M(a, b) memset(a,b,sizeof(a))

// memset(a,0x3f,sizeof(a))
//memset(a,0xcf,sizeof(a))
typedef long long LL;

const int maxn = 0x3f3f3f3f;
int yuesefu(int n,int m){
    if(n == 1){
        return 0; //这里返回下标,从0开始，只有一个元素就是剩余的元素0
    }
    else{
        return (yuesefu(n-1,m) + m) % n; //我们传入的n是总共多少个数
    }
}
int main(void){
    int a,b;
    cin>>a>>b;
    cout<<yuesefu(a,b)<<endl;

    //或者，直接循环迭代，求出来的result如上
    int result = 0;
    for(int i = 2;i <= a;i++){
        result = (result+b) %i;
    }
    cout<<"result = "<<result<<endl;
    return 0;
}