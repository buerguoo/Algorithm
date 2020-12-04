#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//TLE
const int MAXM = 30100;
const int MAXN = 150100;
const int INF = 0x3f3f3f3f;
bool vis[MAXM];
int dis[MAXM];
int head[MAXM];
int stack[MAXN]; //作为栈
int top;    //栈顶
int cnt;
struct Edge{
    int v;
    int cost;
    int next;
    //Edge(int _v=0, int _c=0):v(_v), cost(_c){}
}E[MAXN];

//vector<Edge> E[MAXM];

void AddEdge(int u, int v, int c)
{
    E[cnt].v = v;
    E[cnt].cost = c;
    E[cnt].next = head[u];
    head[u] = cnt++;
}

int SPFA(int start, int n)
{
    for(int i = 1;i <= n;i++){
        vis[i] = false;
        dis[i] = INF;
    }
    dis[start] = 0;
    stack[top++] = start;
    vis[start] = true;
    while(top != 0){
        int u = stack[--top];
        vis[u] = false;
        //printf("%d %d\n", u, E[u].size());
        for(int i = head[u];i != -1;i = E[i].next){
            int v = E[i].v;
            int cost = E[i].cost;
            //printf("dv=%d du=%d c=%d\n", dis[v], dis[u], cost);
            if(dis[v] > dis[u] + cost){
                dis[v] = dis[u] + cost;
                if(!vis[v]){
                    stack[top++] = v;
                    vis[v] = true;
                }
            }
        }
    }
    return dis[n];
}

int main()
{
    int M, N;
    while(scanf("%d%d", &M, &N) != EOF){
    int x, y, z;
    top = 0;
    cnt = 0;
    memset(head, -1, sizeof(head));
    for(int i = 0;i < N;++i){
        scanf("%d%d%d", &x, &y, &z);
        AddEdge(x, y, z);
    }
    int ans = SPFA(1, M);
    printf("%d\n", ans);
    }
    return 0;
}