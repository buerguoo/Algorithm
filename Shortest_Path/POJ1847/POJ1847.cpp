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
struct  qnode
{
    int u;
    int cost;
    qnode(int _u=0, int _c=0):u(_u), cost(_c){}
    bool operator <(const qnode &r) const{
        return cost > r.cost;
    }
};

struct  Edge
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
        vis[i] = false;
        dis[i] = INF;
    }
    dis[start] = 0;
    priority_queue<qnode> Q;
    Q.push(qnode(start, 0));
    while (!Q.empty())
    {
        int u = Q.top().u;
        Q.pop();
        //printf("u = %d cost = %d\n", u, c);
        if(vis[u])  continue;
        vis[u] = true;
        for(int i = 0;i < E[u].size();++i){
            int v = E[u][i].v;
            int cost = E[u][i].cost;
            if(!vis[v] && dis[u]+cost < dis[v]){
                dis[v] = dis[u] + cost;
                Q.push(qnode(v, dis[v]));
            }
        }
    }
    
    return 0;
}

int main()
{
    int N, A, B;
    while(scanf("%d%d%d", &N, &A, &B) != EOF){
        for(int i = 1;i <= N;++i)   E[i].clear();
        for(int u = 1;u <= N;++u){
            int n;
            scanf("%d", &n);
            for(int j = 0;j < n;++j){
                int v;
                scanf("%d", &v);
                if(j==0)  addEdge(u, v, 0);
                else addEdge(u, v, 1);
            }
        }
        Dijkstra(A, N);
        printf("%d\n", dis[B]==INF?-1:dis[B]);
    }
    return 0;
}