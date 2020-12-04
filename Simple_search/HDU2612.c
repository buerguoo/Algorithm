#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXN 210

int n,m;
int x,y,z;
int jud[2][MAXN][MAXN];
char grids[MAXN][MAXN];

typedef struct QNode{
    int x,y,z;
    struct QNode *next;
}QNode;

typedef struct {
    QNode *front;
    QNode *rear;
}Queue;

Queue Q;

int InitQueue()
{
    Q.front = (QNode*)malloc(sizeof(QNode));
    Q.rear = Q.front;
    if(!Q.front) exit(0);
    Q.front->next = NULL;
    return 0;
}

int EnQueue(int x,int y,int z)
{
    QNode *q = (QNode*)malloc(sizeof(QNode));
    if(!q) exit(0);
    q->x = x;
    q->y = y;
    q->z = z;
    q->next = NULL;
    Q.rear->next = q;
    Q.rear = q;
    return 0;

}

int DeQueue()
{
    if(Q.front == Q.rear) return -1;
    QNode *p = Q.front->next;
    x = p->x;
    y = p->y;
    z = p->z;
    Q.front->next = p->next;
    if(Q.rear == p) Q.rear = Q.front;
    free(p);
    return 0;
}

void Step()
{
    int x1[4] = {0,1,0,-1};
    int y1[4] = {1,0,-1,0};
    int tx,ty,i = 0;
    for(i = 0;i < 4;i++)
    {
        tx = x + x1[i];
        ty = y + y1[i];
        if(tx >= 0 && ty >= 0 && tx < n && ty < m && !jud[z][tx][ty]
           ){if(grids[tx][ty] == '.' || grids[tx][ty] == '@')
                {EnQueue(tx,ty,z);
                jud[z][tx][ty] = jud[z][x][y] +1;}
        }
    }
}

int Min()
{
    int i,j;
    int min = 1061109567;
    for(i = 0;i < n;i++)
    {
        for(j = 0;j < m;j++)
        {
            if(grids[i][j] == '@' && min > jud[0][i][j]+jud[1][i][j] && jud[0][i][j] && jud[1][i][j])
                min = jud[0][i][j]+jud[1][i][j];

        }
    }
    return min;
}

int Bfs()
{
    int key = 0;
    while(1){
        key = DeQueue();
        if(key == -1)
            return Min();
        Step();
    }
    return 0;
}



int main()
{
    int i=0,j=0;
    int key = 0;
    while(scanf("%d %d",&n,&m) != EOF){
        getchar();
        InitQueue();
        memset(jud,0,sizeof(jud));
        for(i = 0;i < n;i++)
        {
            for(j = 0;j < m;j++)
                {
                scanf("%c",&grids[i][j]);
                if(grids[i][j] == 'Y')
                EnQueue(i,j,0);
                if(grids[i][j] == 'M')
                EnQueue(i,j,1);
                }
                getchar();

        }
        key = Bfs();
        printf("%d\n",key*11);
    }
    return 0;
}
