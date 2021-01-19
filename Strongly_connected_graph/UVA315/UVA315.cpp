/*
Author:buerguoo
Time:
memory:

Data:
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
#define FILL(a, b)  memset(a, b, sizeof(a))
typedef long long ll;
const int MAXN = 110;
const int MAXM = 10010;
const int INF = 0x3f3f3f3f;
int DFN[MAXN], Low[MAXN], Stack[MAXN], Belong[MAXN], head[MAXN];
int Index, tol, top, bridge;
bool Instack[MAXN], cut[MAXN];
int add_block[MAXN];   //ɾ��һ��������ӵ���ͨ��
//����
struct Edge{
    int to, next;
    bool cut;//�����
}E[MAXM];
void addEdge(int u, int v)
{
    E[tol].to = v;
    E[tol].cut = false;
    E[tol].next = head[u];
    head[u] = tol++;
}
void Tarjan(int u, int pre)
{
    int v;
    DFN[u] = Low[u] = Index++;
    Stack[tol++] = u;
    Instack[u] = true;
    int son = 0;    //��������һuΪ�����ж���һ��������
    for(int i = head[u];i != -1;i = E[i].next)
    {
        v = E[i].to;
        if(v == pre)    continue;
        if(!DFN[i]){
            Tarjan(v, u);
            if(Low[u] > Low[v]) Low[u] = Low[v];
            //��
            //һ�������(u,v)���ţ����ҽ���(u,v)Ϊ��֦�ߣ�������DFS(u)<Low(v)��
            if(Low[v] > DFN[u]){
                bridge++;
                E[i].cut = true;
                E[i^1].cut = true;
            }
             //���
            //һ������u�Ǹ�㣬���ҽ�������(1)��(2) (1) uΪ��������u�ж���һ��������
            //(2) u��Ϊ���������������(u,v)Ϊ��֦��(��Ƹ��ӱߣ�
            //��uΪv���������еĸ���)��ʹ��DFS(u)<=Low(v)
            if(u != pre && DFN[u] <= Low[v]){
                cut[u] = true;
                add_block[u]++;
            }
        }
        else if(Low[u] > DFN[v])
            Low[u] = DFN[v];
    }
    if(u == pre && son > 1) cut[u] = true;
    if(u == pre) add_block[u] = son - 1;
    Instack[u] = false;
    top--;
}
void solve(int N)
{
    memset(DFN, 0, sizeof(DFN));
    memset(Instack, false, sizeof(Instack));
    memset(cut, false, sizeof(cut));
    memset(add_block, 0, sizeof(add_block));
    top = Index = 0;
    bridge = 0;
    for(int i = 1;i <= N;++i)
        if(!DFN[i])
            Tarjan(i, i);
    int ans = 0;
    for(int i = 1;i <= N;++i)
        if(cut[i]) ans++;
    printf("%d\n", ans);
}
void init()
{
    memset(head, -1, sizeof(head));
    tol = 0;
}
int g[110][110];
char buf[1010];
int main()
{
    int n;
    while(scanf("%d",&n)==1 && n)
    {
        gets(buf);
        memset(g,0,sizeof(g));
        while(gets(buf))
        {
            if(strcmp(buf,"0")==0)break;
            char *p = strtok(buf," ");
            int u;
            sscanf(p,"%d",&u);
            p = strtok(NULL," ");
            int v;
            while(p)
            {
                sscanf(p,"%d",&v);
                p = strtok(NULL," ");
                g[u][v]=g[v][u]=1;
            }
        }
        init();
        for(int i = 1;i <= n;i++)
           for(int j = i+1;j <= n;j++)
              if(g[i][j])
              {
                  addEdge(i,j);
                  addEdge(j,i);
              }
        solve(n);
    }
    return 0;
}