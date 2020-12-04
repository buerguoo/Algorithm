#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  MAXN 20

int m,n;
int triple[MAXN][MAXN];
int book[MAXN][MAXN];
int ans[MAXN][MAXN];
int chx[5] = {0,1,-1,0,0};
int chy[5] = {0,0,0,1,-1};
int min = 10000,count;

void turn(int x,int y,int z)
{
    int cx,cy;
    if(!z)
        book[x][y]++;
    for(int i = 0; i < 5; i++)
    {
        cx = x;
        cy = y;
        cx += chx[i];
        cy += chy[i];
        if(cx >= 0 && cy >= 0 && cx < m && cy < n)
            triple[cx][cy] = (triple[cx][cy] + 1) % 2;
    }
}

void back()
{
    count = 0;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            count += book[i][j];
            if(book[i][j])
                turn(i,j,1);
        }
    }
}

void save()
{
    if(count < min){
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
            ans[i][j] = book[i][j];
    }
    min = count;
    }
}

//深度搜索寻找可用的方法
int dfs()
{
    int count = 0;
    if(m == 1)
    {
        for(int j = 0; j < n; j++)
            count += triple[0][j];
    }
    for(int i = 1; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(triple[i-1][j] == 1)
                turn(i,j,0);
        }
        if(i == m-1)
        {
            for(int j = 0; j < n; j++)
                count += triple[i][j];
        }
    }
    back();
    if(!count)
        return 1;
    return 0;
}

//穷举第一行的情况2^M*N
void enu()
{
    int i,j;
    for(i = 0; i < 1<<m; i++)
    {
        memset(book,0,sizeof(book));
        for(j = 0; j < m; j++)
            {
                book[0][j] = i>>j & 1;
                if(book[0][j] == 1)
                    turn(0,j,2);
            }
        if(dfs())
            save();
    }
}



int main()
{
    memset(ans,0,sizeof(ans));
    scanf("%d %d",&m,&n);
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
            scanf("%d",&triple[i][j]);
        getchar();
    }
    enu();
    if(min == 10000)
        printf("IMPOSSIBLE\n");
    else
    {
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
                printf("%d ",ans[i][j]);
            printf("\n");
        }
    }
    return 0;
}
