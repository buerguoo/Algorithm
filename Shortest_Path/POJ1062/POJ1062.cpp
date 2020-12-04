#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//Dijkstra+堆优化
const int MAXN = 110;
const int INF = 0x3f3f3f3f;
int dis[MAXN];
bool vis[MAXN];
int level[MAXN];
int Pr[MAXN];
int cp[2];
int M, N;
struct qnode{
    int u;
    int cost;
    qnode(int _u=0, int _c=0):u(_u), cost(_c){}
    bool operator < (const qnode &r) const{
        return cost > r.cost;
    }
};

struct Edge
{
    int v;
    int cost;
    Edge(int _v=0, int _c=0):v(_v), cost(_c){}
};
vector<Edge> E[MAXN];

void addEdge(int u, int v, int c)
{
    E[u].push_back(Edge(v, c));
}

int Dijkstra(int start, int n)
{
    for(int i = 1;i <= n;++i){
        dis[i] = INF;
        vis[i] = false;
    }
    dis[start] = 0;
    priority_queue<qnode> Q;
    Q.push(qnode(start, 0));
    while (!Q.empty())
    {
        int u = Q.top().u;
        Q.pop();
        vis[u] = true;
        for(int i = 0;i < E[u].size();i++){
            int v = E[u][i].v;
            int cost = E[u][i].cost;
            if(!vis[v] && level[v]<=cp[1] && level[v]>=cp[0]
                && dis[v]>dis[u]+cost){
                    dis[v] = dis[u]+cost;
                    Q.push(qnode(v, dis[v]));  
                }
        }
    }
    int MIN = INF;
    for(int i = 1;i <= n;++i)
        if(dis[i]+Pr[i] < MIN)
            MIN = dis[i]+Pr[i];
    
    return MIN;
}

int main()
{  
    scanf("%d%d", &M, &N);
    memset(level, 0, sizeof(level));
    memset(Pr, 0, sizeof(Pr));
    for(int i = 1;i <= N;++i){
        int P, L, X;
        scanf("%d%d%d", &P, &L, &X);
        level[i] = L;
        Pr[i] = P;
        for(int j = 0;j < X;++j){
            int T, V;
            scanf("%d%d", &T, &V);
            addEdge(i, T, V);
        }
    }
    int mincost = INF;
    for(int i = 0;i <= M;++i){
        cp[0] = level[1] - M + i;
        cp[1] = level[1] + i;

        mincost = min(mincost, Dijkstra(1, N));
    }
    printf("%d\n", mincost);
    return 0;
}