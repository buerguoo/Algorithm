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
struct qnode{
    int v;
    int c;
    qnode(int _v = 0, int _c = 0):v(_v), c(_c){}
    bool operator < (const qnode &r) const{
        return c > r.c;
    }
};
struct Edge{
    int v;
    int cost;
    Edge(int _v = 0, int _c = 0):v(_v), cost(_c){}
};
vector<Edge> E[MAXN];

int Dijkstra(int n,int beg)
{
    for(int i = 0;i <= n;++i){
        vis[i]= false;
        dis[i] = INF;
    }
    dis[beg] = 0;
    priority_queue<qnode> Q;
    Q.push(qnode(beg, 0));
    while (!Q.empty())
    {
        qnode tmp = Q.top();
        Q.pop();
        int u = tmp.v;
        if(vis[u])  continue;
        vis[u] = true;
        for(int i = 0;i < E[u].size();i++){
            int v = E[u][i].v;
            int cost = E[u][i].cost;
            if(!vis[v] && dis[v] > dis[u]+cost){
                dis[v] = dis[u]+cost;
                Q.push(qnode(v, dis[v]));
            }
        }
    }
    int MAX = 0;
    for(int i = 1;i <= n;i++){
        //printf("%d\n", dis[i]);
        if(dis[i] > MAX)
            MAX = dis[i];
            }
    
    return MAX;
}

int main()
{
    int N;
    while(scanf("%d", &N)!=EOF){
    for(int i = 1;i <= N;i++)   E[i].clear();

    for(int i = 2;i <= N;++i)
        for(int j = 1;j < i;++j){
            char z[10];
            int c = INF;
            scanf("%s", z);
            if(z[0] >= '0' && z[0] <= '9')
                c = atoi(z);
            E[i].push_back(Edge(j, c));
            E[j].push_back(Edge(i, c));
        }
    printf("%d\n", Dijkstra(N, 1));
    }
    return 0;
}