//https://blog.csdn.net/yuege38/article/details/75161634
//https://vjudge.net/problem/POJ-1236
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
//5
//2 5 0
//5 0
//0
//0
//1 0

//题意：给出n个学校和一些学校之间的网络链接关系，学校之间的网络是单向边，让你求出两个问题的答案，1.至少需要多少份软件，使得所有学校都可以收到。2.如果希望用一份软件就能够使所有学校收到需要添加几条边
//
//
//
//题解：首先求强连通分量然后缩点，所谓缩点就是将一个连通图化为一个点。然后再以联通图构成一个图。
//
//然后这题的问题1只要求联通分量入度为0的点的和就行了，问题2就是求连通分量入度和出度为0的和的最
//
//        大值。（为了构成全连通分量构成的图联通，最少要加max（入度为0的，出度为0的）才能保证联通）。


using namespace std;

const int maxn = 100 + 10;

int N;
int In[maxn], Out[maxn];

/***************************Tarjan算法模板***************************/
vector<int> G[maxn];// 图，下标从1开始
int Mark[maxn], Root[maxn], Stack[maxn];     //时间戳，根(当前分量中时间戳最小的节点)，栈
bool Instack[maxn];                           //是否在栈中标记
int Ssc[maxn];                                 //每个节点所在的强连通分量的编号
int Index, Ssc_n, Top;                        //搜索时用的时间戳，强连通分量总数，栈顶指针

void Tarjan(int u)                                //u 当前搜索到的点
{
    Mark[u] = Root[u] = ++ Index;              //每找到一个点，对时间戳和根初始化
    Stack[Top ++] = u;                                 //压栈
    Instack[u] = true;                           //在栈中标记

    int v;

    for(int i= 0; i< G[u].size(); i++)                //向下搜索
    {
        v = G[u][i];
        if(Mark[v] == 0)                                //没到过的点
        {
            Tarjan(v);                                       //先向下搜索
            if(Root[u] > Root[v]) Root[u] = Root[v];            //更新根
        }
        else if(Instack[v] && Root[u] > Mark[v]) Root[u] = Mark[v]; //到过的点且点仍在栈中，试着看这个点能不能成为根
    }
/*对当前点的搜索结束*/
    if(Mark[u] == Root[u])                           //当前点本身时根
    {
        Ssc_n ++;                                   //更新强连通分量数

        do{                                   //栈中比它后入栈的元素在以它为根的强连通分量中
            v = Stack[-- Top];
            Instack[v] = false;
            Ssc[v] = Ssc_n;
        }while(v != u);                                  //直到它自己
    }
}

void SSC()
{
    memset(Mark, 0, sizeof Mark);                          //初始化时间戳和栈内标记
    memset(Instack, false, sizeof Instack);
    Index = Ssc_n = Top = 0;                               //初始化时间戳，强连通分量数，栈顶指针

    for(int i= 1; i<= N; i++)                                //保证图上所有点都访问到
        if(Mark[i] == 0) Tarjan(i);
}
/***************************Tarjan算法模板***************************/

int main()
{
    //freopen("in.txt", "r", stdin);

    scanf("%d", &N);
    for(int i= 1; i<= N; i++)
    {
        int x;
        while(scanf("%d", &x), x)
            G[i].push_back(x);
    }

    SSC();

    if(Ssc_n == 1)                                      //只有一个强连通分量的情况
    {
        cout << "1\n0\n";
        return 0;
    }

    memset(In, 0, sizeof In);                            //求每个强连通分量的入度和出度
    memset(Out, 0, sizeof Out);
    for(int u= 1; u<= N; u++)
    {
        for(int i= 0; i< G[u].size(); i++)
        {
            int v = G[u][i]; // 一条边 u->v
            if(Ssc[u] != Ssc[v])
                Out[Ssc[u]] ++, In[Ssc[v]] ++; // u的所属连通分量出度+1， v的所属连通分量入度+1
        }
    }

    int S1 = 0, S2 = 0;                                 //找入度为0、出度为0的点的数目
    for(int i= 1; i<= Ssc_n; i++)
    {
        if(In[i] == 0) S1 ++;
        if(Out[i] == 0) S2 ++;
    }
    cout<<Ssc_n<<endl;
    cout<<S1<<endl;
    cout<<S2<<endl;
    cout << S1 << endl << max(S1, S2) << endl;

    return 0;
}