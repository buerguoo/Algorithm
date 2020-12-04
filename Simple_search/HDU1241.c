#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXN 100

int n,m;
int x,y,k = 0;
char grids[MAXN][MAXN];
int jud[MAXN][MAXN];

int Tra();

typedef struct QNode{
    int x,y;
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

int EnQueue(int x,int y)
{
    QNode *q = (QNode*)malloc(sizeof(QNode));
    if(!q) exit(0);
    q->x = x;
    q->y = y;
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
    Q.front->next = p->next;
    if(Q.rear == p) Q.rear = Q.front;
    free(p);
    return 0;
}

int Step()
{
    int x1[8] = {1,0,-1,0,1,1,-1,-1};
    int y1[8] = {0,1,0,-1,1,-1,1,-1};
    int i = 0,tempx = 0,tempy = 0;
    for(i = 0;i < 8;i++)
    {
        tempx = x + x1[i];
        tempy = y + y1[i];
        if(tempx >= 0 && tempy >= 0 && tempx < n && tempy < m && !jud[tempx][tempy]
           && grids[tempx][tempy] == '@')
        {
            jud[tempx][tempy] = 1;
            EnQueue(tempx,tempy);
        }
    }
    return 0;
}

int Bfs()
{
    int key = 0;
    while(1)
    {
        key = DeQueue();
        if(key == -1)
           {
             Tra();
             return 0;
           }
        Step();
    }
    return 0;
}

int Tra()
{
    int i,j;
    for(i = 0;i < n;i++)
        {
            for(j = 0;j < m;j++)
                {
                    if(!jud[i][j] && grids[i][j] == '@')
                    {
                        EnQueue(i,j);
                        jud[i][j] = 1;
                        Bfs();
                        k++;
                    }
                }
        }
        return k;

}

int main()
{
    int i,j;
    int key = 0;
    while(1){
        scanf("%d %d",&n,&m);
        getchar();
        if(n == 0)
            break;
        InitQueue();
        memset(jud,0,sizeof(jud));
        k = 0;
        for(i = 0;i < n;i++)
        {
            for(j = 0;j < m;j++)
                scanf("%c",&grids[i][j]);
            getchar();
        }
        key = Tra();
        printf("%d\n",key);
        }
}
