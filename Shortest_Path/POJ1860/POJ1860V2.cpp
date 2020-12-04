#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//SPFA算法同V1
const int MAXN = 110;
const int INF = 0x3f3f3f3f;
bool vis[MAXN];
double dis[MAXN];   //标记划分
int cnt[MAXN];  //每个点的入队次数
struct Edge{
    int v;
    double rate;
    double com;
    Edge(int _v=0,double _r=0, double _c=0):
     v(_v), rate(_r), com(_c){}
};
vector<Edge> E[MAXN];

bool SPFA(int n, int beg, double V)
{
    for(int i = 0;i < n;++i){
        vis[i] = false;
        cnt[i] = 0;
        dis[i] = 0;
    }
    dis[beg] = V;
    cnt[beg] = 1;
    vis[beg] = true;
    queue<int> Q;
    while(!Q.empty())   Q.pop();
    Q.push(beg);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        vis[u] = false;
        for(int i = 0;i < E[u].size();++i){
            Edge e = E[u][i];
            int v = e.v;
            double r = e.rate, c = e.com;
            if(dis[v] < (dis[u]-c)*r){
                dis[v] = (dis[u]-c)*r;
                if(!vis[v]){
                    vis[v] = true;
                    Q.push(v);
                    if(++cnt[v] > n) return true;
                }                
            }
        }
    }
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
        E[a].push_back(Edge(b, Rab, Cab));
        E[b].push_back(Edge(a, Rba, Cba));
    }

    if(SPFA(N, S, V))   printf("YES\n");
    else printf("NO\n");
    return 0;
}