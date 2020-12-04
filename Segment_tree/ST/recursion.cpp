//线段树操作的递归形式
//进行区间修改时采用，比非递归形式（仅在区间修改时）简单
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
using namespace std;
const int MAXN = 10000;
int sum[MAXN<<2];//存原数组
int add[MAXN<<2];//惰性标记
int A[MAXN], n;//对应输入
void PushUp(int rt){sum[rt] = sum[rt<<1] + sum[rt<<1|1];}
//建立线段树
//[l, r]是代表区间，rt代表位置
void Construt(int l, int r, int rt)
{
    //叶子节点
    if(l == r){
        sum[rt] = A[l];
        return ;
    }
    //找到中间数，左右递归
    int m = (l+r)>>1;
    Construt(l, m, rt<<1);
    Construt(m+1, r, rt<<1|1);
    //更新
    PushUp(rt);
}
//点修改
void Update(int L, int C, int l, int r, int rt)
{
    //到达叶结点
    if(l == r){
        sum[rt] += C;
        return ;
    }
    //判断查询方向
    int m = (l+r)>>1;
    if(L <= m) Update(L, C, l, m, rt<<1);
    if(r > m) Update(L, C, m+1, r, rt<<1|1);
    //更新
    PushUp(rt);
}
//区间修改
void Update_section(int L, int R, int C, int l, int r, int rt)
{
    if(L <= l && R >= r){
        //更新数字和，向上保持正确
        sum[rt] += C*(l-r+1);
        //增加Add标记，表示本区间的Sum正确，子区间的Sum仍需要根据Add的值来调整
        add[rt] += C;
        return ;
    }
    int m = (l+r)>>1;
    PushDown(rt, m-l+1, r-m);//下推标记
    if(L <= m)  Update_section(L, R, C, l, m, rt<<1);
    if(R >= m)  Update_section(L, R, C, l, r, rt<<1|1);
    PushUp(rt);//更新节点
}
//区间查询
//ln表示左子树的个数，rn表示右子树的个数
void PushDown(int rt, int ln, int rn)
{
    if(add[rt]){
        //下推标记
        add[rt<<1] += add[rt];
        add[rt<<1|1] += add[rt];
        //修改子节点的sum
        sum[rt<<1] += add[rt]*ln;
        sum[rt<<1|1] += add[rt]*rn;
        //节点归零
        add[rt] = 0;
    }
}
int Query(int L, int R, int l, int r, int rt)
{
    //[l, r]在[L, R]区间内，直接返回
    if(l >= L && r <= R){
        return sum[rt];
    }
    //累加值
    int ans = 0;
    int m = (l+r)>>1;
    //在查询时更新
    PushDown(rt, l-m+1, r-m);
    if(L <= m)  Query(L, R, l, m, rt<<1);//左子区间重合
    else Query(L, R, m+1, r, rt<<1|1);//右子区间重合
    return ans;
}