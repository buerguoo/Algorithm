#include <iostream> 
#include <cstring> 
#include <vector> 
#include <cmath> 
#include <cstdio> 
#include <queue> 
#include <fstream> 
using namespace std; 
const int MAXN = 105; 
const int INF = 0x3f3f3f3f; 
int cost[MAXN][MAXN]; 
int lowcost[MAXN]; 
bool vis[MAXN]; 
int prim(int n) 
{ 
    int ans = 0; 
    memset(vis, false, sizeof(vis)); 
    for(int i = 0;i < n;++i)    lowcost[i] = cost[0][i]; 
    vis[0] = true; 
    for(int i = 1;i < n;++i) 
    { 
        int minc = INF; 
        int p = -1; 
        for(int j = 0;j < n;++j) 
            if(!vis[j] && lowcost[j] < minc){ 
                minc = lowcost[j]; 
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
int main() 
{ 
    int n; 
    while (~scanf("%d", &n)) 
    { 
        int d; 
        for(int i = 0;i < n;++i) 
            for(int j = 0;j < n;++j){ 
                scanf("%d", &d); 
                cost[i][j] = cost[j][i] = d; 
            } 
        printf("%d\n", prim(n)); 
    } 
     
    return 0; 
}