/*
Author:buerguoo
Time:31ms
memory:1836KB

Data:2020-11-19 17:39:22
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
const int MAXN = 105;
const double INF = 0x3f3f3f3f;
double cost[MAXN][MAXN];
double lowc[MAXN];
bool vis[MAXN];
struct Point{
    int x, y;
}P[MAXN];
double Dis(Point a, Point b)
{
    double dis = sqrt(double(a.x-b.x)*(a.x-b.x)+double(a.y-b.y)*(a.y-b.y));
    if((dis > 0 && dis < 10) || dis > 1000)
        dis = INF;
    
    return dis;
}
double prim(int n)
{
    double ans = 0;
    memset(vis, false, sizeof(vis));
    for(int i = 0;i < n;++i)    lowc[i] = cost[0][i];
    vis[0] = true;
    for(int i = 1;i < n;++i){
        double minc = INF;
        int p = -1;
        for(int j = 0;j < n;++j)
            if(!vis[j] && lowc[j] < minc){
                minc = lowc[j];
                p = j;
            }
        if(minc == INF) return -1;
        vis[p] = true;
        ans += minc;
        for(int j = 0;j < n;++j)
            if(!vis[j] && lowc[j] > cost[p][j])
                lowc[j] = cost[p][j];
    }

    return ans;
}
int main()
{
    int T;
    scanf("%d", &T);
    while(T--){
        int n;
        scanf("%d", &n);
        for(int i = 0;i < n;++i)
            scanf("%d%d", &P[i].x, &P[i].y);
        for(int i = 0;i < n;++i)
            for(int j = i;j < n;++j)
                cost[i][j] = cost[j][i] = Dis(P[i], P[j]);

        double ans = prim(n);
        if(ans == -1) printf("oh!\n");
        else printf("%.1lf\n", ans*100);
    }
    return 0;
}