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
//WA不行的啦
const int MAXN = 1010;
const int INF = 0x3f3f3f3f;
int dis[MAXN];
bool vis[MAXN];
int A, B;
bool D[MAXN][MAXN];
struct qnode{
    int u;
    int c;
    int pre;
    qnode(int _u=0, int _c=0,int _p=0):u(_u), c(_c),pre(_p){}
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
bool Dijkstra(int start, int n)
{
    for(int i = 1;i <= n;++i){
        dis[i] = INF;
        vis[i] = false;
    }
    dis[start] = 0;
    priority_queue<qnode> Q;
    Q.push(qnode(start, 0, 0));
    while(!Q.empty()){
        int u = Q.top().u;
        int pre = Q.top().pre;
        Q.pop();
        D[u][pre] = D[pre][u] = true;
        if(vis[u])  continue;
        vis[u] = true;
        printf("u = %d\n", u);
        for(int i = 0;i < E[u].size();++i){
            int v = E[u][i].v;
            int cost = E[u][i].cost;
            if(!vis[v] && dis[v] > dis[u]+cost && !D[u][v]){
                dis[v] = dis[u] + cost;
                printf("v = %d u = %d cost + %d\n", v, u, cost);
                Q.push(qnode(v, dis[v], u));
            }    
        }
    }
    if(dis[B] == INF)   return false;
    
    return true;
} 

void addEdge(int u, int v, int c)
{
    E[u].push_back(Edge(v, c));
}

int main()
{
    ifstream infile;
    infile.open("D://input.txt", ios::in);
    int T;
    //scanf("%d", &T);
    infile >> T;
    //printf("%d\n", T);
    while (T-- > 0)
    {
        int n, m;
        ///scanf("%d%d", &n, &m);
        infile >> n >> m;
        for(int i = 1;i <= n;++i)   E[i].clear();
        memset(D, 0, sizeof(D));
        for(int i = 1;i <= m;++i){
            int a, b, c;
            //scanf("%d%d%d", &a, &b, &c);
            infile >> a >> b >> c;
            addEdge(a, b, c);
            addEdge(b, a, c);
        }
        infile >> A >> B;
        //scanf("%d%d", &A, &B);   
        int t = 0;
        while (Dijkstra(A, n))
            t++;
        printf("%d\n", t);
        
    }
    infile.close();

    return 0;
}