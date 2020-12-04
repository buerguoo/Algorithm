#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//并查集
const int MAXN = 1100;
int pre[MAXN];

int find(int s)
{
    int root=s, tmp;
    while(pre[root] != root) root = pre[root];
    while (pre[s] != root)
    {
        tmp = pre[s];
        pre[tmp] = root;
        s = tmp;
    }
    
    return root;
}
void unionSet(int x, int y)
{
    pre[find(y)] = find(x);
}

struct Point
{
    int x, y;
}P[MAXN];
vector<int> S;
double dis(Point a, Point b)
{
    return sqrt(double(a.x-b.x)*(a.x-b.x)+double(a.y-b.y)*(a.y-b.y));
}

int main()
{
    int N;
    double D;
    scanf("%d%lf", &N, &D);
    for(int i = 1;i <= N;++i)   scanf("%d%d", &P[i].x, &P[i].y);
    for(int i = 1;i <= N;++i)   pre[i] = i;
    char ch[2];
    while (~scanf("%s", ch))
    {
        if(ch[0] == 'O'){
            int t;
            scanf("%d", &t);
            S.push_back(t);
            for(int i = 0;i < S.size();++i){
                if(pre[S[i]] != t && dis(P[t], P[S[i]]) <= D)
                    unionSet(t, S[i]);
            }
        }
        else if(ch[0] == 'S'){
            int x, y;
            scanf("%d%d", &x, &y);
            if(find(x) == find(y))
                printf("SUCCESS\n");
            else 
                printf("FAIL\n");
        }
    }
    
    return 0;
}

