/*
Author:buerguoo
Time:
memory:

Data:
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
const int MAXN = 1000;
const int MAXM = 1e6;
const int INF = 0x3f3f3f3f;
int in[MAXN], pre[MAXN], id[MAXN], vis[MAXN];
struct Edge{
    int u, v, cost;
}E[MAXM];
struct Point{
    int x, y, z;
}P[MAXN];
int zhuliu(int root, int n, int m, Edge E[])
{
    int res = 0;
    while(1){
        for(int i = 0;i < n;++i)    in[i] = INF;
        for(int i = 0;i < m;++i)    if(E[i].u != E[i].v && E[i].cost < in[E[i].v]){
            in[E[i].v] = E[i].cost;
            pre[E[i].v] = E[i].u;
        }
        for(int i = 0;i < n;++i) if(i != root && in[i] == INF)
            return -1;
        
        int tn = 0;
        in[root] = 0;
        memset(id, -1, sizeof(id));
        memset(vis, -1, sizeof(vis));
        for(int i = 0;i < n;++i){
            res += in[i];
            int v = i;
            while(v != root && vis[v] != i && id[v] == -1){
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
        for(int i = 0;i < n;++i)
            if(id[i] == -1)
                id[i] = tn++;
        for(int i = 0;i < m;){
            int v = E[i].v;
            E[i].v = id[E[i].v];
            E[i].u = id[E[i].u];
            if(E[i].v != E[i].u)
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
    int n, X, Y, Z;
    while(~scanf("%d%d%d%d", &n, &X, &Y, &Z)){
        if(!n && !X && !Y && !Z)
            break;
        int m = 0;
        for(int i = 0;i < n;i++){
            scanf("%d%d%d", &P[i+1].x, &P[i+1].y, &P[i+1].z);
            E[m].u = 0;
            E[m].v = i+1;
            E[m++].cost = X*P[i+1].z;
        }
        int k = 0, t = 0;
        for(int i = 0;i < n;++i){
            scanf("%d", &k);
            while(k--){
                scanf("%d", &t);
                E[m].u = i+1;
                E[m].v = t;
                int mhd = abs(P[i+1].x-P[t].x) + abs(P[i+1].y-P[t].y) + abs(P[i+1].z-P[t].z);
                E[m].cost = Y*mhd;
                if(P[i+1].z > P[t].z) E[m].cost += Z;
                m++;
            }
        }
        //for(int i = 0;i < m;++i)
            //printf("%d %d %d\n", E[i].u, E[i].v, E[i].cost);
        int res = zhuliu(0, n+1, m, E);
        if(res == -1) printf("poor XiaoA\n");
        else printf("%d\n", res);
    }

    return 0;
}