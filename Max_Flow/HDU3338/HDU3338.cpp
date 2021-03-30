/*
Time limit:
Memory limit:

Author:buerguoo
Time:
memory:

Data:
*/
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 2010;
int dis[MAXN], cur[MAXN], pre[MAXN], gap[MAXN];
int maze[MAXN][MAXN], G[MAXN][MAXN];
struct black{
    int x, y, val, ind;
    bool type;
    black(int _x, int _y, int _v, int _i, bool _t):x(_x), y(_y), val(_v), ind(_i), type(_t){}
};
int sap(int s, int t, int nodenum)
{
    memset(dis, 0, sizeof(dis));
    memset(cur, 0, sizeof(cur));
    memset(gap, 0, sizeof(gap));
    gap[0] = nodenum;
    int u = pre[s] = s;
    int maxflow = 0, aug = -1;
    while(dis[s] < nodenum){
        loop:
            for(int v = cur[u];v < nodenum;v++){
                if(maze[u][v] && dis[u] == dis[v] + 1){
                    if(aug == -1 || aug > maze[u][v]) aug = maze[u][v];
                    pre[v] = u;
                    u = cur[u] = v;
                    if(v == t){
                        maxflow += aug;
                        for(u = pre[u]; v != s;v = u, u = pre[u]){
                            maze[u][v] -= aug;
                            maze[v][u] += aug;
                        }
                        aug = -1;
                    }
                    goto loop;
                }
            }
        int mindis = nodenum - 1;
        for(int v = 0;v < nodenum;++v)
            if(maze[u][v] && mindis > dis[v]){
                mindis = dis[v];
                cur[u] = v;
            }
        if(!(--gap[dis[u]])) break;
        gap[dis[u] = mindis+1]++;
        u = pre[u];
    }
    return maxflow;
}
int id[100][100];
queue<black> Q;
int rnum, bnum;
bool isNum(char c)
{
    if(c < '0' || c > '9')
        return false;
    
    return true;
}
void to(char *p, int x, int y)
{
    int res = 0;
    if(isNum(p[0])){
        for(int i = 0;i < 3;++i)
            res = res * 10 + (p[i] - '0');
        Q.push(black(x, y, res, ++bnum, false));
    }else if(p[0] == '.') id[x][y] = ++rnum;
    res = 0;
    if(isNum(p[4])){
        for(int i = 4;i < 7;++i)
            res = res * 10 + (p[i] - '0');
        Q.push(black(x, y, res, ++bnum, true));
    }   
}
int main()
{
    int n, m;
    char p[8];
    while(~scanf("%d %d", &n, &m)){
        memset(id, 0, sizeof(id));
        memset(maze, 0, sizeof(maze));
        while(!Q.empty()) Q.pop();
        rnum = bnum = 0;
        for(int i = 0;i < n;++i)
            for(int j = 0;j < m;++j){
                scanf("%s", p);
                to(p, i, j);
            }
        int s = 0, t = rnum+bnum+1;
        while(!Q.empty()){
            black tmp = Q.front();
            Q.pop();
            int count = 0;
            if(!tmp.type){
                int j = tmp.y;
                for(int i = tmp.x+1;i < n;++i)
                    if(id[i][j]){
                        maze[id[i][j]][rnum+tmp.ind] = 8;
                        maze[rnum+tmp.ind][id[i][j]] = -8;
                        count++;
                    }else  break;
                for(int i = tmp.x+1;i < n;++i)
                    if(id[i][j]){
                        maze[rnum+tmp.ind][t] = tmp.val-count;
                        maze[t][rnum+tmp.ind] = count-tmp.val;
                    }else  break;   
            }else{
                int i = tmp.x;
                for(int j = tmp.y+1;j < m;++j)
                    if(id[i][j]){
                        maze[id[i][j]][rnum+tmp.ind] = -8;
                        maze[rnum+tmp.ind][id[i][j]] = 8;
                        count++;
                    }else break;
                for(int j = tmp.y+1;j < m;++j)
                    if(id[i][j]){
                        maze[s][rnum+tmp.ind] = tmp.val-count;
                        maze[rnum+tmp.ind][s] = count-tmp.val;
                    }else break;
            }
        }
        memcpy(G, maze, sizeof(G));
        sap(s, t, rnum+bnum+2);
        for(int i = 0;i < n;++i){
            for(int j = 0;j < m;++j)    if(id[i][j]){
                for(int k = rnum;k < rnum+bnum+1;++k) if(G[id[i][j]][k]){
                    //printf("G = %d maze = %d\n", G[id[i][j]][k], maze[id[i][j]][k]);
                    printf("%d ", G[id[i][j]][k] - maze[id[i][j]][k] + 1);
                    break;
                }
            }else printf("- "); 
            printf("\n");
            }
    }
    return 0;
}