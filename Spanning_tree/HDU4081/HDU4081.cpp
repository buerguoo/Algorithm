/*
Author:buerguoo
Time:109ms
memory:18388KB

Data:2020-11-30 22:21:02
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
const int MAXN = 1005;
const double INF = 0x3f3f3f3f;
double cost[MAXN][MAXN], Max[MAXN][MAXN], lowc[MAXN];
int pre[MAXN], Pe[MAXN];
bool vis[MAXN], used[MAXN][MAXN];
struct Point{
    int x, y;
}P[MAXN];
double Dis(Point a, Point b)
{
    return sqrt(double(a.x-b.x)*(a.x-b.x)+double(a.y-b.y)*(a.y-b.y));
}
double Prim(int n)
{
    memset(used, false, sizeof(used));
    memset(Max, 0, sizeof(Max));
    for(int i = 0;i < n;++i){
        vis[i] = false;
        lowc[i] = cost[0][i];
        pre[i] = 0;
    }
    vis[0] = true;
    double ans = 0;
    double Min;
    int  p;
    for(int i = 1;i < n;++i){
        Min = INF;
        p = -1;
        for(int j = 0;j < n;++j)    if(!vis[j] && lowc[j] < Min){
            Min = lowc[j];
            p = j;
        }
        if(Min == INF)   return -1;
        vis[p] = true;
        ans += Min;
        used[p][pre[p]] = used[pre[p]][p] = true;
        for(int j = 0;j < n;++j){
            if(vis[j] && j!=p)  Max[p][j] = Max[j][p] = max(Max[j][pre[p]], lowc[p]);
            if(!vis[j] && lowc[j]>cost[p][j]){
                lowc[j] = cost[p][j];
                pre[j] = p;
            }
        }
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
        for(int i = 0;i < n;++i)    scanf("%d%d%d", &P[i].x, &P[i].y, &Pe[i]);
        for(int i = 0;i < n;++i)
            for(int j = i;j < n;++j)
                cost[i][j] = cost[j][i] = Dis(P[i], P[j]);
        double mst = Prim(n);
        double ans = 0;
        for(int i = 0;i < n;++i)
            for(int j = i+1;j < n;++j){
                if(used[i][j])  ans = max(ans, (Pe[i]+Pe[j])/(mst-cost[i][j]));
                else ans = max(ans, (Pe[i]+Pe[j])/(mst-Max[i][j]));
            }
        
        printf("%.2lf\n", ans);
    }
    return 0;
}
