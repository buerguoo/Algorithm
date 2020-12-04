#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;
//Dijkstra算法
const int MAXN = 1010;
const int INF = 0x3f3f3f3f;
bool vis[MAXN];
int pre[MAXN];
int cost[MAXN][MAXN];
int lowcost[MAXN];

int Dijkstra(int cost[][MAXN], int lowcost[], int n, int beg)
{
    for(int i = 0;i < n;++i)
    {
        lowcost[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    lowcost[beg] = 0;
    for(int j = 0;j < n;++j)
    {
        int k = -1;
        int min = INF;
        for(int i = 0;i < n;++i)
        {
            if(!vis[i] && lowcost[i]<min)
            {   
                 min = lowcost[i];
                 k = i;
            }
        }
        if(k == -1) break;
        vis[k] = true;
        for(int i = 0;i < n;++i)
        {
            if(!vis[i] && lowcost[i]>lowcost[k]+cost[k][i]){
                lowcost[i] = lowcost[k]+cost[k][i];
                pre[i] = k;
            }
        }
        //printf("lowcost[k=%d] = %d\n",k, lowcost[k]);
    }

    return lowcost[0];
}

int main()
{
    int T, N;
    int x, y, z;
    while(scanf("%d%d", &T, &N) != EOF){
    for(int i = 0;i < MAXN;++i)    cost[i][i] = 0;
    for(int i = 0;i < MAXN;++i)
        for(int j = 0;j < MAXN;++j)
            cost[i][j] = INF;

    for(int i = 0;i < T;++i)
    {
        scanf("%d%d%d", &x, &y, &z);
        if(cost[x-1][y-1] > z)
            cost[x-1][y-1] = cost[y-1][x-1] = z;
    }

    printf("%d\n", Dijkstra(cost, lowcost, N, N-1));
    }
    return 0;
}