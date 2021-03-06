    /*
    Author:buerguoo
    Time:390ms
    memory:1876KB

    Data:2020-12-18 15:32:56
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
    const int MAXN = 1005;
    const int MAXM = 10010;
    const ll INF = 1e17;
    int in[MAXN], pre[MAXN], vis[MAXN], pos;
    ll id[MAXN];
    struct Edge{
        int u, v, cost;
    }E[MAXM];

    ll zhuliu(int root, int n, int m, Edge E[])
    {
        ll res = 0;
        while(1){
            for(int i = 0;i < n;++i)    in[i] = INF;
            for(int i = 0;i < m;++i)    if(E[i].v != E[i].u && E[i].cost < in[E[i].v]){
                in[E[i].v] = E[i].cost;
                pre[E[i].v] = E[i].u;
                if(E[i].u == root)
                    pos = i;    
            }
                
            for(int i = 0;i < n;++i) if(i != root && in[i] == INF) 
                return -1;

            int tn = 0;
            memset(id, -1, sizeof(id));
            memset(vis, -1, sizeof(vis));
            in[root] = 0;
            for(int i = 0;i < n;++i){
                res += in[i];
                int v = i;
                while(v != root && vis[v] != i && id[v] == -1){
                    vis[v] = i;
                    v = pre[v];
                }
                if(id[v] == -1 && v != root){
                    for(int u = pre[v];u != v;u = pre[u])
                        id[u] = tn;
                    id[v] = tn++;
                }
            }

            if(tn == 0) break;
            for(int i = 0;i < n;++i)
                if(id[i] == -1)
                    id[i] = tn++;
            
            for(int i = 0;i < m;i++){
                int v = E[i].v;
                E[i].u = id[E[i].u];
                E[i].v = id[E[i].v];
                if(E[i].v != E[i].u)
                    E[i].cost -= in[v];
                //这样会打乱边和根的关系
               // else
                    //swap(E[i], E[--m]);
            }
            n = tn;
            root = id[root];
        }
        
        return res;
    }

    int main()
    {
        int n, m;
        while(~scanf("%d%d", &n, &m)){
            int u, v, c;
            ll sum = 0;
            for(int i = 0;i < m;++i){
                scanf("%d%d%d", &u, &v, &c);
                E[i].u = ++u;
                E[i].v = ++v;
                E[i].cost = c;
                sum += c;
            }
            sum++;
            for(int i = m;i < n+m;++i){
                E[i].u = 0;
                E[i].v = i - m + 1;
                E[i].cost = sum;
            }           
            ll ans = zhuliu(0, n+1, n+m, E);
            if(ans == -1 || ans-sum>=sum)
                printf("impossible\n\n");
            else 
                printf("%lld %d\n\n", ans-sum, pos-m);
        }
        return 0;   
    }