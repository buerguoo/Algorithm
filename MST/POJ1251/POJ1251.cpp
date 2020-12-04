#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
const int MAXN = 30;
const int INF = 0x3f3f3f3f;
int cost[MAXN][MAXN];
int lowcost[MAXN];
bool vis[MAXN];
int prim(int n)
{
    int ans = 0;
    memset(vis, false, sizeof(vis));
    for(int i = 0;i < n;++i)  lowcost[i] = cost[0][i];
    vis[0] = true;
    for(int i = 1;i < n;++i){
        int minc=INF, p=-1;
        for(int j = 0;j < n;++j){
            if(!vis[j]&&minc>lowcost[j]){
                minc = lowcost[j];
                p = j;
            }
        }
        if(minc == INF) return -1;
        ans += minc;
        vis[p] = true;
        for(int j = 0;j < n;++j){
            if(!vis[j]&&cost[p][j]<lowcost[j])
                lowcost[j] = cost[p][j];
        }
    }
    
    return ans;
}
int main() {
	int n;
	while(~scanf("%d", &n) && n!=0)
	{
	    char c[10];
	    int a, b, d, k;
	    for(int i = 0;i < n;++i)
	        for(int j = 0;j < n;++j)
	            cost[i][j] = INF;
	    for(int i = 1;i < n;++i){
	        scanf("%s%d", c, &k);
	        int a = c[0] - 'A';
	        for(int j = 0;j < k;++j){
	            scanf("%s%d", c, &d);
	            int b = c[0] - 'A';
	            cost[a][b] = d;
                cost[b][a] = d;
	        }

	    }
	    printf("%d\n", prim(n));
	}
	return 0;
}