#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
#define MAXN 800
int m,n,vis[MAXN][MAXN],ghosts[2][2],pos[2][2],limit = 1;
char grids[MAXN][MAXN];
int dire[2][4] = {{1,-1,0,0},{0,0,1,-1}};

struct Node{
    int x,y;
}node;

queue<Node> Q[2];
Node a,nt;

bool check(Node a)
{
    if(abs(a.x-ghosts[1][0])+abs(a.y-ghosts[1][1])<=2*limit)
        return false;
    if(abs(a.x-ghosts[0][0])+abs(a.y-ghosts[0][1])<=2*limit) 
        return false;
    return true;
}

int step(int k)
{
    int tx,ty;
    int Size = Q[k].size();
    while(Size--){
    a = Q[k].front();
    Q[k].pop();
    if(!check(a)) continue;
    for(int i = 0;i < 4;++i){
        tx = a.x + dire[0][i],ty = a.y + dire[1][i];
        nt.x = tx,nt.y = ty;
        if(tx>=0 && tx<m && ty>=0 && ty<n && grids[tx][ty]!='X' && grids[tx][ty] != 'Z'
        && vis[tx][ty]!=k+1  && check(nt) ){

            if(vis[tx][ty]) return 1;
            vis[tx][ty] = k+1;
            Q[k].push(nt);
            }
        }
    }
    return 0;
}

int bfs()
{
    while(!Q[0].empty()) Q[0].pop();
    while(!Q[1].empty()) Q[1].pop(); 

    for(int i = 0;i < 2;++i)
    {
        a.x = pos[i][0],a.y = pos[i][1];
        vis[a.x][a.y] = i+1;
        Q[i].push(a);
    }

    while(!Q[0].empty() || !Q[1].empty()){
        for(int i = 0;i < 3;++i)
            if(step(0))
                return limit;
        if(step(1))
            return limit;
        limit++;
    }
    return 0;
}

int main()
{
    //TLE????搞不懂 草草草草草草草草草 
    int t,p,key;
    cin >> t;
    while(t--){
        cin >> m >> n;
        memset(vis,0,sizeof(vis));
        p = 0;
        for(int i = 0;i < m;++i)
            cin >> grids[i];
        for(int i = 0;i < m;i++)
            for(int j = 0;j < n;j++)
                {
                    if(grids[i][j] == 'Z')
                ghosts[p][0] = i,ghosts[p++][1] = j;
            if(grids[i][j] == 'M')
                pos[0][0] = i,pos[0][1] = j;
            if(grids[i][j] == 'G')
                pos[1][0] = i,pos[1][1] = j;
                }
        key = bfs();
        if(!key)
            cout << -1 << endl;
        else 
            cout << key << endl;
        limit = 1;
    }
    return 0;
}

