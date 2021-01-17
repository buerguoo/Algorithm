#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;
const int MAXN = 20010;//µãÊý
const int MAXM = 50010;//±ßÊý
struct Edge{
    int to, next;
}edge[MAXM];
int head[MAXN], tol;
void addEdge(int u, int v){
    edge[tol].to = v; edge[tol].next = head[u]; head[u] = tol++;
}

int main()
{
    int u, v;
    memset(head, -1, sizeof(head));
    for(int i = 0;i < 5;++i){
        scanf("%d%d", &u, &v);
        addEdge(u, v);
    }
    for(int i =  head[1];i != -1;i = edge[i].next)
        printf("i=%d to=%d next=%d\n",i, edge[i].to, edge[i].next);
    return 0;
}