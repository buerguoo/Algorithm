#include<iostream>
#include<cstring>
using namespace std;
const int MAXN = 20010;//����
const int MAXM = 50010;//����
struct Edge{
    int to, next;
}edge[MAXM];
int Low[MAXN], DFN[MAXN], Stack[MAXN], Belong[MAXN]; //Belong�����ֵ��1 ~ SCC
int Index, top;
int scc;//ǿ��ͨ�����ĸ���
bool Instack[MAXN];
int num[MAXN];//������ͨ����������ĸ�����������1 ~ scc
//num ���鲻һ����Ҫ�����ʵ�����
int head[MAXN], tol;
void addEdge(int u, int v){
    edge[tol].to = v; edge[tol].next = head[u]; head[u] = tol++;
}
void Tarjan(int u){
    int v;
    DFN[u] = Low[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u];i != -1;i = edge[i].next){
        v = edge[i].to;
        if(!DFN[v]){
            Tarjan(v);
            if(Low[u] > Low[v]) Low[u] = Low[v];
        }
        else if(Instack[v] && Low[u] > DFN[v])
            Low[u] = DFN[v];
    }
    if(Low[u] = DFN[u]){
        scc++;
        do{
            v = Stack[top--];
            Instack[v] = false;
            Belong[v] = scc;
            num[scc]++;
        }while(v != u);
    }
}

void solve(int N){
    memset(DFN, 0, sizeof(DFN));
    memset(Instack, false, sizeof(Instack));
    memset(num, 0, sizeof(num));
    Index = scc = 0;
    for(int i = 0;i < N;++i)
        if(!DFN[i])
            Tarjan(i);
}

void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
}