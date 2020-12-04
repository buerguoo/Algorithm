#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXN 101

int n,m,s;
int x,y;
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
    int i;
    int tempx = x,tempy = y;
    for(i = 0;i < 6;i++)
    {
        switch(i){
    case 0:
        x = 0;
        break;
    case 1:
        y = 0;
        break;
    case 2:
        x = n;
        break;
    case 3:
        y = m;
        break;
    case 4:
        if(x >= m-y)
        {
            x = x - m + y;
            y = m;
        }
        else
        {
            y = y + x;
            x = 0;
        }
        break;
    case 5:
        if(y >= n-x)
        {
            y = y - n + x;
            x = n;
        }
        else
        {
            x = y + x;
            y = 0;
        }
        break;
        }
        if(!jud[x][y])
        {
            EnQueue(x,y);
            jud[x][y] = jud[tempx][tempy] + 1;
            /*printf("%d %d Q=%d %d %d H=%d\n",tempx,tempy,jud[tempx][tempy],x,y,jud[x][y]);*/
        }
        x = tempx;
        y = tempy;
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
            return -1;
        if(x == s / 2 || y == s / 2)
            return jud[x][y];
        Step();
    }
    return 0;
}



int main()
{
    int key = 0;
    while(1){
        scanf("%d %d %d",&s,&n,&m);
        getchar();
        if(n == 0)
            break;
        if(s % 2 == 1)
        {
            printf("NO\n");
            continue;
        }
        if(n == s / 2)
        {printf("1\n");
        continue;}
        InitQueue();
        memset(jud,0,sizeof(jud));
        EnQueue(0,0);
        key = Bfs();
        if(key == -1)
            printf("NO\n");
        else
            printf("%d\n",key);

}
}
