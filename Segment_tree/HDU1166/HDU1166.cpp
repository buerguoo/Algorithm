/*
Author:buerguoo
name:HDU1166
Time:218ms
memory:2456KB

Data:2020-11-22 17:00:51
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
const int MAXN = 50010;
int A[MAXN], n, N;
int sum[MAXN<<2];
void build(int n)
{
    N = 1;
    while(N < n+2)  N <<= 1;
    for(int i = 1;i <= n;++i)   sum[N+i] = A[i];
    for(int i = N-1;i > 0;--i)  sum[i] = sum[i<<1] + sum[i<<1|1];
}
void Update(int L, int C)
{
    A[L] += C;
    for(int s=L+N;s;s>>=1)
        sum[s] += C;
}
int Query(int L, int R)
{
    int ans = 0;
    for(int s=L+N-1,t=R+N+1;s^t^1;s>>=1,t>>=1)
    {
        if(~s&1)    ans += sum[s^1];
        if( t&1)    ans += sum[t^1];
    }
    return ans;
}
int main()
{
    int T, t=0;
    scanf("%d", &T);
    while(t++ < T){
        scanf("%d", &n);
        for(int i = 1;i <= n;++i)
            scanf("%d", &A[i]);
        printf("Case %d:\n", t);
        char order[10];
        scanf("%s", order);
        build(n);
        while(order[0] != 'E'){
            int L, R, C;
            switch (order[0])
            {
            case 'Q':
                scanf("%d%d", &L, &R);
                printf("%d\n", Query(L, R));
                break;
            case 'A':
                scanf("%d%d", &L, &C);
                Update(L, C); 
                break;
            case 'S':
                scanf("%d%d", &L, &C);
                Update(L, -C);
                break;
            }
            scanf("%s", order);
        }
    }
    return 0;
}
