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
struct Edge{
    int u;
    int v;
    int cost;
    Edge(int _u=0, int _v=0, int _c=0):u(_u), v(_v), cost(_c){}
};

vector<Edge> E;
int dis[MAXN];

void bellman_ford(int n, int beg)
{
    for(int i = 0;i < n;++i)    dis[i] = 0;
    dis[beg] = INF;
    for(int i = 1;i < n;++i)
    {
        for(int j = 0;j < E.size();++j)
        {
            Edge tmp = E[j];
            int u = tmp.u;
            int v = tmp.v;
            int cost = tmp.cost;
            if(dis[v] < min(cost, dis[u]))
                dis[v] = min(dis[u], cost);
        }
    }
}

int main()
{
    int T, t = 0;
    t = T;
    scanf("%d", &T);
    while(T--)
    {
        int N, M;
        int x, y, z;
        scanf("%d%d", &N, &M);
        E.clear();
        for(int i = 0;i < M;++i){
            scanf("%d%d%d", &x, &y, &z);
            E.push_back(Edge(x-1, y-1, z));
            E.push_back(Edge(y-1, x-1, z));
        }
        bellman_ford(N, 0);
        printf("Scenario #%d:\n%d\n\n",t-T, dis[N-1]);

    }
    return 0;
}