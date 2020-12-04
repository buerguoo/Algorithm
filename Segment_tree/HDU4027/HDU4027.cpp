/*
Author:buerguoo
Time:639ms
memory:4592KB

Data:2020-11-25 12:12:56
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
typedef long long ll;
const int MAXN = 1e5+100;
const int INF = 0x3f3f3f3f;
ll A[MAXN];
ll sum[MAXN<<2];
void PushUp(int rt){sum[rt] = sum[rt<<1] + sum[rt<<1|1];}
void build(int l, int r, int rt)
{
    if(l == r){
        sum[rt] = A[l];
        return ;
    }
    int m = (l+r)>>1;
    build(l, m, rt<<1);
    build(m+1, r, rt<<1|1);
    PushUp(rt);
}
void Update(int L, int R, int l, int r, int rt)
{
    if(l == r){
        sum[rt] = sqrt(sum[rt]);
        return ;
    }
    if(L <= l && R >= r && sum[rt] == r-l+1)
        return ;
    int m = (l+r)>>1;
    if(L <= m)  Update(L, R, l, m, rt<<1);
    if(R > m)   Update(L, R, m+1, r, rt<<1|1);
    PushUp(rt);
}
ll Query(int L, int R, int l, int r, int rt)
{
    if(L <= l && R >= r){
        return sum[rt];
    }
    ll ans = 0;
    int m = (l+r)>>1;
    if(L <= m)  ans += Query(L, R, l, m, rt<<1);
    if(R > m)   ans += Query(L, R, m+1, r, rt<<1|1);
    return ans;
}
int main()
{
    int N, t = 0;
    while(~scanf("%d", &N)){
        for(int i = 1;i <= N;++i)   scanf("%lld", &A[i]);
        build(1, N, 1);
        printf("Case #%d:\n", ++t);
        int M;
        scanf("%d", &M);
        int T, X, Y;
        for(int i = 0;i < M;++i){
            scanf("%d%d%d", &T, &X, &Y);
            if(X > Y)   swap(X, Y);
            if(!T)  Update(X, Y, 1, N, 1);
            else    printf("%lld\n", Query(X, Y, 1, N, 1));
        }
        printf("\n");
    }
    return 0;
}