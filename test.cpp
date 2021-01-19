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
const int MAXN = 105;
const int MAXM = MAXN*MAXN;
const int INF = 0x3f3f3f3f;
int Index, scc, top, tol;
int DFN[MAXN], Low[MAXN], Belong[MAXN], Stack[MAXN], head[MAXN];
bool Instactk[MAXN];
int cd[MAXN], rd[MAXN];
struct Edge{
    int to, next;
}E[MAXM];
void addEdge(int u, int v)
{
    E[tol].to = v;
    E[tol].next = head[u];
    head[u] = tol++;
}
void Tarjan(int u)
{
    int v;
    DFN[u] = Low[u] = ++Index;
    Stack[top++] = u;
    Instactk[u] = true;
    for(int i = head[u];i != -1;i = E[i].next)
    {
        v = E[i].to;
        if(!DFN[v]){
            Tarjan(v);
            if(Low[u] > Low[v]) Low[u] = Low[v];
        }
        else if(Instactk[v] && Low[u] > DFN[v])
            Low[u] = DFN[v];
    }
    if(Low[u] == DFN[u]){
        scc++;
        do{
            v = Stack[--top];
            Instactk[v] = false;
            Belong[v] = scc;
        }
        while(v != u);
    }
}
void solve(int N)
{
    memset(DFN, 0, sizeof(DFN));
    memset(Instactk, false, sizeof(Instactk));
    scc = Index = top = 0;
    for(int i = 1;i <= N;++i) if(!DFN[i])
        Tarjan(i);
}
void init(){
    memset(head, -1, sizeof(head));
    tol = 0;
}
int main()
{
    ifstream infile;
    infile.open("D://input.txt", ios::in);
    int N = 6;
    init();
    int u, v;
    while(!infile.eof()){
        infile >> u >> v;
        addEdge(u, v);
    }
    solve(N);
    printf("%d\n", scc);
    infile.close();
    return 0;
}