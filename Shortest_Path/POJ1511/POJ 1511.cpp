#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//Dijkstra+堆优化
const int MAXN = 1000100;
const int INF = 0x3f3f3f3f;
long long int sum; 
bool vis[MAXN];
int dis[MAXN];
int a[MAXN][3];
struct Edge{
    int v;
    int cost;
    Edge(int _v=0, int _c=0):v(_v), cost(_c){}
};
vector<Edge> E[MAXN];
void AddEdge(int u, int v, int c)
{
    E[u].push_back(Edge(v, c));
}

void SPFA(int start, int n)
{
    for(int i = 1;i <= n;i++){
        vis[i] = false;
        dis[i] = INF;
    }
    dis[start] = 0;
    queue<int> Q;
    while(!Q.empty())   Q.pop();
    Q.push(start);
    vis[start] = true;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        vis[u] = false;
        for(int i = 0;i < E[u].size();i++){
            int v = E[u][i].v;
            int cost = E[u][i].cost;
            if(dis[v] > dis[u] + cost){
                dis[v] = dis[u] + cost;
                if(!vis[v]){
                    Q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    for(int i = 1;i <= n;++i)
        sum += dis[i];
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--){
        int P, Q;
        scanf("%d%d",&P, &Q);
        sum = 0;
        for(int i = 1;i <= P;i++)   E[i].clear();
        for(int i = 0;i < Q;++i)    scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);
        for(int i = 0;i < Q;++i)
            AddEdge(a[i][0], a[i][1], a[i][2]);
        SPFA(1, P);
        for(int i = 1;i <= P;++i)   E[i].clear();
        for(int i = 0;i < Q;i++)
            AddEdge(a[i][1], a[i][0], a[i][2]);
        SPFA(1, P);
        printf("%lld\n", sum);
    }
    return 0;
}