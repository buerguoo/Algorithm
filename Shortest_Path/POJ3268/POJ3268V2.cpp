#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//Bellman_ford算法
const int MAXN = 1010;
const int INF = 0x3f3f3f3f;
int dis[MAXN], _dis[MAXN];

struct  Edge
{
    int u;
    int v;
    int cost;
    Edge(int _u=0, int _v=0, int _c=0):u(_u), v(_v), cost(_c){}
};

vector<Edge> E;

int bellman_ford(int n, int beg)
{
    for(int i = 0;i < n;++i) dis[i] = _dis[i] = INF;
    dis[beg] = _dis[beg] = 0;
    for(int j = 1;j < n;++j)
    {
        for(int i = 0;i < E.size();++i){
            int u = E[i].u;
            int v = E[i].v;
            int cost = E[i].cost;
            if(dis[v] > dis[u]+cost)
                dis[v] = dis[u]+cost;
            if(_dis[u] > _dis[v]+cost)
                _dis[u] = _dis[v]+cost;
        }
    }
    int MAX = 0;
    for(int i = 0;i < n;++i) if(MAX < dis[i]+_dis[i])
        MAX = dis[i] + _dis[i];
    
    return MAX;
}

int main()
{
    int N, M, X;
    int x, y, z;
    scanf("%d%d%d", &N, &M, &X);
    for(int i = 0;i < M;++i){
        scanf("%d%d%d", &x, &y, &z);
        E.push_back(Edge(x-1, y-1, z));
    }
    
    printf("%d\n", bellman_ford(N, X-1));
    return 0;
}