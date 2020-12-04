#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <algorithm>
using namespace std;
const int MAXN = 505;
const double INF = 1e8;
double cost[MAXN][MAXN];
double lowcost[MAXN];
bool vis[MAXN];
struct Point
{
    int x, y;
}P[MAXN];
double Dis(Point a, Point b)
{
    return sqrt(double(a.x-b.x)*(a.x-b.x)+double(a.y-b.y)*(a.y-b.y));
}
bool cmp(double a, double b)
{
    return a>b;
}
double prim(int n, int q)
{
    memset(vis, false, sizeof(vis));
    for(int i = 0;i < n;++i)    lowcost[i] = cost[0][i];
    vis[0] = true;
    for(int i = 1;i < n;++i){
        int minc = INF;
        int p = -1;
        for(int j = 0;j < n;++j)
            if(!vis[j] && minc > lowcost[j]){
                minc = lowcost[j];
                p = j;
            }
        if(minc == INF) return -1;
        vis[p] = true;
        for(int j = 0;j < n;++j)
            if(!vis[j] && lowcost[j] > cost[p][j])
                lowcost[j] = cost[p][j];
    }
    sort(lowcost, lowcost+n, cmp);
    return lowcost[q];
}
int main()
{
    int T;
    scanf("%d", &T);
    while(T--){
        int n, q;
        scanf("%d%d", &q, &n);
        for(int i = 0;i < n;++i)
            scanf("%d%d", &P[i].x, &P[i].y);
        for(int i = 0;i < n;++i)
            for(int j = i;j < n;++j)
                cost[i][j] = cost[j][i] = Dis(P[i], P[j]);
        printf("%.2lf\n", prim(n, q-1));
    }
    return 0;
}