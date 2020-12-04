/*
Author:buerguoo
Time:405ms
memory:9980Kb

Data:2020-11-27 21:56:47
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
typedef long long ll;
const int MAXN = 100000+5;
const int INF = 0x3f3f3f3f;
int sum[MAXN<<2][2], pre[MAXN<<2][2], suf[MAXN<<2][2];
int add[MAXN<<2][2];
void PushUp(int t, int len, int rt)
{
    pre[rt][t] = pre[rt<<1][t];
    suf[rt][t] = suf[rt<<1|1][t];
    if(pre[rt<<1][t] == (len-(len>>1))) pre[rt][t] += pre[rt<<1|1][t];
    if(suf[rt<<1|1][t] == (len>>1)) suf[rt][t] += suf[rt<<1][t];
    sum[rt][t] = max(suf[rt<<1][t]+pre[rt<<1|1][t], max(sum[rt<<1][t], sum[rt<<1|1][t]));
}
void Build(int t, int l, int r, int rt)
{
    add[rt][t] = -1;
    sum[rt][t] = pre[rt][t] = suf[rt][t] = r-l+1;
    if(l == r)  return ;
    int m = (l+r)>>1;
    Build(t, lson);
    Build(t, rson);
    //PushUp(t, r-l+1, rt);
}
void PushDown(int t, int ln, int rn, int rt)
{
    
    if(add[rt][t]!=-1){
        add[rt<<1][t] = add[rt<<1|1][t] = add[rt][t];
        sum[rt<<1][t] = pre[rt<<1][t] = suf[rt<<1][t] = add[rt][t]*ln;
        sum[rt<<1|1][t] = pre[rt<<1|1][t] = suf[rt<<1|1][t] = add[rt][t]*rn;
        add[rt][t] = -1;
    }
}
void Update(int t, int L, int R, int C, int l, int r, int rt)
{
    if(L <= l && R >= r){
        pre[rt][t] = sum[rt][t] = suf[rt][t] = C*(r-l+1);
        add[rt][t] = C;
        return ;
    }
    int m = (l+r)>>1;
    PushDown(t, m-l+1, r-m, rt);
    if(L <= m)  Update(t, L, R, C, lson);
    if(R > m)   Update(t, L, R, C, rson);
    PushUp(t, r-l+1, rt);
}
int Query(int t, int len, int l, int r, int rt)
{
    if(l == r)  return l;
    int m = (l+r)>>1;
    PushDown(t, m-l+1, r-m, rt);
    if(sum[rt<<1][t] >= len)   return Query(t, len, lson);
    else if(suf[rt<<1][t]+pre[rt<<1|1][t]>=len)  return m-suf[rt<<1][t]+1;
    else return Query(t, len, rson);
}

int main()
{
    int C, c = 0;
    scanf("%d", &C);
    while(c++ < C){
        int T, N;
        scanf("%d%d", &T, &N);
        Build(0, 1, T, 1);
        Build(1, 1, T, 1);
        char s[10];
        int A, B;
        printf("Case %d:\n", c);
        while(N--){
            scanf("%s", s);
            if(s[0] == 'D'){
                scanf("%d", &A);
                if(sum[1][0] >= A){
                    int st = Query(0, A, 1, T, 1);
                    printf("%d,let's fly\n", st);
                    Update(0, st, st+A-1, 0, 1, T, 1);
                }
                else printf("fly with yourself\n");
            }
            else if(s[0] == 'N'){
                scanf("%d", &A);
                if(sum[1][0] >= A){
                    int st = Query(0, A, 1, T, 1);
                    printf("%d,don't put my gezi\n", st);
                    Update(0, st, st+A-1, 0, 1, T, 1);
                    Update(1, st, st+A-1, 0, 1, T, 1);
                }
                else if(sum[1][1] >= A){
                    int st = Query(1, A, 1, T, 1);
                    printf("%d,don't put my gezi\n", st);
                    Update(0, st, st+A-1, 0, 1, T, 1);
                    Update(1, st, st+A-1, 0, 1, T, 1);
                }
                else printf("wait for me\n");
            }
            else{
                scanf("%d%d", &A, &B);
                Update(0, A, B, 1, 1, T, 1);
                Update(1, A, B, 1, 1, T, 1);
                printf("I am the hope of chinese chengxuyuan!!\n");
            }
        }
    }
    return 0;
}