#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXN 10

int x,y,t = 0;
int n,m;
char grids[MAXN][MAXN];
int ch[MAXN][MAXN],co[MAXN*MAXN][2],ch1[MAXN][MAXN];


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

int Fire()
{
    int x1[5] = {1,0,-1,0,0};
    int y1[5] = {0,1,0,-1,0};
    int tempx,tempy,temp;
    for(int i = 0;i < 5;i++)
    {
        tempx = x + x1[i];
        tempy = y + y1[i];
        if(tempx >= 0 && tempy >= 0 && tempx < n && tempy < m && !ch[tempx][tempy])
            {
                EnQueue(tempx,tempy);
                ch[tempx][tempy] = ch[x][y] + 1;
                temp = ch[tempx][tempy];
                //printf("ch[%d][%d]=%d ch[%d][%d]=%d\n",x,y,ch[x][y],tempx,tempy,ch[tempx][tempy]);
            }
    }
    return temp;
}

void Back()
{
    for(int i= 0;i < n;i++)
    {
        for(int j = 0;j < n;j++)
            ch[i][j] = ch1[i][j];
    }
}

int Jud()
{
    for(int i= 0;i < n;i++)
    {
        for(int j = 0;j < n;j++)
            {
                //printf("");
                if(!ch[i][j])
                    return 0;
            }
    }
    return 1;
}

int Bfs()
{
    int key,temp,min = 1000;
    int ch1,ch2;
    InitQueue();
    for(int i = 0;i <= (t+1)/2;i++){
        for(int j = i+1;j < t;j++){
            Back();
            EnQueue(co[i][0],co[i][1]);
            EnQueue(co[j][0],co[j][1]);
            while(1){
                key = DeQueue();
                ch1 = Fire();
                key = DeQueue();
                ch2 = Fire();
                if(key == -1)
                {
                    if(ch1 >= ch2)
                        temp = ch1;
                    else
                        temp = ch2;
                    break;
                }
            }
            //printf("%d %d %d\n",i,j,min);
            if(temp < min && Jud())
                min = temp;
        }

    }
    if(min == 1000)
        return -1;
    return min;
}

int main()
{
    int p;
    int k = 0,key;
    scanf("%d",&p);
    while(k < p){
        scanf("%d %d",&n,&m);
        getchar();
        memset(ch1,-1,sizeof(ch));
        memset(co,0,sizeof(co));
        t = 0;
        for(int i = 0;i < n;i++)
        {
            for(int j = 0;j < m;j++)
            {
                scanf("%c",&grids[i][j]);
                if(grids[i][j] == '#')
                   {
                       co[t][0] = i;
                       co[t][1] = j;
                       ch1[i][j] = 0;
                       t++;
                   }
            }
            getchar();
        }
        k++;
        if(t <= 2)
           {
               printf("Case %d:0\n",k);
               continue;
           }
        key = Bfs();
        printf("Case %d:%d\n",k,key);
    }
    return 0;
}
