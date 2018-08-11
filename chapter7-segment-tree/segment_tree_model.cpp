#include <stdio.h>
#include <math.h>
// https://vjudge.net/contest/66989#problem/A

const int MAX = 50010 * 4;
int segment[MAX];//存放线段树，因为类似完全二叉树， 所以可以用数组来表示 从1 开始
//更新root节点的值，即兵营里的人数
void pushUp(int root) {
    segment[root] = segment[root * 2] + segment[root * 2 + 1];
}

//建树，只需要两个点，一个起点，一个终点
void buildTree(int root, int left, int right) {
    if (left == right) {
        //输入兵营里的人数
        scanf("%d", &segment[root]);
        return;
    }
    int mid = (left + right) / 2;
    buildTree(root * 2, left, mid);
    buildTree(root * 2 + 1, mid + 1, right);
    //调整它的上面节点的值
    pushUp(root);
}

/*更新最下面节点的值，而且要更新以上给他有关联的节点的值, root代表根节点，
pos代表更新的位置， add_num 代表增加的值，如果是负数，说明是减少的，left和right
分别为当前节点区间的左右端点*/
/**
 *
 * @param root root代表根节点
 * @param pos pos代表更新的位置
 * @param add_num add_num 代表增加的值
 * @param left left和right
分别为当前节点区间的左右端点
 * @param right
 */
void update(int root, int pos, int add_num, int left, int right) {
    if (left == right) { // 到达叶子节点
        segment[root] += add_num;
        return;
    }
    int mid = (left + right) / 2;
    if (pos <= mid) // 左区间
        update(root * 2, pos, add_num, left, mid);
    else // 右区间
        update(root * 2 + 1, pos, add_num, mid + 1, right);
    //向上调整
    pushUp(root);
}

//获取指定区间内的总数
/**
 *
 * @param root  当前节点的下标
 * @param left 要获取的区间的left
 * @param right
 * @param L 树的当前节点区间L
 * @param R
 * @return 获取指定区间内的总和
 */
int getSum(int root, int left, int right, int L, int R) {
    if (left == L && right == R) {
        return segment[root];
    }
    int mid = (L + R) / 2;
    int res = 0;
    //如果在当前节点的右半个区间内
    if (left > mid) {
        res += getSum(root * 2 + 1, left, right, mid + 1, R);
    }
        //如果在当前节点的左半个区间内
    else if (right <= mid) {
        res += getSum(root * 2, left, right, L, mid);
    }
        //一个在左边，一个在右边
    else {
        res += getSum(root * 2, left, mid, L, mid);
        res += getSum(root * 2 + 1, mid + 1, right, mid + 1, R);
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {

        int n;
        scanf("%d", &n);
        buildTree(1, 1, n);//建树，同时输入节点的值，也就是兵营的人数
        char op[10];
        int t1, t2;
        printf("Case %d:\n", kase);
        while (scanf("%s", op)) {
            if (op[0] == 'E')
                break;
            scanf("%d %d", &t1, &t2);
            if (op[0] == 'A') {
                update(1, t1, t2, 1, n);
            } else if (op[0] == 'S') {
                update(1, t1, -t2, 1, n);
            } else {
                printf("%d\n", getSum(1, t1, t2, 1, n));
            }
        }
    }
    return 0;
}