/*
Author:buerguoo
Time:32ms
memory:504Kb

Data:2020-11-28 22:25:29
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
typedef long long ll;
const int MAXN = 2e4+5;
const int INF = 0x3f3f3f3f;
struct node{
    int l, r, sum, num, lr, rr, cover;
    bool bl, br;
}tr[MAXN<<2];
struct Line{
    int x, y1, y2, val;
    Line(int _x=0, int _y1=0, int _y2=0, int _val=0):x(_x), y1(_y1), y2(_y2), val(_val){}
    bool operator < (Line r)const{
        if(x == r.x)    return val>r.val;
        return x<r.x;
    }
}Lines[MAXN];
int y[MAXN];
void Pushup(int rt)
{

    if(tr[rt].cover){
        tr[rt].sum = tr[rt].rr-tr[rt].lr;
        tr[rt].num = 1;
        tr[rt].bl = tr[rt].br = true;
    }
    else if(tr[rt].l+1==tr[rt].r){
        tr[rt].num = tr[rt].sum = 0;
        tr[rt].bl = tr[rt].br = false;
    }
    else{
        tr[rt].num = tr[rt<<1].num + tr[rt<<1|1].num;
        tr[rt].sum = tr[rt<<1].sum + tr[rt<<1|1].sum;
        tr[rt].bl = tr[rt<<1].bl, tr[rt].br = tr[rt<<1|1].br;
        if(tr[rt<<1|1].bl && tr[rt<<1].br)  tr[rt].num--;
    }
    //printf("cover= %d  %d\n",tr[rt].cover ,tr[rt].num);
}
void Build(int l, int r, int rt)
{
    tr[rt].num =  0;
    tr[rt].l = l, tr[rt].r = r;
    tr[rt].bl = tr[rt].br = false;
    tr[rt].lr = y[l], tr[rt].rr = y[r];
    if(l+1 >= r)    return ;
    int m = (l+r)>>1;
    Build(lson);
    Build(rson);
}
void Update(int L, int R, int C, int rt)
{
    //printf("%d %d %d %d\n", L, R, tr[rt].lr, tr[rt].rr);
    //printf("%d\n", rt);
    if(L <= tr[rt].lr && R >= tr[rt].rr){
        tr[rt].cover += C;
        Pushup(rt);
        return ;
    }
    if(L < tr[rt<<1].rr)  Update(L, R, C, rt<<1);
    if(R > tr[rt<<1|1].lr)   Update(L, R, C, rt<<1|1);
    Pushup(rt);
}
int main()
{
    int n;
    scanf("%d", &n);
    int x1, x2, y1, y2;
    for(int i = 1;i <= n;++i){
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        y[i] = y1, y[i+n] = y2;
        Lines[i] = Line(x1, y1, y2, 1);
        Lines[i+n] = Line(x2, y1, y2, -1);
    }
    sort(y+1, y+1+n*2);
    sort(Lines+1, Lines+1+n*2);
    int m = unique(y+1, y+1+2*n)-y-1;
    Build(1, m, 1);
    int ans = 0, tmp = 0, le=0;
    for(int i = 1;i <= 2*n;++i){
        Update(Lines[i].y1, Lines[i].y2, Lines[i].val, 1);
        ans += 2*le*(Lines[i].x-Lines[i-1].x);
        ans += abs(tr[1].sum-tmp);
        tmp = tr[1].sum;
        le = tr[1].num;
    }
    printf("%d\n", ans);
   return 0;
}