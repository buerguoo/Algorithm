#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define MAXN 101
int count_cas,energy,m,n,ans;
int dier[2][5] = {{1,0,0,-1,0},{0,1,0,0,-1}};
bool vis_but[MAXN][MAXN][MAXN*10+1],M[MAXN][MAXN];
bool vis[MAXN][MAXN][MAXN*10];

struct Cast
{
    int a,b,per,ver;
    int d;
}Cas[MAXN];

void Aim_ans(Cast &N,char D)
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

bool IDA(int x,int y,int depth,int limit)
{
    //printf("x=%d y=%d t=%d\n",x,y,depth);
    int tx,ty;
    if(depth > limit)
        return false;
    if(x == m && y == n)
        {
            ans = depth;
            return true;}
    for(int i = 0;i < 5;++i)
    {
        tx = x + dier[0][i],ty = y + dier[1][i];
        if(tx < 0 || ty < 0 || tx > m || ty > n || vis_but[tx][ty][depth])
            continue;
        vis[tx][ty][depth+1] = true;
        if(IDA(tx,ty,depth+1,limit))
            return true;
        vis[tx][ty][depth+1] = false;
    }
    return false;
}

int main()
{
    //TEL A*算法中的排序过于耗费时间
    int key;
    char D;
    while(1){
    cin >> m >> n >> count_cas >> energy;
    memset(M,0,sizeof(M));
    for(int i = 0;i < count_cas;++i)
       { 
            cin >> D >> Cas[i].per >> Cas[i].ver >>Cas[i].a >> Cas[i].b;
            Aim_ans(Cas[i],D);
            M[Cas[i].a][Cas[i].b] = true;
       }
    memset(vis_but,0,sizeof(vis_but));
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=energy;++i)
        Shoot(i);
    key = IDA(0,0,1,energy);
    vis[0][0][1] = true;
    if(!key)
        cout << "Bad luck!" << endl;
    else
        cout << ans - 1 << endl;
    }
}