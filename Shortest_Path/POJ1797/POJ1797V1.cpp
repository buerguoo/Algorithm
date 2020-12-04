#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//Dijkstra+堆优化
const int MAXN = 1010;
const int INF = 0x3f3f3f3f;
int dis[MAXN];
bool vis[MAXN];

struct qnode{
    int v;
    int c;
    qnode(int _v = 0, int _c = 0):v(_v), c(_c){}
    bool operator < (const qnode &r) const{
        return c < r.c;
    }
};
struct Edge{
    int v;
    int cost;
    Edge(int _v = 0, int _c = 0):v(_v), cost(_c){}
};
vector<Edge> E[MAXN];

void Dijkstra(int n, int beg)
{
    for(int i = 0;i < n;++i){
        vis[i] = false; dis[i] = 0;
    }
    dis[beg] = INF;
    priority_queue<qnode> Q;
    Q.push(qnode(beg, 0));
    while(!Q.empty())
    {
        qnode tmp = Q.top();
        Q.pop();
        int u = tmp.v;
        if(vis[u])  continue;
        vis[u] = true;
        for(int i = 0;i < E[u].size();++i)
        {
            int v = E[u][i].v;
            int cost = E[u][i].cost;
            if(dis[v] < min(cost , dis[u])){
                dis[v] = min(cost, dis[u]);
                Q.push(qnode(v, dis[v]));
            }
        }
    }
}

int main()
{
    int T,t = 0;
    scanf("%d", &T);
    t = T;
    while(T--)
    {
        int N, M;
        int x, y, z;
        scanf("%d%d", &N, &M);
        for(int i = 0;i < N;++i)    E[i].clear();
        for(int i = 0;i < M;++i){
            scanf("%d%d%d", &x, &y, &z);
            E[x-1].push_back(Edge(y-1, z));
            E[y-1].push_back(Edge(x-1, z));
        }
        Dijkstra(N, 0);
        printf("Scenario #%d:\n%d\n\n",t-T, dis[N-1]);
    }
    return 0;
}