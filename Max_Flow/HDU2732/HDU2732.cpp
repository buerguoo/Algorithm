/*
Time limit:1000ms
Memory limit:32768Kb

Author:buerguoo
Time:46ms
memory:5416KB

Data:2021-03-24 13:18:32	
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
const int MAXN = 1010;
const int MAXM = 100010;
int dis[MAXN], cur[MAXN], pre[MAXN], gap[MAXN];
int G[MAXN][MAXN];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; 
int sap(int s, int t, int nodenum)
{
    memset(dis, 0, sizeof(dis));
    memset(cur, 0, sizeof(cur));
    memset(gap, 0, sizeof(gap));
    int u = pre[s] = s;
    int maxflow = 0, aug = -1;
    gap[0] = nodenum;
    while(dis[s] < nodenum){
        loop:
            for(int v = cur[u];v < nodenum;++v)
                if(G[u][v] && dis[u] == dis[v] + 1){
                    if(aug == -1 || aug > G[u][v]) aug = G[u][v];
                    pre[v] = u;
                    u = cur[u] = v;
                    if(v == t){
                        maxflow += aug;
                        for(u = pre[u];v != s;v = u, u = pre[u]){
                            G[u][v] -= aug;
                            G[v][u] += aug;
                        }
                        aug = -1;
                    }
                    goto loop;
                }
        int mindis = nodenum - 1;
        for(int v = 0;v < nodenum;++v)
            if(G[u][v] && mindis > dis[v]){
                mindis = dis[v];
                cur[u] = v;
            }
        if(--gap[dis[u]] == 0) break;
        gap[dis[u] = mindis+1]++;
        u = pre[u];
    }
    return maxflow;
}
int T,s,t,N,d,n,m;
bool judge(int i,int j){
	if(i>=0&&i<n&&j>=0&&j<m) return 1;
	else return 0;
}
char p[25][25], l[25][25];
int id[25][25], pnum, lnum;
int main(int argc, char** argv) {
	cin>>T;
	int kase=0;
	while(T--){
		scanf("%d%d",&n,&d);
		for(int i = 0;i<n;++i) scanf("%s",p[i]);
		for(int i = 0;i<n;++i) scanf("%s",l[i]);
		m = strlen(p[0]);
		pnum=lnum=0;
		for(int i = 0;i<n;++i){
			for(int j = 0;j<m;++j){
				if(l[i][j]=='L')	lnum++;//统计蜥蜴的个数 
				if(p[i][j]-'0')	id[i][j]=pnum++;//给每个柱子编号 
			}
		}
		s=2*pnum,t=2*pnum+1,N=2*pnum+2;//超级源点，超级汇点和点的总数 
		memset(G,0,sizeof(G));
		for(int i = 0;i<n;++i){
			for(int j = 0;j<m;++j){
				int num=p[i][j]-'0';
				if(num){
					if(l[i][j]=='L') G[s][id[i][j]]=1;//如果当前点有蜥蜴，那么源点和当前点建立一条边，容量为 1 ，表示有一只蜥蜴 
					G[id[i][j]][pnum+id[i][j]]=num;//拆点，入点和出点连边，容量为高度，限制蜥蜴的最大跳跃数 
					int flag=0;
				for(int xd=-d;xd<=d;xd++){//枚举坐标 
					for(int yd=abs(xd)-d;yd<=d-abs(xd);yd++){
							if(judge(i+xd,j+yd)&&(p[i+xd][j+yd]-'0'))//如果当前点蜥蜴可以蹦到另一个点
									//那么两点连一条边，容量为当前点的高度，表示最多能有多少只青蛙可以跳到另一个点 
								G[pnum+id[i][j]][id[i+xd][j+yd]]=num;
							if(!judge(i+xd,j+yd)) flag=1;
						}
					if(flag) G[pnum+id[i][j]][t]=num;//当前点如果能跳出界，那么和汇点连一条边，容量为当前点的高度，表示最多能有多少只蜥蜴跳出去。 
					}
				}
			} 
		}
		int left=lnum-sap(s,t,N);//求出最大流 
		if(left==0) printf("Case #%d: no lizard was left behind.\n",++kase);
		else if(left==1) printf("Case #%d: 1 lizard was left behind.\n",++kase);
		else printf("Case #%d: %d lizards were left behind.\n",++kase,left);
	}
	return 0;
}