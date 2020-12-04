#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
using namespace std;
//Dijkstra算法+堆优化
const int MAXN = 1010;
const int INF = 0x3f3f3f3;

struct qnode{
    int v;
    int c;
    qnode(int _v=0, int _c=0):v(_v),c(_c){}
    bool operator < (const qnode &r) const{
        return c>r.c;
    }
};

struct Edge{
    int v;
    int cost;
    Edge(int _v=0, int _c=0):v(_v), cost(_c){}
};
vector<Edge>E[MAXN];
bool vis[MAXN];
int dis[MAXN];

int Dijkstra(int n, int beg)
{
    memset(vis, 0, sizeof(vis));
    for(int i = 0;i < n;++i) dis[i] = INF;
    priority_queue<qnode> Q;
    Q.push(qnode(beg, 0));
    while (!Q.empty())
    {
        qnode tmp = Q.top();
        Q.pop();
        int u = tmp.v;
        if(vis[u])  continue;
        vis[u] = true;
        dis[u] = tmp.c;
        for(int i = 0;i < E[u].size();++i)
        {
            Edge temp = E[u][i];
            int v = temp.v, c = temp.cost;
            if(dis[v] > dis[u]+c)
                Q.push(qnode(v, dis[u]+c));
        }
    }
    
    return dis[0];
}

int main()
{
    int T,N;
    int x, y, z;
    while(scanf("%d%d", &T, &N) != EOF)
    {
        for(int i = 0;i < T;++i)
        {
            scanf("%d%d%d", &x, &y, &z);
            E[x-1].push_back(Edge(y-1, z));
            E[y-1].push_back(Edge(x-1, z)); 
        }
        printf("%d\n", Dijkstra(N, N-1));
    } 

    return 0;
}