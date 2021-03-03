/*
Author:buerguoo
Time:546ms
memory:46956kB

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
const int MAXN = 3030;
const int INF = 0x3f3f3f3f;
int dx[MAXN], dy[MAXN], Mx[MAXN], My[MAXN];
bool used[MAXN];
int dist, uN, si[MAXN];
struct Point{
    int x, y;
}guests[MAXN], umbrellas[MAXN];
vector<int> G[MAXN];
bool SearchP()
{
    queue<int> Q;
    dist = INF;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    for(int u = 0;u < uN;++u){
        if(Mx[u] == -1){
            Q.push(u);
            dx[u] = 0;
        }
    }
    int u, v;
    while(!Q.empty()){
        u = Q.front();
        Q.pop();
        if(dx[u] > dist) break;
        int sz = G[u].size();
        for(int i = 0;i < sz;++i){
            v = G[u][i];
            if(dy[v] == -1){
                dy[v] = dx[u] + 1;
                if(My[v] == -1) dist = dy[v];
                else{
                    dx[My[v]] = dy[v] + 1;
                    Q.push(My[v]);
                }
            }
        }
    }
    return dist != INF;
}
bool dfs(int u){
    int sz = G[u].size();
    int v;
    for(int i = 0;i < sz;++i){
        v = G[u][i];
        if(!used[v] && dx[u]+1 == dy[v]){
            used[v] = true;
            if(My[v] != -1 && dist == dy[v]) continue;
            if(My[v] == -1 || dfs(My[v])){
                My[v] = u;
                Mx[u] = v;
                return true;
            }
        }
    }
    return false;
}
int MaxMatch()
{
    int res = 0;
    memset(Mx, -1, sizeof(Mx));
    memset(My, -1, sizeof(My));
    while(SearchP()){
        memset(used, false, sizeof(used));
        for(int u = 0;u < uN;++u){
            if(Mx[u] == -1 && dfs(u))
                res++;
        }
    }
    return res;
}
double Manhattan(Point a, Point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int main()
{
    int kase = 0, Case, t, vN;
    scanf("%d", &Case);
    while(kase++ < Case){
        scanf("%d", &t);
        scanf("%d", &uN);
        for(int i = 0;i < uN;++i)
            G[i].clear();
        for(int i = 0;i < uN;++i)
            scanf("%d %d %d", &guests[i].x, &guests[i].y, &si[i]);
        scanf("%d", &vN);
        for(int i = 0;i < vN;++i)
            scanf("%d %d", &umbrellas[i].x, &umbrellas[i].y);
        for(int i = 0;i < uN;++i)
            for(int j = 0;j < vN;++j)
                if(Manhattan(guests[i], umbrellas[j]) <= si[i]*t)
                    G[i].push_back(j);
        printf("Scenario #%d:\n%d\n\n", kase, MaxMatch());
    }
    return 0;
}
