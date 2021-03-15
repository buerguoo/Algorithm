//没搞懂啊...
/*
Author:buerguoo
Time:
memory:

Data:
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
const int MAXN = 10010;
const int MAXM = 100010;
const int INF = 0x3f3f3f3f;
/*
    SAP算法
    邻接矩阵
*/
int maze[MAXN][MAXN];
int gap[MAXN], cur[MAXN], pre[MAXN], dis[MAXN];
int SAP(int start, int end, int nodenum)
{
    memset(dis, 0, sizeof(dis));
    memset(cur, 0, sizeof(cur));
    memset(gap, 0, sizeof(gap));
    int u = pre[start] = start, aug = -1, maxflow = 0;
    gap[0] = nodenum;
    while(dis[start] < nodenum){
        loop:
            for(int v = cur[u];v < nodenum;++v)
                if(maze[u][v] && dis[u] == dis[v]+1){
                    if(aug == -1 || aug > maze[u][v])   aug = maze[u][v];
                    pre[v] = u;
                    u = cur[u] = v;
                    if(v == end){
                        maxflow += aug;
                        for(u = pre[u];v != start;v = u, u = pre[u]){
                            maze[u][v] -= aug;
                            maze[v][u] += aug;
                        }
                        aug = -1;
                    }
                    goto loop;
                }
                int mindis = nodenum - 1;
                for(int v = 0;v < nodenum;++v)
                    if(maze[u][v] && mindis > dis[v]){
                        cur[u] = v;
                        mindis = dis[v];
                    }
                if((--gap[dis[u]]) == 0) break;
                gap[dis[u] = mindis+1]++;
                u = pre[u];
    }
    return maxflow;    
}

int head[MAXN], Q[MAXN];
int dep[MAXN], sta[MAXN], cur[MAXN];
int tol;
struct Edge{
    int to, next, flow, cap;
}E[MAXM];
void init(){
    tol = 2;
    memset(head, -1, sizeof(head));
}
void addEdge(int u, int v, int w, int rw = 0){
    E[tol].to = v; E[tol].cap = w; E[tol].flow = 0; E[tol].next = head[u];
    head[u] = tol++;
    E[tol].to = u; E[tol].cap = rw; E[tol].flow = 0; E[tol].next = head[v];
    head[v] = tol++;
}
bool bfs(int s, int t, int n)
{
    memset(dep, -1, sizeof(dep));
    dep[s] = 0;
    int front = 0, tail = 0;
    Q[tail++] = s;
    while(front < tail){
        int u = Q[front++];
        for(int i = head[u];i != -1;i = E[i].next){
            int v = E[i].to;
            if(dep[v] != -1 && E[i].flow < E[i].cap){
                dep[v] = dep[u] + 1;
                if(v == t) return true;
                Q[tail++] = v;
            }
        }
    }
    return false;
}
int dinic(int s, int t, int n)
{
    int maxflow = 0;
    while(bfs(s, t, n)){
        for(int i = 0;i < n;++i) cur[i] = head[i];
        int u = s, tail = -1;
        while(cur[s] != -1){
            if(u == t){
                int tp = INF;
                //到达结尾后获得该路径的最小流
                for(int i = tail-1;i >= 0;--i)  
                    tp = min(tp, E[sta[i]].cap- E[sta[i]].flow);
                //更新
                maxflow += tp;
                for(int i = tail-1;i >= 0;--i){
                    E[sta[i]].flow += tp;
                    E[sta[i]^1].flow -= tp;
                    if(E[i].cap - E[i].flow == 0)
                        tail = i;
                }
                u = E[sta[tail]^1].to;
            }
            //可向下继续寻找，sta[]记录路径，路径的标号为tail
            //cur[]表示当前顶点为遍历的第一个边，u是当前顶点
            else if(cur[u] != -1 && dep[u] + 1 == dep[E[cur[u]].to] &&
                E[cur[u]].cap > E[cur[u]].flow){
                    sta[tail++] = cur[u];
                    u = E[cur[u]].to;
            }
            //回退，找到断点，并寻找下一条边
            else{
                while(u != s && cur[u] == -1)
                    u = E[sta[--tail]^1].to;
                cur[u] = E[cur[u]].next;
            }
        }
    }
    return maxflow;
}
