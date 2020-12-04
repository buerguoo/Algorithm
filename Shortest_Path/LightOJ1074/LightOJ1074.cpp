#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
using namespace std;
//FPSA求负环
const int MAXN = 210;
const int INF = 0x3f3f3f3f;
int dis[MAXN];
bool vis[MAXN];
int cnt[MAXN];
int jun[MAXN];
int q[MAXN];
struct Edge{
    int v;
    int cost;
    Edge(int _v=0, int _c=0):v(_v), cost(_c){}
};
vector<Edge> E[MAXN];
void addEdge(int u, int v,int c)
{
    E[u].push_back(Edge(v, c));
}

void SPFA(int start, int n)
{
    for(int i = 1;i <= n;++i){
        vis[i] = false;
        dis[i] = INF;
        cnt[i] = 0;
    }
    dis[start] = 0;
    queue<int> Q;
    Q.push(start);
    cnt[start] = 1;
    vis[start] = true;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        vis[u] = false;
        for(int i = 0;i < E[u].size();++i){
            int v = E[u][i].v;
            int cost = E[u][i].cost;
            if(dis[v] > dis[u]+cost){
                dis[v] = dis[u] + cost;
                if(!vis[v]){
                    vis[v] = true;
                    if(++cnt[v] > n)    dis[v] = -INF;
                    if(cnt[v] <= n)     Q.push(v);
                }
            }
        }
    }
}

int main()
{
    //ifstream infile;
    //infile.open("D://input.txt", ios::in);
    int T;
    //infile >> T;
    scanf("%d", &T);
    int t = 0;
    while (t++ < T)
    {
        int N;
        //infile >> N;
        //getchar();
        scanf("%d", &N);
        for(int i = 1;i <= N;++i)    scanf("%d", &jun[i]);//infile>>jun[i];
        for(int i = 1;i <= N;++i)   E[i].clear();
        int v, u;
        int n;
        //infile >> n;
        scanf("%d", &n);
        for(int i = 1;i <= n;++i){
            scanf("%d%d", &u, &v);
            //infile >> u >> v;
            addEdge(u, v, (int)pow(double(jun[v]-jun[u]),3));
        }
        //infile >> n;
        scanf("%d", &n);
        for(int i = 0;i < n;++i)     scanf("%d", &q[i]);//infile>>q[i];

        printf("Case %d:\n", t);
        SPFA(1, N);
        for(int i = 0;i < n;++i){
            if(dis[q[i]] == INF || dis[q[i]] < 3)
                printf("?\n");
            else
                printf("%d\n", dis[q[i]]);
        }
    }
    //infile.close();
    return 0;
}