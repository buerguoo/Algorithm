#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxm=2005000;
const int maxn=200500;
struct Edge
{
    int next;int id;int to;
}edge[maxm];
int head[maxn],dist[maxn],f[maxn],low[maxn],dfn[maxn],visit[maxn];
int n,m,cnt,ans,step;
void init()
{
    memset(dist,0,sizeof(dist));
    memset(visit,0,sizeof(visit));
    memset(head,-1,sizeof(head));
    memset(low,0,sizeof(low));
    memset(dfn,0,sizeof(dfn));
    for(int i=1;i<=n;i++)
        f[i]=i;
    step=ans=cnt=0;
}
int findf(int u)
{
    if(u==f[u])
        return u;
    else
    {
        f[u]=findf(f[u]);
        return f[u];
    }
}
void join(int u,int v)
{
    int t1=findf(u);int t2=findf(v);
    if(t1!=t2)
        f[t2]=t1;
}
void add(int u,int v,int id)
{
    edge[cnt].next=head[u];edge[cnt].to=v;edge[cnt].id=id;head[u]=cnt++;
    edge[cnt].next=head[v];edge[cnt].to=u;edge[cnt].id=id;head[v]=cnt++;
}
void tarjan(int u,int fa)
{
    low[u]=dfn[u]=++step;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v=edge[i].to;int id=edge[i].id;
        if(fa==id)
            continue;
        if(!dfn[v])
        {
            tarjan(v,id);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
            {
                ans++;
            }
            else
            {
                join(u,v);
            }
        }
        else
        {
            low[u]=min(low[u],dfn[v]);
        }
    }
}
void bfs(int u)
{
    visit[u]=1;dist[u]=0;
    queue<int>q;
    q.push(u);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i!=-1;i=edge[i].next)
        {
            int v=edge[i].to;
            if(visit[v])
                continue;
            if(findf(x)==findf(v))
            {
                q.push(v);dist[v]=dist[x];visit[v]=1;
            }
            else
            {
                q.push(v);dist[v]=dist[x]+1;visit[v]=1;
            }
        }
    }
}
int main()
{
    int x,y;
    while(scanf("%d%d",&n,&m)&&n&&m)
    {
        init();
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d",&x,&y);
            add(x,y,i);
        }
        tarjan(1,0);
        bfs(1);
        int maxx=0;int pos=1;
        for(int i=1;i<=n;i++)
        {
            if(maxx<dist[i])
            {
                maxx=dist[i];pos=i;
            }
        }
        memset(visit,0,sizeof(visit));memset(dist,0,sizeof(dist));
        bfs(pos);
        maxx=0;
        for(int i=1;i<=n;i++)
        {
            if(maxx<dist[i])
                maxx=dist[i];
        }
        printf("%d\n",ans-maxx);
    }
}