#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//bellman_ford求正环 逆向思维
const int MAXN = 110;
const int INF = 0x3f3f3f3f;
struct Edge{
    int u;
    int v;
    double rate;
    double com;
    Edge(int _u=0, int _v=0,double _r=0, double _c=0):
    u(_u), v(_v), rate(_r), com(_c){}
};

vector<Edge> E;
double dis[MAXN];

bool bellman_ford(int n, int beg, double V)
{
    for(int i = 0;i <= n;++i)    dis[i] = 0;
    dis[beg] = V;
    for(int j = 1;j < n;++j){
        for(int i = 0;i < E.size();++i){
            Edge tmp = E[i];
            int u = tmp.u;
            int v = tmp.v;
            double r = tmp.rate;
            double c = tmp.com;
            if(dis[v] < (dis[u]-c)*r)
                dis[v] = (dis[u]-c)*r;
        }
    }
    for(int i = 0;i < E.size();++i)
        if(dis[E[i].v] < (dis[E[i].u]-E[i].com)*E[i].rate)
            return true;
        
    return false;
}

int main()
{
    int N, M, S;
    double V;
    scanf("%d%d%d%lf", &N, &M, &S, &V);
    for(int i = 0;i < M;++i){
        int a, b;
        double Rab, Cab, Rba, Cba;

        scanf("%d%d%lf%lf%lf%lf", &a, &b, &Rab, &Cab, &Rba, &Cba);
        E.push_back(Edge(a, b, Rab, Cab));
        E.push_back(Edge(b ,a, Rba, Cba));
    }

    if(bellman_ford(N, S, V))   printf("YES\n");
    else printf("NO\n");

    return 0;
}