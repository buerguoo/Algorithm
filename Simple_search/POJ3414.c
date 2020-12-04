#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXN 100

int n1,m1,ind;
int n,m,c;
int jud[MAXN][MAXN];
double su[MAXN*2];

typedef struct QNode{
    int n1,m1;
    int ind;
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

int EnQueue(int n1,int m1,int ind)
{
    QNode *q = (QNode*)malloc(sizeof(QNode));
    if(!q) exit(0);
    q->n1 = n1;
    q->m1 = m1;
    q->ind = ind;
    q->next = NULL;
    Q.rear->next = q;
    Q.rear = q;
    return 0;

}

int DeQueue()
{
    if(Q.front == Q.rear) return -1;
    QNode *p = Q.front->next;
    n1 = p->n1;
    m1 = p->m1;
    ind = p->ind;
    Q.front->next = p->next;
    if(Q.rear == p) Q.rear = Q.front;
    free(p);
    return 0;
}

int Bfs()
{
    int key = 0;
    int tempn,tempm,temp;
    int sur = 0;
    memset(jud,0,sizeof(jud));
    InitQueue();
    EnQueue(0,0,0);
    jud[0][0] = 1;
    while(1){
        key = DeQueue();
        if(key == -1)
            return 0;
        tempn = n1;
        tempm = m1;
       // printf("out %d %d %d \n",n1,m1,ind);
        for(int i = 1;i < 7;i++)
        {
            switch(i){
            case 1:
                n1 = 0;
                break;
            case 2:
                m1 = 0;
                break;
            case 3:
                n1 = n;
                break;
            case 4:
                m1 = m;
                break;
            case 5:
                if(n1 >= m - m1)
                {
                    temp = m1;
                    m1 = m;
                    n1 = n1 - m + temp;
                }
                else
                {
                    m1 = m1 + n1;
                    n1 = 0;
                }
                break;
            case 6:
                if(m1 >= n - n1)
                {
                    temp = n1;
                    n1 = n;
                    m1 = m1 - n + temp;
                }
                else{
                    n1 = m1 + n1;
                    m1 = 0;
                }
                break;
            }
          //printf("%d %d %d %d\n",n1,m1,ind*6+i,jud[n1][m1]);
            if(!jud[n1][m1])
               {
                   //printf("in  %d %d %d %lf\n",n1,m1,sur+1,su[sur+1]);
                   EnQueue(n1,m1,++sur);
                   su[sur] = ind + i*1.0/10;
                   jud[n1][m1] = 1;
               }
            if(n1 == c || m1 == c)
                return sur;
            n1 = tempn;
            m1 = tempm;
        }
    }
    return 0;
}

int main()
{
    int key = 0,sur;
    int i = 0;
    char name[100][10];
    scanf("%d %d %d",&n,&m,&c);
    sur = Bfs();
    if(sur == 0)
       {
           printf("impossible\n");
           return 0;
       }
    while(sur > 0){
        key = ((int)(su[sur]*10) % 10);
        switch(key){
            case 1:
                strcpy(name[i],"DROP(1)");
                break;
            case 2:
                strcpy(name[i],"DROP(2)");
                break;
            case 3:
                strcpy(name[i],"FILL(1)");
                break;
            case 4:
                strcpy(name[i],"FILL(2)");
                break;
            case 5:
                strcpy(name[i],"POUR(1,2)");
                break;
            case 6:
                strcpy(name[i],"POUR(2,1)");
                break;
    }
    //printf("%d %d\n",sur,key);
    sur = (int)su[sur];
    i++;
    }
    printf("%d\n",i);
    for(--i;i >= 0;i--)
    {
        printf("%s",name[i]);
        printf("\n");
    }
}
