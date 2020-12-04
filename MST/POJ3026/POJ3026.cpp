/*
Author:buerguoo
Time：
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
using namespace std;
const int MAXN = 55;
const int INF = 0x3f3f3f3f;
int cost[MAXN*MAXN][MAXN*MAXN];
int p[MAXN][MAXN];
int lowcost[MAXN*MAXN];
char mp[MAXN][MAXN];
bool vis[MAXN*MAXN];
bool v[MAXN][MAXN];
int node[MAXN*MAXN];
int cnt;
int dir[4][2] = {{0,1}, {1, 0}, {0, -1}, {-1, 0}};
map<int, int> M;
int prim(int n)
{
    int ans = 0;
    memset(vis, false, sizeof(vis));
    for(int i = 0;i < n;++i)    lowcost[i] = cost[0][i];
    vis[0] = true;
    for(int i = 1;i < n;++i){
        int minc = INF;
        int p = -1;
        for(int j = 0;j < n;++j)
            if(!vis[j] && lowcost[j] < minc){
                minc = lowcost[j];
                p = j;
            }
        if(minc == INF) return -1;
        vis[p] = true;
        ans += minc;
        for(int j = 0;j < n;++j)
            if(!vis[j] && lowcost[j] > cost[p][j])
                lowcost[j] = cost[p][j];
    }

    return ans;
}
void bfs(int s, int m, int n)
{
    queue<int>  Q;
    memset(p, 0, sizeof(p));
    memset(v, false, sizeof(v));
    while(!Q.empty())   Q.pop();
    Q.push(s);
    v[s/n][s%n] = true; 
    while(!Q.empty()){
        int tmp = Q.front();
        Q.pop();
        int x = tmp / n;
        int y = tmp % n;
        for(int i = 0;i < 4;++i){
            int tx = x + dir[i][0];
            int ty = y + dir[i][1];
            if(!v[tx][ty] && tx >= 0 && tx < m && ty < n && ty >= 0){
                if(mp[tx][ty] != '#'){
                    Q.push(tx*n+ty);
                    v[tx][ty] = true;
                    p[tx][ty] = p[x][y] + 1;
                }  
                if(mp[tx][ty] == 'A' || mp[tx][ty] == 'S')
                    cost[M[s]][M[tx*n+ty]]  = p[tx][ty];
            }
        }
    }
}
int main()
{
    int N;
    scanf("%d", &N);
    while (N--)
    {
        int n, m;
        cnt = 0;
        M.clear();
        memset(mp, 0, sizeof(mp));
        scanf("%d%d", &n, &m);
        //getchar();
        char temp[51];
		gets(temp);
        for(int i = 0;i < m;++i){
            gets(mp[i]);
            for(int j = 0;j < n;++j)
            {
                //scanf("%c", &mp[i][j]);
                if(mp[i][j] == 'A' || mp[i][j] == 'S')
                {
                    node[cnt] = i*n+j;
                    M[i*n+j] = cnt++;
                }
            }
            //getchar();
        }
        for(int i = 0;i < cnt;++i)
            bfs(node[i], m, n);
        
        printf("%d\n", prim(cnt));            
    }
    
    return 0;
}