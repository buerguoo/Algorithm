#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define MAXN 101
int count_cas,energy,m,n,ans;
int dier[2][5] = {{1,0,0,-1,0},{0,1,0,0,-1}};
bool vis_but[MAXN][MAXN][1010],vis[MAXN][MAXN][1010],M[MAXN][MAXN];

struct Node
{
    int x,y,t;
};

struct Cast
{
    char dir;
    int a,b,per,ver;
    int d;
}Cas[MAXN];

void Aim_ans(char D,Cast &N)
{
    
        switch (D)
        {
        case 'N':
        N.d = 3;
            break;
        case 'S':
        N.d = 0;
            break;
        case 'E':
         N.d = 1;
            break;
        case 'W':
        N.d = 4;
            break;
        }
}

void Shoot(int t)
{
        for(int i = 0;i < count_cas;++i){
        Cast N = Cas[i]; 
        int p = dier[0][N.d],k = dier[1][N.d],j = 1;
        int la_ti = t % N.per,z = N.ver*N.per;
        int D_x = 0,D_y = 0,x = N.a,y = N.b;
        for(;D_x < la_ti*N.ver;D_x++,D_y++)
        {
            if(M[x+p*D_x][y+k*D_y])
            {
                j = 0;
                break;
            }
        }
        if(!j)
            continue;
        x += p*D_x,y += k*D_y;
        vis_but[x][y][t] = true;
        for(j=1;;++j)
        {
            x += p,y += k;
            if(M[x][y] || x < 0 || y < 0 || x > m || y > m)
                break;
            if(j % z == 0)
                vis_but[x][y][t] = true;
        }
    }
}

bool BFS()
{
    queue<Node> Q;
    Node a,next;
    a.x = 0,a.y = 0,a.t = 1;
    vis[a.x][a.y][a.t] = true;
    Q.push(a);
    while(!Q.empty())
    {
        a = Q.front();
        Q.pop();
        if(a.x == m && a.y == n)
           {    
               ans = a.t;
               return true;
           }
        if(a.t-1 > energy)
            return false;
        for(int i = 0;i < 5;++i)
        {
            int tx = a.x + dier[0][i],ty = a.y + dier[1][i];
            if(tx >= 0 && tx <= m && ty >= 0 && ty <= n  && !M[tx][ty]
            && !vis_but[tx][ty][a.t] && !vis[tx][ty][a.t+1])
            {
                next.x = tx,next.y = ty,next.t = a.t + 1;
                vis[tx][ty][next.t] = true;
                Q.push(next);
            } 
        }
    }
    return false;
}

int main()
{
    int key;
    while(cin >> m >> n >> count_cas >> energy){
    memset(vis_but,0,sizeof(vis_but));
    memset(vis,0,sizeof(vis));
    memset(M,0,sizeof(M));
    for(int i = 0;i < count_cas;++i)
       { 
            cin >> Cas[i].dir >> Cas[i].per >> Cas[i].ver >> Cas[i].a >> Cas[i].b;
            Aim_ans(Cas[i].dir,Cas[i]);
            M[Cas[i].a][Cas[i].b] = true;
       }     
    for(int j = 1;j <=energy+1;++j)
        Shoot(j);  
    key = BFS();
    if(!key)
        cout << "Bad luck!" << endl;
    else
        cout << ans-1 << endl;
    }
    return 0;
}