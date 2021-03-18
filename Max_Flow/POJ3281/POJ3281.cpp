/*
Author:buerguoo
Time:
memory:
WA
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
const int INF = 0x3f3f3f3f;
const int MAXN = 110;
const int MAXM = 110;
int dx[MAXN], dy[MAXM], Mx[MAXN], My[MAXN];
int x[MAXN], y[MAXN];
vector<int> G[MAXN];
bool used[MAXN];
int uN,  dis;
bool bfs(){
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    dis = INF;
    queue<int> Q;
    for(int i = 0;i < uN;++i)
        if(Mx[i] == -1){
          Q.push(i);
          dx[i] = 0;
        } 
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        if(dx[u] > dis) continue;
        int sz = G[u].size();
        for(int i = 0;i < sz;++i){
            int v = G[u][i];
            if(dy[v] == -1){
                dy[v] = dx[u] + 1;
                if(My[v] == -1) dis = dy[v];
                else{
                    dx[My[v]] = dy[v] + 1;
                    Q.push(My[v]);
                }
            }
        }
    }
    return dis != INF;
}
bool dfs(int u){
    int sz = G[u].size();
    for(int i = 0;i < sz;++i){
        int v = G[u][i];
        if(!used[v] && dx[u] + 1 == dy[v]){
            used[v]= true;
            if(My[v] != -1 && dy[v] == dis) continue;
            if(My[v] == -1 || dfs(My[v])){
                My[v] = u;
                Mx[u] = v;
                return true;
            }
        }
    }
    return false;
}
int Maxmatch(){
    int res = 0;
    memset(My, -1, sizeof(My));
    memset(Mx, -1, sizeof(Mx));
    while(bfs()){
        memset(used, false, sizeof(used));
        for(int i = 0;i < uN;++i){
            if(Mx[i] == -1 && dfs(i))   res++;
        }
    }
    
        
    return res;
}
int main() {
	int N, F, D;
	scanf("%d %d %d", &N, &F, &D);
	uN = F;
	int n, m;
	while(N--){
	    scanf("%d %d", &n, &m);
	    for(int i = 0;i < n;++i)
	        scanf("%d", &x[i]);
	    for(int i = 0;i < m;++i)
	        scanf("%d", &y[i]);
	    for(int i = 0;i < n;++i)
	        for(int j = 0;j < m;++j)
	            G[x[i]-1].push_back(y[j]-1);
	}
	printf("%d\n", Maxmatch());
	return 0;
}