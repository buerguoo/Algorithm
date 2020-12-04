#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXN 1010

int jud[MAXN][MAXN];
char grids[MAXN][MAXN];
int x,y,n,m;
int count = 1,count1 = 0;

int Fire();

typedef struct QNode{
    int x,y;
    struct QNode *next;
}QNode;

typedef struct {
    QNode *front;
    QNode *rear;
}Queue;

Queue Q,Q1;

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

int InitQueue1()
{
    Q1.front = (QNode*)malloc(sizeof(QNode));
    Q1.rear = Q1.front;
    if(!Q1.front) exit(0);
    Q1.front->next = NULL;
    return 0;
}

int EnQueue1(int x,int y)
{
    QNode *q = (QNode*)malloc(sizeof(QNode));
    if(!q) exit(0);
    q->x = x;
    q->y = y;
    q->next = NULL;
    Q1.rear->next = q;
    Q1.rear = q;
    return 0;

}

int DeQueue1()
{
    if(Q1.front == Q1.rear) return -1;
    QNode *p = Q1.front->next;
    x = p->x;
    y = p->y;
    Q1.front->next = p->next;
    if(Q1.rear == p) Q1.rear = Q1.front;
    free(p);
    return 0;
}


int Run()
{
    int co = count;
    int i;
    count = 0;
    while(co-- > 0){
    DeQueue();
    if(jud[x][y] == -1)
        continue;
    if(x == 0 || y == 0 || x == n-1 || y == m-1)
        return 1;
    int x1[4] = {1,0,-1,0};
    int y1[4] = {0,1,0,-1};
    int tempx,tempy;
    for(i = 0;i < 4;i++)
    {
        tempx = x + x1[i];
        tempy = y + y1[i];
        if(tempx >= 0 && tempy >=0
           && tempx < n && tempy < m && grids[tempx][tempy] == '.' && !jud[tempx][tempy])
        {
            count++;
            EnQueue(tempx,tempy);
            jud[tempx][tempy] = jud[x][y] + 1;
        }
    }
    }
    return 0;
}

int Fire()
{
    int co1 = count1;
    int i;
    count1 = 0;
    while(co1-- > 0){
    DeQueue1();
    int x1[4] = {1,0,-1,0};
    int y1[4] = {0,1,0,-1};
    int tempx,tempy;
    for(i = 0;i < 4;i++)
    {
        tempx = x + x1[i];
        tempy = y + y1[i];
        if(tempx >= 0 && tempy >=0
           && tempx < n && tempy < m && grids[tempx][tempy] == '.' && jud[tempx][tempy] != -1 )
            {
                count1++;
                EnQueue1(tempx,tempy);
                jud[tempx][tempy] = -1;
            }
    }
    }
    return 0;
}

int Bfs()
{
    int k = 0;
    while(1){
        k = Run();
        if(k == 1)
            return 1;
        Fire();
        if(!count)
            return 0;
    }
}

int main()
{
    int p,i,j;
    int k = 0,key;
    scanf("%d",&p);
    while(k < p){
        count1 = 0;
        count = 0;
        scanf("%d %d",&n,&m);
        getchar();
        memset(jud,0,sizeof(jud));
        InitQueue();
        InitQueue1();
        for(i = 0;i < n;i++)
        {
            for(j = 0;j < m;j++)
            {
                scanf("%c",&grids[i][j]);
                if(grids[i][j] == 'J')
                    {
                        EnQueue(i,j);
                        count++;
                        jud[i][j] = 1;
                    }
                else if(grids[i][j] == 'F')
                   {
                       EnQueue1(i,j);
                       count1++;
                       jud[i][j] = -1;
                   }
            }
            getchar();
        }
        k++;
        key = Bfs();
        if(!key)
            printf("IMPOSSIBLE\n");
        else
            printf("%d\n",jud[x][y]);
    }
    return 0;
}
