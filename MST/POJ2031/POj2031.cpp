#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
const int MAXN = 105;
const double INF = 1e5;
double cost[MAXN][MAXN];
double lowcost[MAXN];
bool vis[MAXN];
struct point
{
    double x, y, z, r;
}P[MAXN];
double prim(int n)
{
    double ans = 0;
    memset(vis, false, sizeof(vis));
    for(int i = 0;i < n;++i)    lowcost[i] = cost[0][i];
    vis[0] = true;
    for(int i = 1;i < n;++i){
        double minc = INF;
        int p = -1;
        for(int j = 0;j < n;++j)
            if(!vis[j] && minc > lowcost[j])
                {
                    minc =  lowcost[j];
                    p = j;
                }
        if(minc == INF) return -1;
        vis[p] = true;
        ans += minc;
        for(int j = 0;j < n;++j)
            if(!vis[j] && lowcost[j] > cost[p][j])
                lowcost[j] = cost[p][j];
    }

    return ans;
}
double Dis(point a, point b)
{
    double ans = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)
    +(a.z-b.z)*(a.z-b.z))-a.r-b.r;
    if(ans < 0)    ans = 0;
    return ans;
}
int main()
{
    //ifstream infile;
    //infile.open("D://input.txt", ios::in);
    int n;
    //
    while (~scanf("%d", &n) && n)
    {
        for(int i = 0;i < n;++i)    
            scanf("%lf%lf%lf%lf", &P[i].x, &P[i].y, &P[i].z, &P[i].r);
            //infile >> P[i].x >> P[i].y >> P[i].z >> P[i].r;
        for(int i = 0;i < n;++i)
            for(int j = i;j < n;++j)
                cost[i][j] = cost[j][i] = Dis(P[i], P[j]);
        
        printf("%.3lf\n", prim(n));
    }
    //infile.close();
    return 0;
}