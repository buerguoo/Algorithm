/*
Author:buerguoo
name:POJ3468
Time:1672ms
memory:4984KB

Data:2020-11-22 22:51:39
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
const int MAXN = 1e5+10;
int n, N;
long long int A[MAXN];
long long int sum[MAXN<<2], add[MAXN<<2];
void PushUp(int rt) {sum[rt] = sum[rt<<1] + sum[rt<<1|1];}
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
void PushDown(int rt, int ln, int rn)
{
    if(add[rt]){
        add[rt<<1] += add[rt];
        add[rt<<1|1] += add[rt];
        sum[rt<<1] += add[rt]*ln;
        sum[rt<<1|1] += add[rt]*rn;
        add[rt] = 0;
    }
}
void Update(int L, int R, int C, int l, int r, int rt)
{
    if(L <= l && R >= r){
        sum[rt] += C*(r-l+1);
        add[rt] += C;
        return ;
    }
    int m = (l+r)>>1;
    PushDown(rt, m-l+1, r-m);
    if(L <= m)  Update(L, R, C, l, m, rt<<1);
    if(R > m)   Update(L, R, C, m+1, r, rt<<1|1);
    PushUp(rt);
}
long long int Query(int L, int R, int l, int r, int rt)
{
    if(L <= l && R >= r){
        return sum[rt];
    }
    long long int ans = 0;
    int m = (l+r)>>1;
    PushDown(rt, m-l+1, r-m);
    if(L <= m)  ans += Query(L, R, l, m, rt<<1);
    if(R > m)   ans += Query(L, R, m+1, r, rt<<1|1);
    
    return ans;
}
int main()
{
    int N, Q;
    scanf("%d%d", &N, &Q);
    for(int i = 1;i <= N;i++)   scanf("%lld", &A[i]);
    //memset(add, 0, sizeof(add));
    build(1, N, 1);
    char s[2];
    int a, b, c;
    for(int i = 0;i < Q;++i)
    {
        scanf("%s", s);
        if(s[0] == 'Q'){
            scanf("%d%d", &a, &b);
            printf("%lld\n", Query(a, b, 1, N, 1));
        } 
        else if(s[0] == 'C'){
            scanf("%d%d%d", &a, &b, &c);
            Update(a, b, c, 1, N, 1);
        }
    }

    return 0;
}
