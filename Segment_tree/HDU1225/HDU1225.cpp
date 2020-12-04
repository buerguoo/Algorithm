/*
Author:buerguoo
Time:280ms
memory:2080KB

Data:2020-11-29 17:05:47
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
#define rson m, r, rt<<1|1
#define ls(i)   i<<1
#define rs(i)   i<<1|1
typedef long long ll;
const int MAXN = 2005;
const int INF = 0x3f3f3f3f;
struct Node{
    int l, r;
    double lr, rr, sum, sum2;
    int cover;
}T[MAXN<<2];
struct Line{
    double x, y1, y2;
    int val;
    Line(double _x=0, double _y1=0, double _y2=0, int _v=0):x(_x), y1(_y1), y2(_y2), val(_v){}
    bool operator < (const Line &r) const{
        if(x == r.x)    return val>r.val;
        return x<r.x;
    }
}L[MAXN];
bool cmp(double a, double b)
{
    return a<b;
}
double Y[MAXN];
void PushUp(int rt)
{
    if(T[rt].cover){
        T[rt].sum = T[rt].rr-T[rt].lr;
    }
    else if(T[rt].l+1==T[rt].r)
        T[rt].sum = 0;
    else
        T[rt].sum = T[ls(rt)].sum + T[rs(rt)].sum;
    if(T[rt].cover > 1){
        T[rt].sum2 = T[rt].rr-T[rt].lr;
    }
    else if(T[rt].l+1==T[rt].r)
        T[rt].sum2 = 0;
    else if(T[rt].cover == 1)
        T[rt].sum2 = T[ls(rt)].sum + T[rs(rt)].sum;
    else
        T[rt].sum2 = T[ls(rt)].sum2 + T[rs(rt)].sum2;
}
void Build(int l, int r, int rt)
{
    T[rt].l = l, T[rt].r = r;
    T[rt].cover = 0;
    T[rt].sum2= T[rt].sum = 0;
    T[rt].lr = Y[l]; 
    T[rt].rr = Y[r];
    if(l+1>=r)  return ;
    int m = (l+r)>>1;
    Build(lson);
    Build(rson);
}
void Update(double L, double R, int C, int rt)
{
    if(L <= T[rt].lr && R >= T[rt].rr){
        T[rt].cover += C;
        PushUp(rt);
        return ;
    }
    if(L < T[ls(rt)].rr)    Update(L, R, C, ls(rt));
    if(R > T[rs(rt)].lr)    Update(L, R, C, rs(rt));
    PushUp(rt);
}
int main()
{
    int t;
    scanf("%d", &t);
    while(t--){
        int N;
        scanf("%d", &N);
        double x1, x2, y1, y2;
        for(int i = 1;i <= N;++i){
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            Y[i] = y1, Y[i+N] = y2; 
            L[i] = Line(x1, y1, y2, 1);
            L[i+N] = Line(x2, y1, y2, -1);
        }
        sort(Y+1, Y+1+N*2, cmp);    
        sort(L+1, L+1+N*2);
        int m = unique(Y+1, Y+1+N*2)-Y-1;
        Build(1, m, 1);
        double ans = 0;
        for(int i = 1;i < 2*N;++i){
            Update(L[i].y1, L[i].y2, L[i].val, 1);
            ans += T[1].sum2*(L[i+1].x-L[i].x);
        }
        printf("%.2lf\n", ans);
    }
    return 0;
}