#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXN 10000

int prime[MAXN],jud[MAXN];

typedef struct QNode{
    int data;
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

int EnQueue(int e)
{
    QNode *q = (QNode*)malloc(sizeof(QNode));
    if(!q) exit(0);
    q->data = e;
    q->next = NULL;
    Q.rear->next = q;
    Q.rear = q;
    return 0;

}

int DeQueue()
{
    int e = 0;
    if(Q.front == Q.rear) return -1;
    QNode *p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if(Q.rear == p) Q.front = Q.rear;
    free(p);
    return e;
}

void Prime()
{
    memset(prime,0,sizeof(prime));
    for(int i = 1000;i < MAXN;i++)
    {
        for(int j = 2;j <= (int)sqrt(i*1.0);j++)
        {
            if(i%j == 0)
                prime[i] = 1;
        }
    }
}

int Bfs(int begin,int end)
{
    int vtemp,temp,e = 1,t[4];
    InitQueue();
    EnQueue(begin);
    memset(jud,0,sizeof(jud));
    Prime();
    while(1){
    e = DeQueue(Q);
    if(e == -1)
        break;
    t[0] = e / 1000;
    t[1] = e % 1000 / 100;
    t[2] = e % 100 / 10;
    t[3] = e % 10;
    if(e == end)
        return jud[e];
    for(int i = 0;i < 4;i++)
    {
        temp = t[i];
        for(int j = 0;j < 10;j++)
        {
            if(i == 0 && j == 0)
                j++;
            if(j != temp){
            t[i] = j;
            vtemp = t[0]*1000 + t[1]*100 + t[2]*10 + t[3];
            if(!jud[vtemp] && !prime[vtemp])
               {
                   EnQueue(vtemp);
                   jud[vtemp] = jud[e] + 1;
                  //printf("%d %d %d\n",e,vtemp,jud[vtemp]);
               }
            if(vtemp == end)
                 return jud[vtemp];
            }
        }
        t[i] = temp;
    }
    }
    return -1;
}



int main()
{
    int n,begin,end,key;
    scanf("%d",&n);
    for(int i = 0;i < n;i++)
    {
        scanf("%d %d",&begin,&end);
        key = Bfs(begin,end);
        if(key != -1)
            printf("%d\n",key);
        else
            printf("Impossible\n");
    }

}
