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
const int MAXN = 310;
const int INF = 0x3f3f3f3f;
int dis[MAXN];
bool vis[MAXN];
int E[MAXN][MAXN];
struct  qnode
{
    int u;
    int cost;
    qnode(int _u=0, int _c=0):u(_u), cost(_c){}
    bool operator < (const qnode &r) const{
        return cost > r.cost;
    }
};

void Dijkstra(int start, int n)
{
    priority_queue<qnode> Q;
    while (!Q.empty())  Q.pop();
    for(int i = 0;i < n;++i){
        vis[i] = false;
        if(i == start)
            dis[i] = INF;
        else {
            dis[i] = E[start][i];
            Q.push(qnode(i, dis[i]));
        }
    } 
    while(!Q.empty()){
        int u = Q.top().u;
        Q.pop();
        //printf("?u = %d\n", u);
        if(vis[u])  continue;
        vis[u] = true;
        //printf("u = %d\n", u);
        for(int i = 0;i < n;i++){
            if(!vis[i] && dis[u]+E[u][i] < dis[i]){
                dis[i] = dis[u] + E[u][i];
                Q.push(qnode(i, dis[i]));
            }
        }
    }
}

int main()
{
    int n;
    //ifstream infile;
    //infile.open("D://input.txt", ios::in);
    //scanf("%d", &n) != EOF
    while (scanf("%d", &n) != EOF)
    {
        memset(E, -1, sizeof(E));
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j)
                //infile >> E[i][j];
                scanf("%d", &E[i][j]);
        
        Dijkstra(0, n);
        int ans = dis[n-1];
        int huan1 = dis[0];
        Dijkstra(n-1, n);
        int huan2 = dis[n-1]; 
        printf("%d\n", min(ans, huan1+huan2));
    }
     //infile.close();
    return 0;
}