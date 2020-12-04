#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int maze[5][5],note[20][2];
double node[5][5];
int x,y;

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
    int x1[4] = {1,0,-1,0};
    int y1[4] = {0,1,0,-1};
    int i = 0,tempx = 0,tempy = 0;
    for(i = 0;i < 4;i++)
    {
        tempx = x + x1[i];
        tempy = y + y1[i];
        if(tempx >= 0 && tempy >= 0 && tempx < 5 && tempy < 5 && !maze[tempx][tempy])
        {
            maze[tempx][tempy] = 1;
            node[tempx][tempy] = x + y * 1.0 / 10;
            EnQueue(tempx,tempy);
        }
    }
    return 0;
}

int Bfs()
{
    int key = 0;
    EnQueue(0,0);
    maze[0][0] = 1;
    while(1)
    {
        key = DeQueue();
        if(key == -1)
            return -1;
        if(x == 4 && y == 4)
            return 0;
        Step();
    }
    return 0;
}

int main()
{
    int i=0,j=0;
    int key = 0,k = 0;
    int tempx = 0,tempy = 0;
    InitQueue();
    for(i = 0;i < 5;i++)
    {
        for(j = 0;j < 5;j++)
            scanf("%d",&maze[i][j]);
        getchar();
    }
    key = Bfs();
    if(!key){
        while(x+y>0){
            note[k][0] = x;
            note[k][1] = y;
            tempx = (int)node[x][y];
            tempy = (int)(node[x][y]*10) % 10;
            x = tempx;
            y = tempy;
            k++;
        }
        note[k][0] = 0;
        note[k][1] = 0;
        for(;k >= 0;k--)
            printf("(%d, %d)\n",note[k][0],note[k][1]);
    }
}