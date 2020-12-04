#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
using namespace std;
//Dijkstra+堆优化
//WA
const int MAXN = 100100;
const int INF =0x3f3f3f3f;
int dis[MAXN];
bool vis[MAXN];
int c[MAXN];
int C;
bool door;
struct qnode{
    int u;
    int c;
    qnode(int _u=0, int _c=0):u(_u), c(_c){}
    bool operator < (const qnode &r) const{
        return c > r.c;
    }
};
struct Edge{
    int v;
    int cost;
    Edge(int _v=0, int _c=0):v(_v), cost(_c){}
};
vector<Edge> E[MAXN];
int Dijkstra(int start, int n)
{
    for(int i = 1;i <= n;++i){
        dis[i] = INF;
        vis[i] = false;
    }
    if(c[start] != c[n])    dis[n] = C;
    dis[start] = 0;
    priority_queue<qnode> Q;
    Q.push(qnode(start, 0));
    while(!Q.empty()){
        int u = Q.top().u;
        Q.pop();
        if(vis[u])  continue;
        vis[u] = true;
        for(int i = 0;i < E[u].size();++i){
            int v = E[u][i].v;
            int cost = E[u][i].cost;
            if(!vis[v] && dis[v] > dis[u]+cost){
                dis[v] = dis[u] + cost;
                Q.push(qnode(v, dis[v]));
            }    
        }
    }

    if(c[start] == c[n] && door){
    int MIN = INF;
    for(int i = 1;i <= n;++i) if(c[i]!=c[start])  MIN = min(MIN, dis[i]);
    MIN = min(MIN, C);
    dis[n] = min(dis[n], MIN+C);
    }
    return dis[n];
}
void addEdge(int u, int v, int co)
{
    E[u].push_back(Edge(v, co));
}

int main()
{
    int T;
    int Case = 0;
    scanf("%d", &T);
    while(Case++ < T){
        int N, M;
        scanf("%d%d%d", &N, &M, &C);
        door = false;
        for(int i = 1;i <= N;++i) E[i].clear();
        for(int i = 1;i <= N;++i){
            int l;
            scanf("%d", &l);
            c[i] = l; 
            if(i>1&&l - c[i-1]!=0) door = true;
        }
        for(int i = 0;i < M;++i){
            int u, v, co;
            scanf("%d%d%d", &u, &v, &co);
            addEdge(u, v, co);
            addEdge(v, u, co);
        }
    int ans = Dijkstra(1, N);
    if(ans == INF)  ans = -1;
    printf("Case #%d: %d\n", Case, ans);
    }
    return 0;
}