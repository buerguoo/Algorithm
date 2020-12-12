/*
Author:buerguoo
Time:94ms
memory:216KB

Data:2020-12-12 23:19:58
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
const int MAXN = 105;
const int MAXM = 1e4+10;
const double INF = 0x3f3f3f3f;
double in[MAXN];
int pre[MAXN], id[MAXN], vis[MAXN];
struct Edge{
    int u, v;
    double cost;
}E[MAXM];
struct Point{
    int x, y;
}P[MAXN];
double zhuliu(int n, int m, int root, Edge E[])
{
    double res = 0;
    while(1){
        for(int i = 0;i < n;++i)
            in[i] = INF;
        for(int i = 0;i < m;++i)
            if(E[i].u != E[i].v && E[i].cost < in[E[i].v]){
                pre[E[i].v] = E[i].u;
                in[E[i].v] = E[i].cost;
            }
        for(int i = 0;i < n;++i)
            if(in[i] == INF && i != root)    return -1;
        int tn = 0;
        in[root] = 0;
        memset(id, -1, sizeof(id));
        memset(vis, -1, sizeof(vis));
        for(int i = 0;i < n;++i){
            res += in[i];
            int v = i;
            while(v != root && id[v] == -1 && vis[v] != i){
                vis[v] = i;
                v = pre[v];
            }
            if(v != root && id[v] == -1){
                for(int u=pre[v]; u != v;u = pre[u])
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
            E[i].u = id[E[i].u];
            E[i].v = id[E[i].v];
            if(E[i].u != E[i].v)
                E[i++].cost -= in[v];
            else
                swap(E[i],  E[--m]);
            }
            n = tn;
            root = id[root];
        }

        return res;    
}

double Dis(Point a, Point b)
{
    return sqrt(double(a.x-b.x)*(a.x-b.x)+double(a.y-b.y)*(a.y-b.y));
}

int main()
{
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        for(int i = 0;i < n;++i)
            scanf("%d%d", &P[i].x, &P[i].y);
        int a, b, p = 0;
        for(int i = 0;i < m;++i){
            scanf("%d%d", &a, &b);
            E[p].u = a-1;
            E[p].v = b-1;
            E[p++].cost = Dis(P[a-1], P[b-1]);
        }
        double res = zhuliu(n, m, 0, E);
        if(res == -1)   printf("poor snoopy\n");
        else printf("%.2lf\n", res);
    }
    return 0;
}