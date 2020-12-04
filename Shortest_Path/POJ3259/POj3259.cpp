#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//SPFA算法
const int MAXN = 510;
const int INF = 0x3f3f3f3;
struct  Edge
{
    int v;
    int cost;
    Edge(int _v=0, int _c=0):v(_v), cost(_c){}
};
vector<Edge> E[MAXN];
int cnt[MAXN];
int dis[MAXN];
bool vis[MAXN];

bool Bellman_ford(int n, int beg)
{
    for(int i = 0;i <= n;++i){
        cnt[i] = 0;
        vis[i] = false;
        dis[i] = INF;
    }
    dis[beg] = 0;
    cnt[beg] = 1;
    vis[beg] = true;
    queue<int> Q;
    while(!Q.empty())   Q.pop();
    Q.push(beg);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        vis[u] = false;
        for(int i = 0;i < E[u].size();i++)
        {
            int v = E[u][i].v;
            int cost = E[u][i].cost;
            if(dis[v] > dis[u]+cost){
                dis[v] = dis[u]+cost;
                if(!vis[v]){
                    vis[v] = true;
                    Q.push(v);
                    if(++cnt[v] > n)    return true;
                }
            }
        }
    }

    return false;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--){
        int N, M, W;
        scanf("%d%d%d", &N, &M, &W);
        int x, y, z;
        for(int i = 0;i <= N;++i)    E[i].clear();
        for(int i = 0;i < M;++i){
            scanf("%d%d%d", &x, &y, &z);
            E[x].push_back(Edge(y, z));
            E[y].push_back(Edge(x, z));
        }
        for(int i = 0;i < W;++i){
            scanf("%d%d%d", &x, &y, &z);
            E[x].push_back(Edge(y, -1*z));
        }

        if(Bellman_ford(N, N))  printf("YES\n");
        else    printf("NO\n");
    }
    return 0;
}