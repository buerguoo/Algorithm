#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int MAXN = 10010;
const int MAXM = 20010;
int head[MAXN], tol;
bool vis[MAXN];
ll dist[MAXN];
int s, t, n, m;
struct node{
    int u; 
    ll dis;
    bool operator<(const node &a) const{
        return dis > a.dis;
    }
};
struct Edge{
    int to, next;
    ll dis, weight;
    Edge(){}
    Edge(int _t, ll _w, int _n, ll _d):to(_t), weight(_w), next(_n), dis(_d){}
}E[MAXM];
void init()
{
    tol = 0;
    memset(head, -1, sizeof(head));
}
void addEdge(int u, int v, ll weight, ll dis)
{
    E[tol] = Edge(v, weight, head[u], dis);
    head[u] = tol++;
}
ll dijkstra(ll w)
{
    for(int i = 1;i <= n;++i){
        dist[i] = INF;
        vis[i] = false;
    }
    dist[s] = 0;
    priority_queue<node> Q;
    Q.push({s, dist[s]});
    while(!Q.empty()){
        int u = Q.top().u;
        Q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(int i = head[u];i != -1;i = E[i].next){
            int v = E[i].to, dis = E[i].dis, weight = E[i].weight;
            if(w > weight) continue;
            if(!vis[v] && dist[u] + dis < dist[v]){
                dist[v] = dist[u] + dis;
                Q.push({v, dist[v]});
            }
        }
    }
    return dist[t];
}
int main()
{   
    ll w, d;
    int u, v;
    ll weight, dis, max_weight = 0;
    init();
    scanf("%d %d %d %d %lld %lld", &n, &m, &s, &t, &w, &d);
    while(m--){
        scanf("%d %d %lld %lld", &u, &v, &weight, &dis);
        addEdge(u, v, weight, dis);
        addEdge(v, u, weight, dis);
        max_weight = max(max_weight, weight);
    }
    ll min_dis = dijkstra(w);
    ll l = w+1, r = max_weight, ans = -1;
    while(l <= r){
        int md = (l + r) >> 1;
        if(min_dis + dijkstra(md) <= d){
            ans = md;
            l = md + 1;
        }else r = md - 1;
    }
    printf("%lld\n", ans == -1 ? -1 : ans - w);
    return 0;
}