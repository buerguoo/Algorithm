
/*
Author:buerguoo
Time:32ms
memory:592KB

Data:2020/11/24 23:44:00
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
#include <set>
using namespace std;
const int MAXN = 8010;
int sum[MAXN<<2];
int ans[MAXN];
int tmp;
void PushDown(int rt){
    if(sum[rt]!=-1){
        sum[rt<<1] = sum[rt<<1|1] = sum[rt];
        sum[rt] = -1;
    } 
}
void Update(int L, int R, int C, int l, int r, int rt)
{
    if(L <= l && R >= r){
        sum[rt] = C;
        return ;
    }
    PushDown(rt);
    int m = (l+r)>>1;
    if(L <= m)  Update(L, R, C, l, m, rt<<1);
    if(R > m)   Update(L, R, C, m+1, r, rt<<1|1);
}
void Query(int L, int R, int l, int r, int rt)
{
    if(l == r){
        if(sum[rt]!=-1 && sum[rt]!=tmp) ans[sum[rt]]++;
        tmp = sum[rt];
        return ;
    }
    PushDown(rt);
    int m = (l+r)>>1;
    if(L <= m)  Query(L, R, l, m, rt<<1);
    if(R > m)   Query(L, R, m+1, r, rt<<1|1);
}
int main()
{
    int n;
    //
    while(~scanf("%d", &n)){
        int x1, x2, c;
        tmp = -1;
        memset(sum, -1, sizeof(sum));
        memset(ans, 0, sizeof(ans));
        for(int i = 0;i < n;++i){
            scanf("%d%d%d", &x1, &x2, &c);
            if(x1<x2)Update(x1+1, x2, c, 1, 8000, 1);
        }
        Query(1, 8000, 1, 8000, 1);
        for(int i = 0;i <= 8000;i++)   if(ans[i])
            printf("%d %d\n", i, ans[i]);
        printf("\n");
    }
    return 0;
}