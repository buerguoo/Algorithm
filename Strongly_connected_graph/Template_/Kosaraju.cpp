#include<iostream>
#include<cstring>
using namespace std;
const int MAXN = 20010;
const int MAXM = 50010;
struct Edge{
    int to, next;
}edge1[MAXM], edge2[MAXM];
int head1[MAXN], head2[MAXN], tol1, tol2;
int cnt1, cnt2;
int num; //中间变量，用来记录连通分量的个数
int Belong[MAXN], setNum[MAXN];//Belong属于哪一个连通分量
bool Mark1[MAXN], Mark2[MAXN];
int st[MAXN];   //按结束时间从小到大排序
void addEdge(int u, int v){
    edge1[tol1].to = v;edge1[tol1].next = head1[u];head1[u] = tol1++;
    edge2[tol2].to = u;edge1[tol2].next = head2[v];head2[v] = tol2++;
}
void DFS1(int u)
{
    Mark1[u] = true;
    for(int i = head1[u];i != -1;i = head1[i])
        if(!Mark1[i])
            DFS1(i);
    st[cnt1++] = u;
}
void DFS2(int u){
    Mark2[u] = true;
    num++;
    Belong[u] = cnt2;
    for(int i = head2[u];i != -1;i = head2[i])
        if(!Mark2[u])
            DFS2(i);
}
void solve(int N)
{
    memset(head1, -1, sizeof(head1));
    memset(head2, -1, sizeof(head2));
    memset(Mark1, false, sizeof(Mark1));
    memset(Mark2, false, sizeof(Mark2));
    tol1 = tol2 = 0;
    cnt1 = cnt2 = 0;
    for(int i = 0;i < N;++i)
        if(!Mark1[i])
            DFS1(i);
    for(int i = cnt1-1;i >= 0;--i){
        if(!Mark2[st[i]]){
            num = 0;
            DFS2(st[i]);
            setNum[cnt2++] = num;z
        }
    }
}