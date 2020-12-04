/*
Author:buerguoo
Time:6442ms
memory:12052Kb

Data:2020-11-27 00:59:11
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
#define FILL(a, b)  memset(a, b, sizeof(a))
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
typedef long long LL;
const int MOD = 10007;
const int mod = 10007;
const int MAXN = 1e5+5;
const int INF = 0x3f3f3f3f;
LL sum1[MAXN<<2], sum2[MAXN<<2], sum3[MAXN<<2];
LL add[MAXN<<2], mul[MAXN<<2];
void PushUp(int rt)
{
    sum1[rt] = (sum1[rt<<1] + sum1[rt<<1|1])%MOD;
    sum2[rt] = (sum2[rt<<1] + sum2[rt<<1|1])%MOD;
    sum3[rt] = (sum3[rt<<1] + sum3[rt<<1|1])%MOD;
}
void build(int l, int r, int rt)
{
    sum1[rt] = sum2[rt] = sum3[rt] = 0;
    add[rt] = 0, mul[rt] = 1;
    if(l == r) return ;
    int m = (l+r)>>1;
    build(lson);
    build(rson);
    //PushUp(rt);
}

void PushDown(int rt, int ln, int rn)
{
    if(mul[rt]!=1){
        mul[rt<<1] = mul[rt]*mul[rt<<1]%MOD;
        mul[rt<<1|1] = mul[rt]*mul[rt<<1|1]%MOD;
        add[rt<<1] = add[rt<<1]*mul[rt]%MOD;
        add[rt<<1|1] = add[rt<<1|1]*mul[rt]%MOD;
        LL u = mul[rt]*mul[rt]%MOD, v = mul[rt]*mul[rt]*mul[rt]%MOD;
        sum1[rt<<1] = sum1[rt<<1]*mul[rt]%MOD;
        sum1[rt<<1|1] = sum1[rt<<1|1]*mul[rt]%MOD;
        sum2[rt<<1] = sum2[rt<<1]*u%MOD;
        sum2[rt<<1|1] = sum2[rt<<1|1]*u%MOD;
        sum3[rt<<1] = sum3[rt<<1]*v%MOD;
        sum3[rt<<1|1] = sum3[rt<<1|1]*v%MOD;
        mul[rt] = 1;
    }
    if(add[rt]!=0){
        add[rt<<1] = (add[rt<<1]+add[rt])%MOD;
        add[rt<<1|1] = (add[rt<<1|1]+add[rt])%MOD;
        LL u = add[rt]*add[rt]%MOD, v = add[rt]*add[rt]*add[rt]%MOD;
        LL t1 = sum1[rt<<1], t2 = sum1[rt<<1|1];
        LL t3 = sum2[rt<<1], t4 = sum2[rt<<1|1];
        sum1[rt<<1] = (sum1[rt<<1] + ln*add[rt])%MOD;
        sum1[rt<<1|1] = (sum1[rt<<1|1] + rn*add[rt])%MOD;
        sum2[rt<<1] = (sum2[rt<<1] + ln*u + 2*add[rt]*t1)%MOD;
        sum2[rt<<1|1] = (sum2[rt<<1|1] + rn*u + 2*add[rt]*t2)%MOD;
        sum3[rt<<1] = (sum3[rt<<1] + v*ln + 3*t3*add[rt] + 3*t1*u)%MOD;
        sum3[rt<<1|1] = (sum3[rt<<1|1] + v*rn + 3*t4*add[rt] + 3*t2*u)%MOD;
        add[rt] = 0;
    }
    
}
void Update(int L, int R, LL C, int T, int l, int r, int rt)
{
    if(L <= l && R >= r){
        LL u = C*C%MOD, v = C*C*C%MOD;
        int len = r-l+1;
        if(T == 1){
            LL t1 = sum1[rt], t2 = sum2[rt];
            add[rt] = (add[rt] + C) % MOD;
            sum1[rt] = (sum1[rt] + C*len)%MOD;
            sum2[rt] = (sum2[rt] + u*len + 2*t1*C)%MOD;
            sum3[rt] = (sum3[rt] + v*len + 3*t1*u + 3*t2*C)%MOD;
        }
        else if(T == 2){
            mul[rt] = mul[rt]*C%MOD;
            add[rt] = add[rt]*C%MOD;
            sum1[rt] = sum1[rt]*C%MOD;
            sum2[rt] = sum2[rt]*u%MOD;
            sum3[rt] = sum3[rt]*v%MOD;
        }
        else{
            add[rt] = C;mul[rt] = 0;
            sum1[rt] = C*len%MOD;
            sum2[rt] = u*len%MOD;
            sum3[rt] = v*len%MOD;
        }
        return ;
    }
    int m = (l+r)>>1;
    PushDown(rt, m-l+1, r-m);
    if(L <= m)  Update(L, R, C, T, lson);
    if(R > m)   Update(L, R, C, T, rson);
    PushUp(rt);
}
LL Query(int L, int R, int P, int l, int r, int rt)
{
    if(L <= l && R >= r){
        if(P == 1)  return sum1[rt];
        else if(P == 2) return sum2[rt];
        else return sum3[rt];
    }
    int m = (l+r)>>1;
    LL ans = 0;
    PushDown(rt, m-l+1, r-m);
    //Pushdown(rt, r-l+1);
    if(L <= m)  ans += Query(L, R, P, lson);
    if(R > m)   ans += Query(L, R, P, rson);

    return ans%MOD;
}
int main()
{
    int n, m;
    while(~scanf("%d%d", &n, &m)){
         if(n == 0 && m == 0)    break;
        int T, x, y, c;
        build(1, n, 1);
        for(int i = 0;i < m;++i){
            scanf("%d%d%d%d", &T, &x, &y, &c);
            if(T == 4)  printf("%lld\n", Query(x, y, c, 1, n, 1));
            else    Update(x, y, c, T, 1, n, 1);
        }
    }
    return 0;
}