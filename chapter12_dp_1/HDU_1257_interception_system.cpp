//https://vjudge.net/contest/68966#problem/I
// dp 单维度 路径值更新
#include <stdio.h>
#include <string.h>
int a;//用来保存导弹的高度
int b[100000];//用来保存拦截系统能够拦截的高度
int main()
{
    int n,cnt;//n代表总共的导弹的个数，cnt代表拦截系统的个数
    while(scanf("%d",&n)!=EOF)
    {
        memset(b,0,sizeof(b));//b用来保存拦截系统能够拦截的最大高度
        cnt=0;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&a);
            int j;
            for(j=0;j<=cnt;j++)//每次都用较小的高度来替换b中的数值
            {
                if(b[j]>=a)//如果拦截系统能够拦截就拦截
                {
                    b[j]=a;
                    break;
                }
            }
            if(j>cnt)//如果拦截系统都不能够拦截，就只能够再重新用一个拦截系统了
            {
                b[++cnt]=a;//因为每次都是先遍历，再往后追加，所以b中的数是从小到达进行排序的
            }
        }
        printf("%d\n",cnt);
    }
    return 0;
}
