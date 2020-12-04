/*
Author:buerguoo
name:HDU1754
Time:703ms
memory:4588KB

Data:2020-11-22 21:23:23
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
using namespace std;
//并查集
const int MAXN = 2e5+10;
int A[MAXN], n, N;
int sum[MAXN<<2];
void build(int n)
{
    N = 1;
    while(N < n+2)  N <<= 1;
    for(int i = 1;i <= n;++i)   sum[i+N] = A[i];
    for(int i = N-1;i > 0;--i)
        sum[i] = max(sum[i<<1], sum[i<<1|1]);
}
void Update(int L, int C)
{
    A[L] = C;
    sum[L+N] = C;
    for(int s=(L+N)>>1;s;s>>=1)
        sum[s] = max(sum[s<<1], sum[s<<1|1]);
}
int Query(int L, int R)
{
    int Max = 0;
    for(int s=L+N-1, t=R+N+1;s^t^1;s>>=1, t>>=1)
    {
        if(~s&1)    Max = max(Max, sum[s^1]);
        if( t&1)    Max = max(Max, sum[t^1]);
    }

    return Max;
}
int main()
{
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        for(int i = 1;i <= n;++i)
            scanf("%d", &A[i]);
        char o[2];
        int a, b;
        build(n);
        for(int i = 0;i < m;++i){
            scanf("%s%d%d", o, &a, &b);
        if(o[0] == 'Q')    printf("%d\n", Query(a, b));
        else if(o[0] == 'U')   Update(a, b);
        }
    }

    return 0;
}