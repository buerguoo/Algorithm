#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
using namespace std;
//bellman_ford算法
const int MAXN = 210;
const double INF = 0x3f3f3f3f; 
struct Edge{
    int u;
    int v;
    double cost;
    Edge(int _u, int _v,double _c):u(_u), v(_v), cost(_c){}
};
struct point
{
    int x, y;
    point(int _x, int _y):x(_x), y(_y){}
};
double dis[MAXN];
vector<Edge> E;
vector<point> P;
double dist(point a, point b)
{
    return sqrt(double(a.x-b.x)*(a.x-b.x)+double(a.y-b.y)*(a.y-b.y));
}

void Bellman_ford(int n, int beg)
{
    for(int i = 0;i < n;++i)    dis[i] = INF;
    dis[beg] = 0;
    for(int i = 1;i < n;++i)
    {
        for(int j = 0;j < E.size();++j)
        {
            int u = E[j].u;
            int v = E[j].v;
            double cost = E[j].cost;
            if(cost < dis[v]){
                if(cost >= dis[u])
                    dis[v] = cost;
                else if(dis[v] > dis[u])
                    dis[v] = dis[u];
            }
        }
    }
}

int main()
{
    int N;
    int T = 0;
    while(scanf("%d" ,&N) && N != 0)
    {
        int x, y;
        P.clear();
        E.clear();
        for(int i = 0;i < N;++i)
        {
            scanf("%d%d", &x, &y);
            P.push_back(point(x, y));
        }
        for(int i = 0;i < P.size();++i)
            for(int j = i+1;j < P.size();++j)
                {
                    E.push_back(Edge(i , j, dist(P[i], P[j])));
                    E.push_back(Edge(j , i, dist(P[i], P[j])));
                }    

        Bellman_ford(N, 0);        
        printf("Scenario #%d\n", ++T);
        printf("Frog Distance = %.3lf\n\n", dis[1]);

    } 
    return 0;
}