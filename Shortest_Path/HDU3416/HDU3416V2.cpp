#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
using namespace std;
//SPFA最小费用最大流
//TLE
const int MAXN = 1010;
const int MAXM = 100100*2;
const int INF = 0x3f3f3f3f;
int dis[MAXN], pre[MAXN];
bool vis[MAXN];
int head[MAXN], tol;
int N;
struct Edge{
    int to, next, cap, flow, cost;
}edge[MAXM];
void Init(int n)
{
    N = n;
    tol = 0;
    memset(head, -1, sizeof(head));
}
void addEdge(int u, int v, int cap, int cost)
{
    edge[tol].to = v;
    edge[tol].cap = cap;
    edge[tol].flow = 0;
    edge[tol].cost = cost;
    edge[tol].next = head[u];
    head[u] = tol++;
    edge[tol].to = u;
    edge[tol].cap = 0;
    edge[tol].flow = 0;
    edge[tol].cost = -cost;
    edge[tol].next = head[v];
    head[v] = tol++;

}
bool SPFA(int s, int t)
{
    for(int i = 1;i <= N;++i){
        vis[i] = false;
        dis[i] = INF;
        pre[i] = -1;
    }
    dis[s] = 0;
    queue<int> Q;
    Q.push(s);
    vis[s] = true;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        vis[u] = false;
        for(int i = head[u];i != -1;i = edge[i].next){
            int v = edge[i].to;
            int cost = edge[i].cost;
            if(edge[i].cap > edge[i].flow && dis[v] > dis[u]+cost){
                dis[v] = dis[u] + cost;
                pre[v] = i;
                if(!vis[v]){
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }
    if(pre[t] == -1)    return false;
    return true;
    
}
int minCostMaxFlow(int s, int t, int &cost)
{
    int flow = 0;
    int all = INF;
    while (SPFA(s, t))
    {
        cost = 0;
        int MIN = INF;
        for(int i = pre[t];i != -1;i = pre[edge[i^1].to]){
            if(MIN > edge[i].cap - edge[i].flow)
                MIN = edge[i].cap - edge[i].flow;
        }
        //printf("MIN = %d\n", MIN);
        for(int i = pre[t]; i != -1;i = pre[edge[i^1].to]){
            //printf("i = %d\n", i);
            edge[i].flow += MIN;
            edge[i^1].flow -= MIN;
            cost += edge[i].cost * MIN;
        }
        if(all >= cost){
            flow += MIN;
            all = cost;
        }
        
        //printf("cost = %d\n", cost);
    }

    return flow;
}

int main()
{
    //ifstream infile;
    //infile.open("/home/buerguoo/文档/input.txt", ios::in);
    int T;
    scanf("%d", &T);
    //infile >> T;
    //printf("%d\n", T);
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        //infile >> n >> m;
        Init(n);
        for(int i = 1;i <= m;++i){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            //infile >> a >> b >> c;
            addEdge(a, b, 1, c);
        }
        int A, B;
        //infile >> A >> B;
        scanf("%d%d", &A, &B);   
        int t = 0;
        printf("%d\n", minCostMaxFlow(A, B, t));
        
    }
    //infile.close();

    return 0;
}