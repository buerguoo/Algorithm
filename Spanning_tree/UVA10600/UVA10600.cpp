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
const int MAXN = 110;
const int INF = 0x3f3f3f3f;
int cost[MAXN][MAXN], lowc[MAXN], Max[MAXN][MAXN], pre[MAXN];
bool vis[MAXN], used[MAXN][MAXN];
int prim(int n)
{
    int ans = 0;
    memset(Max, 0, sizeof(Max));
    memset(used, false, sizeof(used));
    for(int i = 0;i < n;++i){
        vis[i] = false;
        lowc[i] = cost[0][i];
        pre[i] = 0;
    }
    vis[0] = true;
    int Min, p;
    for(int i = 1;i < n;++i){
        Min = INF;
        p = -1;
        for(int j = 0;j < n;++j)
            if(!vis[j] && Min > lowc[j]){
                Min = lowc[j];
                p = j;
            }
        if(Min == INF)  return -1;
        vis[p] = true;
        ans += Min;
        used[p][pre[p]] = used[pre[p]][p] = true;
        for(int j = 0;j < n;++j){
            if(vis[j] && j != p)    Max[j][p] = Max[p][j] = max(Max[j][pre[p]], lowc[p]);
            if(!vis[j] && lowc[j] > cost[p][j]){
                lowc[j] = cost[p][j];
                pre[j] = p;
            }
        }
    }
    return ans;
}
int smst(int n, int mst)
{
    int ans = INF;
    for(int i = 0;i < n;++i)
        for(int j = i+1;j < n;++j)
            if(!used[i][j] && cost[i][j]!=INF)
                ans = min(ans, mst-Max[i][j]+cost[i][j]);
    
    return ans;
}
int main()
{
    int T;
    scanf("%d", &T);
    while(T--){
        int N, M;
        scanf("%d%d", &N, &M);
        int a, b, c;
        for(int i = 0;i < N;++i)
            for(int j = 0;j < N;++j)
                cost[i][j] = INF;
        for(int i = 0;i < M;++i){
            scanf("%d%d%d", &a, &b, &c);
            cost[a-1][b-1] = cost[b-1][a-1] = c;
        }
        int mst = prim(N);
        int smt = smst(N, mst);
        printf("%d %d\n", mst, smt);
    }
    return 0;
}