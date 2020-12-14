/*
Author:buerguoo
Time:20ms
memory:

Data:2020-12-14 22:33:19
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
typedef long long ll;
const int MAXN = 1010;
const int MAXM = 40010;
const int INF = 0x3f3f3f3f;
int in[MAXN], id[MAXN], vis[MAXN], pre[MAXN];
struct Edge{
    int u, v, cost;
}E[MAXM];
int zhuliu(int root, int n, int m, Edge Edge[])
{
    int res = 0;
    while(1){
        for(int i = 0;i < n;++i)   in[i] = INF;
        for(int i = 0;i < m;++i)   if(E[i].u != E[i].v && E[i].cost < in[E[i].v]){
            in[E[i].v] = E[i].cost;
            pre[E[i].v] = E[i].u;
        }
        for(int i = 0;i < n;++i)    if(i != root && in[i] == INF)
            return -1;
    
        FILL(id, -1);
        FILL(vis, -1);
        in[root] = 0;
        int tn = 0;
        for(int i = 0;i < n;++i){
            res += in[i];
            int v = i;
            while(v != root && vis[v] != i && id[i] == -1){
                vis[v] = i;
                v = pre[v];
            }
            if(v != root && id[v] == -1){
                for(int u = pre[v];u != v;u = pre[u])
                    id[u] = tn;
                id[v] = tn++;
            }
        }
        if(tn == 0) break;
        for(int i = 0;i < n;++i)    if(id[i] == -1)
            id[i] = tn++;
        for(int i = 0;i < m;){
            int v = E[i].v;
            E[i].u = id[E[i].u];
            E[i].v = id[E[i].v];
            if(E[i].u != E[i].v)
                E[i++].cost -= in[v];
            else 
                swap(E[i], E[--m]);
        }
        n = tn;
        root = id[root];
    }

    return res;
}

int main()
{
    int N;
    scanf("%d", &N);
    int Case = 0;
    while(N--){
        int n, m;
        scanf("%d%d", &n, &m);
        int u, v, c;
        for(int i = 0;i < m;++i){
            scanf("%d%d%d", &u, &v, &c);
            E[i].u = u;
            E[i].v = v;
            E[i].cost = c;
        }
        int tmp = zhuliu(0, n, m, E);
        printf("Case #%d: ", ++Case);
        if(tmp == -1) printf("Possums!\n");
        else printf("%d\n", tmp);
    }
    return 0;
}