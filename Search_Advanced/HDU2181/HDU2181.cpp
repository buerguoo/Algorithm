#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;
#define N 25
int G[N][N],path[N],vis[N],m,t = 0;

void Dfs(int x,int k)
{
    
    if(k == 21 ){
        if(G[x][m]){
        path[21] = path[1];
        printf("%d: ",++t);
        for(int i = 1;i <= 21;i++)
            printf(" %d",path[i]);
        printf("\n");
        }
        return ;
    }
        for(int j = 1;j < 21;++j) if(!vis[j] && G[x][j])
            {
                path[k] = j;
                vis[j] = 1;
                Dfs(j,k+1);
                vis[j] = 0;
            }
    
}

int main()
{
    int a,b,c;
    int p = 0;
    memset(vis,0,sizeof(vis));
    memset(G,0,sizeof(G));
    for(int i = 1;i < 21;++i)
    {
        cin >> a >> b>> c;
        G[i][a] = G[i][b] = G[i][c] = 1;
             
    }
    while(cin >> m && m){
    vis[m] = 1;
    path[1] = m;
    Dfs(m,2);
    }
    return 0;
}