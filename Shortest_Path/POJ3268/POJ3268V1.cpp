#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//Dijkstra+堆优化
const int MAXN = 1010;
const int INF = 0x3f3f3f3f;
bool vis[MAXN], _vis[MAXN];
int dis[MAXN], _dis[MAXN];

struct qnode
{
    int v;
    int c;
    qnode(int _v=0, int _c=0):v(_v), c(_c){}
    bool operator <(const qnode &r) const{
        return c > r.c;
    } 
};

int E[MAXN][MAXN];

int Dijkstra(int n, int beg)
{
    for(int i = 0;i < n;++i){
        dis[i] =   _dis[i] = INF;
        vis[i] = _vis[i] = false;
    }
    dis[beg] =  _dis[beg] = 0;
    priority_queue<qnode> Q, _Q;
    Q.push(qnode(beg, 0));
    while(!Q.empty()){
        qnode tmp = Q.top();
        Q.pop();
        int u = tmp.v;
        if(vis[u])  continue;
        vis[u] = true;
        for(int v = 0;v < n;++v){
            int cost = E[u][v];
            if(dis[v] > dis[u] + cost){
                dis[v] = dis[u] + cost;
                Q.push(qnode(v, dis[v]));
            }
        }
    }
    _Q.push(qnode(beg, 0));
    while(!_Q.empty()){
        qnode _tmp = _Q.top();
        _Q.pop();
        int u = _tmp.v;
        if(_vis[u])  continue;
        _vis[u] = true;
        for(int v = 0;v < n;++v){
            int _cost = E[v][u];
            if(_dis[v] > _dis[u] + _cost){
                _dis[v] = _dis[u] + _cost;
                _Q.push(qnode(v, _dis[v]));
            }
        }
    }
    int MAX = 0;
    for(int i = 0;i < n;++i) if(MAX < dis[i]+_dis[i])
        MAX = dis[i] + _dis[i];
    
    return MAX;
}

int main()
{
    int N, M, X;
    int x, y, z;
    scanf("%d%d%d", &N, &M, &X);
    for(int i = 0;i < N;++i)
        for(int j = 0;j < N;++j)
            E[i][j] = INF;
    for(int i = 0;i < M;++i){
        scanf("%d%d%d", &x, &y, &z);
        E[x-1][y-1] = z;
    }
    printf("%d\n", Dijkstra(N, X-1));

    return 0;
}