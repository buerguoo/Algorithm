#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
using namespace std;
//Dijkstra+堆优化
const int MAXN = 210;
const double INF = 0x3f3f3f3f;
double dis[MAXN];
bool vis[MAXN];
struct qnode{
    int v;
    double c;
    qnode(int _v=0, double _c=0):v(_v), c(_c){}
    bool operator <(const qnode &r) const{
        return c > r.c;
    }
};

struct Edge{
    int v;
    double cost;
    Edge(int _v, double _c):v(_v), cost(_c){}
};

struct point
{
    int x, y;
};

point P[MAXN];
vector<Edge> E[MAXN];

double dist(point a, point b)
{
    return sqrt(double(a.x-b.x)*(a.x-b.x)+double(a.y-b.y)*(a.y-b.y));
}

void Dijkstra(int n, int beg)
{
    for(int i = 0;i < n;++i){
        dis[i] = INF;
        vis[i] = false;
    }
    priority_queue<qnode> Q;
    Q.push(qnode(beg, 0));
    while(!Q.empty())
    {
        qnode tmp = Q.top();
        Q.pop();
        int u = tmp.v;
        if(vis[u]) continue;
        vis[u] = true;
        dis[u] = tmp.c;
        for(int i = 0;i < E[u].size();++i)
        {
            int v = E[u][i].v;
            double cost = E[u][i].cost;
            //printf("dis[u=%d] = %lf\t dis[v=%d] = %lf cost=%lf\n",u,dis[u],v, dis[v], cost);
            if(dis[v] > cost)
                {
                    if(dis[u] <= cost)
                        {Q.push(qnode(v, cost)); dis[v]=cost;}
                    else
                        {Q.push(qnode(v, dis[u])); dis[v] = dis[u];} 

                    
                }
        }
    }
}

int main()
{
    int N;
    int T = 0;
    while(scanf("%d", &N) != EOF && N != 0)
    {
        for(int i = 0;i < N;++i){
            scanf("%d%d", &P[i].x, &P[i].y);
            E[i].clear();
        }
        
        for(int i = 0;i < N;++i)
            for(int j = 0;j < N;++j)    if(i != j)
                E[i].push_back(Edge(j, dist(P[i], P[j])));
        
        Dijkstra(N, 0);
        printf("Scenario #%d\n", ++T);
        printf("Frog Distance = %.3lf\n\n", dis[1]);

    }
    return 0;
}
