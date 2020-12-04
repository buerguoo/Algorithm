#include <cstring>
#include <iostream>
#include <cstdio>
#include <queue>
#include<algorithm>
using namespace std;
#define MAXN 110
int count_cas,energy,m,n;
int dier[2][5] = {{1,0,0,-1,0},{0,1,0,0,-1}};
bool vis_but[MAXN][MAXN][1010],vis[MAXN][MAXN][1010],M[MAXN][MAXN];

struct Node
{
    int x,y,h,g;
    
    bool operator<(const Node c) const{
       return  h + g >= c.h + c.g;
    } 

    int get_hash()
    {
        h = abs(m-x) + abs(n-y);
        return h;
    }
};

struct Cast
{
    char dir;
    int a,b,per,ver;
    int d;
}Cas[MAXN];

void Aim_ans(char D,Cast &Cas)
{
    
        switch (D)
        {
        case 'N':
        Cas.d = 3;
            break;
        case 'S':
        Cas.d = 0;
            break;
        case 'E':
        Cas.d = 1;
            break;
        case 'W':
        Cas.d = 4;
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

int Bfs_A()
{
    priority_queue<Node> Q;
    Node a,next;
    int t = 0,tx,ty;
    a.g = 1; a.x = 0; a.y = 0; a.get_hash();
    vis[a.x][a.y][a.g-1] = true;
    Q.push(a);
    while(!Q.empty()){
        a = Q.top();
        Q.pop();
        t = a.g;
        if(a.x == m && a.y == n)
            return a.g-1;
        if(a.g-1 > energy)
            return -1;
        for(int i = 0;i < 5;i++)
        {
            tx = a.x + dier[0][i],ty = a.y + dier[1][i];
            if(tx >= 0 && ty >= 0 && tx <= m && ty <= n && !vis_but[tx][ty][t] 
            && !vis[tx][ty][t] && !M[tx][ty])
            {
                
                vis[tx][ty][t] = true;
                next.x = tx,next.y = ty;
                next.g = a.g + 1;
                next.get_hash();
                Q.push(next);
            }
        }
    }
    return -1;
}

int main()
{
    //AC 280ms
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
    key = Bfs_A();
    if(key == -1)
        cout << "Bad luck!" << endl;
    else
        cout << key << endl;
    }
    return 0;
}