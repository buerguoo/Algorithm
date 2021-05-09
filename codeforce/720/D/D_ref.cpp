#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(x) cout << #x << ": " << (x) << endl
#else
#define debug(x)
#endif
//GNU C++14
using namespace std;
typedef long long ll;
typedef vector<int> vi;
const int maxn=1e6+7,inf=0x3f3f3f3f,mod=1e9+7;
 
vi g[maxn];
int n,y[maxn],z[maxn];
 
struct node
{
    int xl,yl,xr,yr;
};
vector<node>ans;
void dfs(int u,int fa)
{
    y[u]=u,z[u]=0;
    vi q;
    for(auto &v:g[u])
    {
        if(v==fa) continue;
        dfs(v,u);
        if(z[v]) q.push_back(v);
        else
        {
            if(y[u]==u) y[u]=y[v];
            else if(!z[u]) z[u]=y[v];
            else
            {
                ans.push_back({u,v,v,y[u]});
                y[u]=y[v];
            }
        }
    }
    for(auto &v:q)
    {
        ans.push_back({u, v, y[v], y[u]});
        y[u]=z[v];
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int kase;
    cin>>kase;
    while(kase--)
    {
        cin>>n;
        for(int i=0;i<=n;++i) g[i].clear();
        ans.clear();
        for(int i=0,u,v;i<n-1;++i)
        {
            cin>>u>>v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1,0);
        cout<<ans.size()<<'\n';
        for(auto &it:ans) cout<<it.xl<<" "<<it.yl<<" "<<it.xr<<" "<<it.yr<<'\n';
    }
    return 0;
}