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
struct Node{
    int x;
    int y;
    bool operator < (const Node &r) const{
        return (double)x/y > (double)r.x/r.y;
    }
};
double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        priority_queue<Node> Q;
        int sz = classes.size();
        double res = 0;
        Node tmp;
        for(int i = 0;i < sz;++i){
            tmp.x = classes[i][0];
            tmp.y = classes[i][1];
            Q.push(tmp);
        }
        for(int i = 0;i < extraStudents;++i){
            tmp = Q.top();
            Q.pop();
            tmp.x += 1;
            tmp.y += 1;
            Q.push(tmp);
        }
        while(!Q.empty()){
            tmp = Q.top();
            Q.pop();
            res += (double)tmp.x/tmp.y;
        }
        return res/sz;
    }

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