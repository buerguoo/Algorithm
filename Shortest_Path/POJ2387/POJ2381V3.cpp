#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
using namespace std;
//bellman_ford算法  松弛法
const int MAXN = 1010;
const int INF = 0x3f3f3f3;
int dis[MAXN];
struct Edge{
    int u;
    int v;
    int cost;
    Edge(int _u, int _v, int _c):u(_u), v(_v), cost(_c){}
};
vector<Edge> E;

bool Dijkstra(int n, int beg)
{
    for(int i = 0;i < n;++i)  dis[i] = INF;
    dis[beg] = 0;
    //最多会进行n-1次
    for(int i = 1;i < n;++i)
    {
        bool flag = false;
        for(int j = 0;j < E.size();j++)
        {
            Edge tmp = E[j];
            int u = tmp.u;
            int v = tmp.v;
            int cost = tmp.cost;
            if(dis[v] > dis[u]+cost)
            {
                dis[v] = dis[u] + cost;
                flag = true;
            } 
        }
        if(!flag) return true;
    }
    for(int j = 0;j < E.size();++j)
        if(dis[E[j].v] > dis[E[j].u]+E[j].cost)
            return false;

    return true;    
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
            E.push_back(Edge(x-1, y-1, z));
            E.push_back(Edge(y-1, x-1, z));
        }

        if(Dijkstra(N, N-1))
            printf("%d\n", dis[0]);
    }
}