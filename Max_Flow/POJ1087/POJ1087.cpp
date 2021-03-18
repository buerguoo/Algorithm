/*
Author:buerguoo
Time:0ms
memory:168kB

Data:2021-03-18 15:27:35
*/
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
const int MAXM = 10100;
int head[MAXN], tol;
int dep[MAXN], sta[MAXN], cur[MAXN], k;
int G[MAXN];
char name[3000][30];
struct Edge{
    int to, next, flow, cap;
}E[MAXM];
void addEdge(int u, int v, int w, int rw = 0){
    E[tol].to = v; E[tol].cap = w; E[tol].flow = 0;
    E[tol].next = head[u]; head[u] = tol++;
    E[tol].to = u; E[tol].cap = rw; E[tol].flow = 0;
    E[tol].next = head[v]; head[v] = tol++;
}
void init(){
    tol = 2;
    memset(head, -1, sizeof(head));
}
bool bfs(int s, int t, int n)
{
    memset(dep, -1, sizeof(dep));
    dep[s] = 0;
    int front = 0, tail = 0;
    G[tail++] = s;
    while(front < tail){
        int u = G[front++];
        for(int i = head[u];i != -1;i = E[i].next){
            int v = E[i].to;
            if(dep[v] == -1 && E[i].cap > E[i].flow){
                dep[v] = dep[u] + 1;
                if(v == t) return true;
                G[tail++] = v;
            }
        }
    }
    return false;
}
int dinic(int s, int t, int n){
    int maxflow = 0;
    while(bfs(s, t, n)){
        for(int i = 0;i < n;++i) cur[i] = head[i];
        int u = s, tail = 0;
        while(cur[s] != -1){
            if(u == t){
                int tp = INF;
                for(int i = tail-1;i >= 0;--i)  
                    tp = min(tp, E[sta[i]].cap-E[sta[i]].flow);
                maxflow += tp;
                for(int i = tail-1;i >= 0;--i){
                    E[sta[i]].flow += tp;
                    E[sta[i]^1].flow -= tp;
                    if(E[sta[i]].cap - E[sta[i]].flow == 0)
                        tail = i;
                }
                u = E[sta[tail]^1].to;
            }else if(cur[u] != -1 && E[cur[u]].cap > E[cur[u]].flow && 
                dep[u] + 1 == dep[E[cur[u]].to]){
                    sta[tail++] = cur[u];
                    u = E[cur[u]].to;
            }else{
                while(u != s && cur[u] == -1)
                    u = E[sta[--tail]^1].to;
                cur[u] = E[cur[u]].next;
            }
        }
    }
    return maxflow;
}
int sol(char *str)
{
    int i;
    if(k==0)
    {
        strcpy(name[1],str);
        k=1;
        return  1;
    }
    for(i=1; i<=k; i++)
        if(strcmp(name[i],str)==0)
            return i;
    k++;
    strcpy(name[k],str);
    return k;
}
int main()
{
    int n1,n2,n3;
    int st,ed;
    int a,b;
    int num1[105][2],num2[105][2],num3[105][2];
    char str1[30],str2[30];
    while(~scanf("%d",&n1))
    {
        k=0;
        init();
        for(int i=0;i<n1;i++)
        {
            scanf("%s",str1);
            num1[i][0]=sol(str1);
        }
        scanf("%d",&n2);
        for(int i=0;i<n2;i++)
        {
            scanf("%s%s",str1,str2);
            num2[i][0]=sol(str1);
            num2[i][1]=sol(str2);
        }
        scanf("%d",&n3);
        for(int i=0;i<n3;i++)
        {
            scanf("%s%s",str1,str2);
            num3[i][0]=sol(str1);
            num3[i][1]=sol(str2);
        }
        int s = 0, t = k+1;
        for(int i=0;i<n1;i++)
        {
            addEdge(num1[i][0],t,1);
        }
        for(int i=0;i<n2;i++)
        {
            addEdge(num2[i][0],num2[i][1],1);
            addEdge(s,num2[i][0],1);
        }
        for(int i=0;i<n3;i++)
        {
            addEdge(num3[i][0],num3[i][1],INF);
        }
        printf("%d\n",n2-dinic(s, t, k+2));
    }
    return 0;
}