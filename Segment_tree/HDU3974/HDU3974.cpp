/*
Author:buerguoo
Time:202ms
memory:2696Kb

Data:2020-11-26 17:33:37
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
const int MAXN = 50010;
const int INF = 0x3f3f3f3f;
int sum[MAXN<<2], head[MAXN];
bool vis[MAXN];
int tol;
struct Edge{
    int v, next;
    Edge(){}
    Edge(int _v, int _n):v(_v), next(_n){}
}E[MAXN];
void Init()
{
    FILL(vis, false);
    FILL(head, -1);
    tol = 0;
}
void addEdge(int u, int v)
{
    E[tol] = Edge(v, head[u]);
    head[u] = tol++;
}
int st[MAXN], ed[MAXN];
int num;
void dfs(int u)
{
    st[u] = ++num;
    for(int i = head[u];~i;i=E[i].next)
        dfs(E[i].v);
    ed[u] = num;
}
void build(int l, int r, int rt)
{
    sum[rt] = -1;
    if(l == r)  return ;
    int m = (l+r)>>1;
    build(lson);
    build(rson);
}
void PushDown(int rt)
{
    if(sum[rt]!=-1){
        sum[rt<<1] = sum[rt<<1|1] = sum[rt];
        sum[rt] = -1;
    }
}
void Update(int L, int R, int C, int l, int r, int rt)
{
    if(L <= l && R >= r){
        sum[rt] = C;
        return ;
    }
    PushDown(rt);
    int m = (l+r)>>1;
    if(L <= m)  Update(L, R, C, lson);
    if(R > m)   Update(L, R, C, rson);
}
int Query(int L, int l, int r, int rt)
{
    if(l == r)
        return sum[rt];
    PushDown(rt);
    int m = (l+r)>>1;
    if(L <= m)  return Query(L, lson);
    else   return Query(L, rson);
}
int main()
{
    int T, t=0;
    scanf("%d", &T);
    while(t++ < T){
        int n;
        scanf("%d", &n);
        Init();
        int a, b;
        for(int i = 1;i < n;++i){
            scanf("%d%d", &a, &b);
            vis[a] = true;
            addEdge(b, a);
        }
        num = 0;
        for(int i = 1;i <= n;++i)   if(!vis[i]){
            dfs(i);
            break;
        }
        build(1, num, 1);
        int M;
        char s[2];
        scanf("%d", &M);
        printf("Case #%d:\n", t);
        for(int i = 0;i < M;++i){
            scanf("%s", s);
            if(s[0] == 'C'){
                scanf("%d", &a);
                printf("%d\n", Query(st[a], 1, num, 1));
            }
            else{
                scanf("%d%d", &a, &b);
                Update(st[a], ed[a], b, 1, num, 1);
            }
        }
    }
    return 0;
}