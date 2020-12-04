#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//差分约束
const int MAXN = 1010;
const int INF = 0x3f3f3f3f;
int dis[MAXN];
bool vis[MAXN];
int cnt[MAXN];
struct Edge
{
    int v;
    int c;
    Edge(int _v=0, int _c=0):v(_v), c(_c){}
};
vector<Edge>E[MAXN];

void addEdge(int u, int v, int c)
{
    E[u].push_back(Edge(v, c));
}

bool SPFA(int start, int n)
{
    for(int i = 1;i <= n;++i){
        vis[i] = false;
        dis[i] = INF;
        cnt[i] = 0;
    }
    queue<int> Q;
    Q.push(start);
    dis[start] = 0;
    vis[start] = true;
    cnt[start] = 1;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        vis[u] = false;
        for(int i = 0;i < E[u].size();++i){
            int v = E[u][i].v;
            int cost = E[u][i].c;
            if(dis[u]+cost < dis[v]){
                dis[v] = dis[u]+cost;
                if(!vis[v]){
                    vis[v] = true;
                    Q.push(v);
                    if(++cnt[v] > n) return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    int N, ML, MD;
    scanf("%d%d%d", &N, &ML, &MD);
    for(int i = 1;i <= N;++i)   E[i].clear();
    int a, b, c;
    for(int i = 0;i < ML;++i){
        scanf("%d%d%d", &a, &b, &c);
        addEdge(a, b, c);
    }
    for(int i = 0;i < MD;++i){
        scanf("%d%d%d", &a, &b, &c);
        addEdge(b, a, -c);
    }
    if(SPFA(1, N)){
        if(dis[N] == INF)   printf("-2\n");
        else    printf("%d\n", dis[N]);
    }
    else    printf("-1");
    return 0;
} 
