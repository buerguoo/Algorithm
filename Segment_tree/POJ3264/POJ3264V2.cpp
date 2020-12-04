/*
Author:buerguoo
Time:2110MS
memory:1346KB

Data:2020-11-25 11:09:38
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
const int MAXN = 50010;
const int INF = 0x3f3f3f3f;
int A[MAXN];
int Max[MAXN<<2], Min[MAXN<<2];
//递归形式
void PushUp(int rt){
    Max[rt] = max(Max[rt<<1], Max[rt<<1|1]);
    Min[rt] = min(Min[rt<<1], Min[rt<<1|1]);
}
void build(int l, int r, int rt)
{
    if(l == r){
        Max[rt] = Min[rt] = A[l];
        return ;
    }
    int m = (l+r)>>1;
    build(l, m, rt<<1);
    build(m+1, r, rt<<1|1);
    PushUp(rt);
}
int Query(int L, int R, int l, int r, int rt)
{
    if(L <= l && R >= r){
        return Max[rt];
    }
    int _max = 0;
    int m = (l+r)>>1;
    if(L <= m)  _max = max(Query(L, R, l, m, rt<<1), _max);  
    if(R > m)   _max = max(Query(L, R, m+1, r, rt<<1|1), _max);    

    return _max;
}
int _Query(int L, int R, int l, int r, int rt)
{
    if(L <= l && R >= r){
        return Min[rt];
    }
    int _min = INF;
    int m = (l+r)>>1;
    if(L <= m)  _min = min(_Query(L, R, l, m, rt<<1), _min);  
    if(R > m)   _min = min(_Query(L, R, m+1, r, rt<<1|1), _min);    

    return _min;
}
int main()
{
    int N, Q;
    scanf("%d%d", &N, &Q);
    for(int i = 1;i <= N;++i)   scanf("%d", &A[i]);
    build(1, N, 1);
    int A, B;
    for(int i = 0;i < Q;++i){
        scanf("%d%d", &A, &B);
        printf("%d\n", Query(A, B, 1, N, 1)-_Query(A, B, 1, N, 1));
    }
    return 0;
}