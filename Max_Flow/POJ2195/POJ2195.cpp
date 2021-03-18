/*
Author:buerguoo
Time:16ms
memory:172KB

Data:2021-03-18 16:30:55
*/
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
//二分图最大权匹配,寻找相等子图
const int INF = 0x3f3f3f3f;
const int MAXN = 110;
const int MAXM = 110;
int lx[MAXN], ly[MAXM], slack[MAXM], linker[MAXM];
bool visx[MAXN], visy[MAXM];
int g[MAXN][MAXM];
char mp[MAXN][MAXM];
int uN, vN;
struct Point{
    int x, y;
}H[MAXN], M[MAXN];
bool dfs(int u){
    visx[u] = true;
    for(int v = 0;v < vN;++v){
        if(visy[v] || !g[u][v]) continue;
        int tp = lx[u] + ly[v] - g[u][v];
        if(tp == 0){
            visy[v] = true;
            if(linker[v] == -1 || dfs(linker[v])){
                linker[v] = u;
                return true;
            }
        }else if(slack[v] > tp){
            slack[v] = tp;
        }
    }
    return false;
}
int KM()
{
    memset(linker, -1, sizeof(linker));
    memset(ly, 0, sizeof(ly));
    for(int i = 0;i < uN;++i){
        lx[i] = -INF;
        for(int j = 0;j < vN;++j)
            if(lx[i] < g[i][j]) lx[i] = g[i][j];
    }
    for(int u = 0;u < uN;++u){
        for(int i = 0;i < vN;++i)
            slack[i] = INF;
        while(true){
            memset(visx, false, sizeof(visx));
            memset(visy, false, sizeof(visy));
            if(dfs(u)) break;
            int d = INF;
            for(int i = 0;i < vN;++i)
                if(!visy[i] && d > slack[i])
                    d = slack[i];
            for(int i = 0;i < uN;++i)
                if(visx[i]) lx[i] -= d;
            for(int i = 0;i < vN;++i){
                if(visy[i]) ly[i] += d;
                else slack[i] -= d;
            }
        }
    }
    int res = 0;
    for(int i = 0;i < vN;++i)
        if(linker[i] != -1)
            res += g[linker[i]][i];
    
    return res;
} 
int dis(Point a, Point b){
    return abs(a.x-b.x)+abs(a.y-b.y);
}
int main()
{
    int n, m, c1, c2;
    while(~scanf("%d %d", &n, &m) && (n || m)){
        for(int i = 0;i < n;++i)
            scanf("%s", mp[i]);
        c1 = 0;
        c2 = 0;
        for(int i = 0;i < n;++i)
            for(int j = 0;j < m;++j){
                if(mp[i][j] == 'H'){
                    H[c1].x = i; H[c1++].y = j;
                }else if(mp[i][j] == 'm'){
                    M[c2].x = i; M[c2++].y = j;
                }
            }
        uN = c1, vN = c2;
        memset(g, 0, sizeof(g));
        for(int i = 0;i < c1;++i)
            for(int j = 0;j < c2;++j)
                g[i][j] = -dis(H[i], M[j]);   
        
        printf("%d\n", -KM());
    }
    return 0;
}