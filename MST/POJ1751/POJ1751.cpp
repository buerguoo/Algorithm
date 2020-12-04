#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <algorithm>
using namespace std;
const int MAXN = 755;
const double INF = 1e8;
double cost[MAXN][MAXN];
double lowcost[MAXN];
bool vis[MAXN];
int pre[MAXN];
struct Point{
    int x, y;
}P[MAXN];

double Dis(Point a, Point b)
{
    return sqrt(double(a.x-b.x)*(a.x-b.x)+double(a.y-b.y)*(a.y-b.y));
}
void prim(int n)
{
    memset(vis, false, sizeof(vis));
    for(int i = 1;i <= n;++i){
        lowcost[i] = cost[1][i];
        pre[i] = 1;
    }    
    vis[1] = true;
    for(int i = 1;i < n;++i){
        double minc = INF;
        int p = -1;
        for(int j = 1;j <= n;++j)
            if(!vis[j] && minc > lowcost[j])
                {
                    minc =  lowcost[j];
                    p = j;
                }
        if(minc == INF) return ;
        vis[p] = true;
        if(lowcost[p]!=0) printf("%d %d\n", pre[p], p);
        for(int j = 1;j <= n;++j)
            if(!vis[j] && lowcost[j] > cost[p][j]){
                lowcost[j] = cost[p][j];
                pre[j] = p;
            }
                
    }
}
int main()
{
    //ifstream infile;
    //infile.open("D://input.txt", ios::in);
    int N;
    scanf("%d", &N);
    //infile >> N;
    for(int i = 0;i < N;++i)
        scanf("%d%d", &P[i].x, &P[i].y);
        //infile >> P[i].x >> P[i].y;
    for(int i = 0;i < N;++i)
        for(int j = i;j < N;++j)
            cost[j+1][i+1] = cost[i+1][j+1] = Dis(P[i], P[j]);
    int M;
    scanf("%d", &M);
    //infile >> M;
    for(int i = 0;i < M;++i){
        int u, v;
        scanf("%d%d", &u, &v);
        //infile >> u >> v;
        cost[u][v] = cost[v][u] = 0;
    }            
    prim(N);
    //infile.close();
    return 0;
}