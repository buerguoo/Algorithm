/*
Author:buerguoo
Time:10ms
memory:

Data:2020-12-03 14:39:28
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
#define FILL(a, b)  memset(a, b, sizeof(a))
typedef long long ll;
const int MAXN = 110;
const int INF = 0x3f3f3f3f;
int F[MAXN], ind[MAXN] ,cnt;
struct Edge
{
    int u, v, w;
    Edge(int _u=0, int _v=0, int _w=0):u(_u), v(_v), w(_w){}
    bool operator< (const Edge &r) const{
        return w<r.w;
    }
}E[MAXN<<1];
void addEdge(int u, int v, int w)
{
    E[cnt].u = u;
    E[cnt].v = v;
    E[cnt++].w = w; 
}
int find(int x)
{
    if(F[x] == -1)  return x;
    else return F[x] = find(F[x]);
}
int Kruskal(int n, int moved)
{
    int ans = 0, num = 0;
    memset(F, -1, sizeof(F));
    for(int i = 0;i < cnt;i++) if(i != moved)
    {
        int u = E[i].u;
        int v = E[i].v;
        int w = E[i].w;
        int t1 = find(u);
        int t2 = find(v);
        if(t1 != t2){
            if(moved == -1) ind[num] = i;
            ++num;
            ans += w;
            F[t1] = t2;
        }
        if(num == n-1) break;
    }
    if(num != n-1) return INF;

    return ans;
}
int main()
{
    int T, t = 0;
    scanf("%d", &T);
    while (t++ < T)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        cnt = 0;
        int a, b, c;
        while(m--){
            scanf("%d%d%d", &a, &b, &c);
            addEdge(a, b, c);
        }

        sort(E, E+cnt);

        int mst = Kruskal(n, -1);
        if(mst == INF)   printf("Case #%d : No way\n", t);
        else{
            int Min = INF;
            for(int i = 0;i < n-1;++i)
                Min = min(Min, Kruskal(n, ind[i]));
            if(Min == INF)  printf("Case #%d : No second way\n", t);
            else   printf("Case #%d : %d\n",t, Min);
        }
    }
    
    return 0;
}