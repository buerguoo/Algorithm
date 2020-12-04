/*
Author:buerguoo
Time:1438MS
memory:1312KB

Data:2020-11-25 10:56:49
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
//非递归形式的线段树
int n, N;
void build(int n)
{
    N = 1;
    while(N < n+2)  N<<=1;
    for(int i = 1;i <= n;++i)   Max[i+N] = A[i], Min[i+N] = A[i];
    for(int i = N-1;i > 0;--i)  
        Max[i] = max(Max[i<<1], Max[i<<1|1]), Min[i] = min(Min[i<<1], Min[i<<1|1]);
}
int Query(int L, int R)
{
    int _max = 0, _min = INF;
    for(int s=L+N-1, t=R+N+1;s^t^1;s>>=1, t>>=1){
        if(~s&1)    _max = max(_max, Max[s^1]), _min = min(_min, Min[s^1]);
        if( t&1)    _max = max(_max, Max[t^1]), _min = min(_min, Min[t^1]);
    }

    return _max-_min;
}
int main()
{
    int N, Q;
    scanf("%d%d", &N, &Q);
    for(int i = 1;i <= N;++i)   scanf("%d", &A[i]);
    build(N);
    int A, B;
    for(int i = 0;i < Q;++i){
        scanf("%d%d", &A, &B);
        printf("%d\n", Query(A, B));
    }
    return 0;
}