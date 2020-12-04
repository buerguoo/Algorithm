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
int A[MAXN], n, N;//n表示当前数组A的个数,N表示扩充元素的个数
int sum[MAXN], add[MAXN];
//建树
void build(int n)
{
    int N = 1;
    //得到N的值
    while(N < n+2) N<<=2;
    //更新叶子结点，在左右多扩充结点
    for(int i = 1;i <= n;++i)   sum[N+i] = A[i];
    //更新非叶节点
    for(int i = N-1;i > 0;--i){
        //更新非叶节点
        sum[i] = sum[i<<1] + sum[i<<1|1];
        //清空非叶节点的标记
        add[i] = 0;
    }
}
//点修改
void Update(int L, int C)
{
    for(int i = L+N;i;i >>= 1)
        sum[i] += C;
}
//点修改下的区间查询
int Query(int L, int R)
{   
    //只要左区间在左子树，右区间在右子树，就可以相加
    int ans = 0; 
    for(int s=L+N-1,t=R+N+1;s^t^1;s>>=1, t>>=1){
        if(~s&1)    ans += sum[s^1];
        if( t&1)    ans += sum[s^1];
    }
    return ans;
}
//区间修改
void Update_sec(int L, int R, int C)
{
    int s, t, ln = 0, rn = 0, x = 1;
    //ln表示s走过的路径上的节点包含的数的数量
    //rn表示t走过的节点包含几个数
    //x表示当前节点包含几个数
    for(s=L+N-1, t=R+N+1;s^t^1;s>>=1,t>>=1,x<<=1){
        //更新sum
        sum[s] += C*ln;
        sum[t] += C*rn;
        //处理add
        if(~s&1)    add[s^1]+=C, sum[s^1]+=C*x, ln+=x;
        if( t&1)    add[t^1]+=C, sum[s^1]+=C*x, rn+=x;
    }
    for(;s;s>>=1, t>>=1){
        sum[s] += C*ln;
        sum[t] += C*rn;
    }
}
//区间修改下的区间查询
int _Query(int L, int R)
{
    int s, t, Ln=0, Rn=0, x=1;
    int ans = 0;
    for(s=L+N-1, t=R+N+1;s^t^1;s>>=1, t>>=1, x<<=1){
        //根据标记更新
        if(add[s])  ans += add[s]*Ln;
        if(add[t])  ans += add[t]*Rn;
        //常规更新
        if(~s&1)    ans += sum[s^1], Ln+=x;
        if( t&1)    ans += sum[t^1], Rn+=x;
    }
    //处理上层标记
    for(;s;s>>=1, t>>=1){
        ans += add[s]*Ln;
        ans += add[t]*Rn;
    }

    return ans;
}