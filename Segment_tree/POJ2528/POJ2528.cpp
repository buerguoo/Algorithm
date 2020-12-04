/*
Author:buerguoo
Time:79ms
memory:1008KB

Data:2020-11-23 23:08:11
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;
const int MAXN = 20010;
int li[MAXN], ri[MAXN];
int sum[MAXN<<4], ls[MAXN<<3];
bool vis[MAXN<<3];
void PushDown(int rt)
{
    if(sum[rt]){
        sum[rt<<1] = sum[rt<<1|1] = sum[rt];
        sum[rt] = 0;
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
int ans;
void Query(int L, int R, int l, int r, int rt)
{
    if(!vis[sum[rt]] && sum[rt]){
        ans++;
        vis[sum[rt]] = true;
        return ;
    }
    if(l == r)  return ;
    PushDown(rt);
    int m = (l+r)>>1;
    if(L <= m)  Query(L, R, l, m, rt<<1);
    if(R > m)   Query(L, R, m+1, r, rt<<1|1);
}
int main()
{
    //ifstream infile;
    //infile.open("D://input.txt", ios::in);
    int T;
    scanf("%d", &T);
    //infile >> T;
    while(T--){
        int n;
        //infile >> n;
        memset(vis, false, sizeof(vis));
        //memset(sum, 0, sizeof(sum));
        scanf("%d", &n);
        int tol = 0;
        for(int i = 0;i < n;++i){
            scanf("%d%d", &li[i], &ri[i]);
            //infile >> li[i] >> ri[i];
            ls[tol++] = li[i];
            ls[tol++] = ri[i];
        }
        sort(ls, ls+tol);
        tol = unique(ls, ls+tol) - ls;
        int tmp = tol;
        for(int i = 1;i < tol;i++)
            if(ls[i] - ls[i-1] > 1)
                ls[tmp++] = (ls[i]+ls[i-1])>>1;
        tol = tmp;
        sort(ls, ls+tol);
        for(int i = 0;i < n;++i){
            int L = lower_bound(ls, ls+tol, li[i]) - ls;
            int R = lower_bound(ls, ls+tol, ri[i]) - ls;
            //printf("L = %d R = %d\n", L, R);
            Update(L+1, R+1, i+1, 1, tol, 1);
        }
        ans = 0;
        Query(1, tol, 1, tol, 1);
        printf("%d\n", ans);
    }
    //infile.close();
    return 0;
}