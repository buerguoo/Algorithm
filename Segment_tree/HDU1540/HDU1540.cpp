/*
Author:buerguoo
Time:374ms
memory:3321KB

Data:2020-11-25 23:29:41
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
const int MAXN = 50010;
const int INF = 0x3f3f3f3f;
int sum[MAXN<<2], pre[MAXN<<2], suf[MAXN<<2];
int A[MAXN];
int tol;
void PushUp(int rt, int len)
{
    pre[rt] = pre[rt<<1];
    suf[rt] = suf[rt<<1|1];
    if(pre[rt<<1]==(len-(len>>1))) pre[rt] += pre[rt<<1|1];
    if(suf[rt<<1|1]==(len>>1))   suf[rt] += suf[rt<<1];
    sum[rt] = max(suf[rt<<1]+pre[rt<<1|1], max(sum[rt<<1], sum[rt<<1|1]));
}
void build(int l, int r, int rt)
{
    if(l == r){
        sum[rt] = pre[rt] = suf[rt] = 1;
        return ;
    }
    int m = (l+r)>>1;
    build(l, m, rt<<1);
    build(m+1, r, rt<<1|1);
    PushUp(rt, r-l+1);
}
void Update(int L, int C, int l, int r, int rt)
{
    if(r == l){
        sum[rt] = pre[rt] = suf[rt] = C;
        return ;
    }
    int m = (l+r)>>1;
    if(L <= m)  Update(L, C, l, m, rt<<1);
    else    Update(L, C, m+1, r, rt<<1|1);
    PushUp(rt, r-l+1);
}
int  Query(int L, int l, int r, int rt)
{
    if(!sum[rt] || sum[rt]==r-l+1 || l==r)
        return sum[rt];
    int m = (l+r)>>1;
    if(L <= m){
        if(L+suf[rt<<1]>m) return suf[rt<<1]+pre[rt<<1|1];
        else return Query(L, l, m, rt<<1);
    }
    else{
        if(L-pre[rt<<1|1]<=m)  return suf[rt<<1]+pre[rt<<1|1];
        else return Query(L, m+1, r, rt<<1|1);
    }
}
int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        build(1, n, 1);
        char s[2];
        int L;
        tol = 0;
        while(m--){
            scanf("%s", s);
            if(s[0] == 'D'){
                scanf("%d", &L);
                Update(L, 0, 1, n, 1);
                A[tol++] = L;
            }
            else if(s[0] == 'Q'){
                scanf("%d", &L);
                printf("%d\n", Query(L, 1, n, 1));
            }
            else Update(A[--tol], 1, 1, n, 1);
        }
    }
    
    return 0;
}