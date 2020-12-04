/*
Author:buerguoo
name:HDU1166
Time:249ms
memory:2460KB

Data:2020-11-22 17:35:50
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
void Update(int L, int C, int l, int r, int rt)
{
    if(L == l && L == r){
        sum[rt] += C;
        return ;
    }
    int m = (l+r)>>1;
    if(L <= m)    Update(L, C, l, m, rt<<1);
    else Update(L, C, m+1, r, rt<<1|1);
    PushUp(rt);
}
int Query(int L, int R, int l, int r, int rt)
{
    if(L <= l && R >= r){
        return sum[rt];
    }
    int ans = 0;
    int m = (l+r)>>1;
    if(L <= m)  ans += Query(L, R, l, m, rt<<1);
    if(R > m)   ans += Query(L, R, m+1, r, rt<<1|1);

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
        build(1, n, 1);
        while(order[0] != 'E'){
            int L, R, C;
            switch (order[0])
            {
            case 'Q':
                scanf("%d%d", &L, &R);
                printf("%d\n", Query(L, R, 1, n, 1));
                break;
            case 'A':
                scanf("%d%d", &L, &C);
                Update(L, C, 1, n, 1); 
                break;
            case 'S':
                scanf("%d%d", &L, &C);
                Update(L, -C, 1, n, 1);
                break;
            }
            scanf("%s", order);
        }
    }
    return 0;
}
