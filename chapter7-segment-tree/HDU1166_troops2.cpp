#include <bits/stdc++.h>
// http://acm.hdu.edu.cn/showproblem.php?pid=1166
using namespace std;
#define M(a, b) memset(a,b,sizeof(a))

// memset(a,0x3f,sizeof(a))
//memset(a,0xcf,sizeof(a))
typedef long long LL;

const int maxn = 0x3f3f3f3f;

class SegmentTree {
public:
    SegmentTree(int N) {
        this->N = N; // 叶子节点个数
        int n = (1 << ((int) ceil(log(N) / log(2) + 1))); // 总的节点个数
        tree = vector<int>(n, 0); // 构造线段树的数据结构
        lazy = vector<int>(n, 0); // 延迟增量值
    }

    int query(int L, int R) { // lazy 意思 查询的时候才更新区间高度，update的时候不更新
        return queryUtil(1, 0, N - 1, L, R);
    }

    int queryUtil(int index, int s, int e, int L, int R) {
        if (lazy[index] != 0) {
            int update = lazy[index];
            lazy[index] = 0;
            tree[index] = max(tree[index], update);
            if (s != e) {
                lazy[2 * index] = max(lazy[2 * index], update);
                lazy[2 * index + 1] = max(lazy[2 * index + 1], update);
            }
        }
        if (s > e || s > R || e < L) {
            return 0;
        }
        if (s >= L && e <= R) {
            return tree[index];
        }
        int mid = s + (e - s) / 2;
        return max(queryUtil(2 * index, s, mid, L, R), queryUtil(2 * index + 1, mid + 1, e, L, R));
    }

    void update(int L, int R, int h) { // lazy 意思 查询的时候才更新区间高度，update的时候不更新
        updateUtil(1, 0, N - 1, L, R, h);
    }

    void updateUtil(int index, int s, int e, int L, int R, int h) {
        if (lazy[index] != 0) {
            int update = lazy[index];
            lazy[index] = 0;
            tree[index] = max(tree[index], update);
            if (s != e) {
                lazy[2 * index] = max(lazy[2 * index], update);
                lazy[2 * index + 1] = max(lazy[2 * index + 1], update);
            }
        }
        if (s > e || s > R || e < L) {
            return;
        }
        if (s >= L && e <= R) {
            tree[index] = max(tree[index], h);
            if (s != e) {
                lazy[2 * index] = max(lazy[2 * index], h);
                lazy[2 * index + 1] = max(lazy[2 * index + 1], h);
            }
            return;
        }
        int mid = s + (e - s) / 2;
        updateUtil(2 * index, s, mid, L, R, h);
        updateUtil(2 * index + 1, mid + 1, e, L, R, h);
        tree[index] = max(tree[2 * index], tree[2 * index + 1]);
    }

private:
    vector<int> tree;
    vector<int> lazy;
    int N;
};


int main() {
    int T;
    cin>>T;
    while (T--) {
        int input_N;
        cin >> input_N;
        SegmentTree *segment_tree = new SegmentTree(input_N);

        int nums[input_N];
        for (int i = 0; i < input_N; i++) {
            cin >> nums[i];
            segment_tree->update(i,i,nums[i]);
            printf("%d, ",segment_tree->query(i,i));
        }


        char instr[10];
        int i_a, i_b;
        while (scanf("%s", instr) && strcmp(instr,"End")!=0) {
            cin >> i_a >> i_b;
            i_a--;

            int l, r;
            if (strcmp(instr,"Query")==0) {
                i_b--;

                l = i_a;
                r = i_b;
                int h = segment_tree->query(l, r);
                cout << h << endl;

            } else if (strcmp(instr,"Add")==0) {
                l = i_a;
                r = i_a;
                int h = segment_tree->query(l, r) + i_b;
                segment_tree->update(l, r, h); // [L, R] 区间高度更新

            } else if (strcmp(instr,"Sub")==0) {
                l = i_a;
                r = i_a;
                int h = segment_tree->query(l, r) - i_b;
                segment_tree->update(l, r, h); // [L, R] 区间高度更新
            }
        }
    }

    return 0;
}