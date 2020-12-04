/*
Author:buerguoo
Time:748ms
memory:4736KB

Data:2020-11-24 20:44:41
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
const int MAXN = 1e5+5;
int A[MAXN];
int sum[MAXN<<2], add[MAXN<<2];
void PushUp(int rt){sum[rt] = sum[rt<<1] + sum[rt<<1|1];}
void build(int l, int r, int rt)
{
    if(l == r){
        sum[rt] = A[l];
        return ;
    }
    int m = (l+r)>>1;
    build(l, m, rt<<1);
    build(m+1, r, rt<<1|1);
    PushUp(rt);
}
void PushDown(int rt, int ln, int rn)
{
    if(add[rt]){
        add[rt<<1] = add[rt];
        add[rt<<1|1] = add[rt];
        sum[rt<<1] = add[rt]*ln;
        sum[rt<<1|1] = add[rt]*rn;

        add[rt] = 0;
    }
}
void Update(int L, int R, int C, int l, int r, int rt)
{
    if(L <= l && R >= r){
        sum[rt] = C*(r-l+1);
        add[rt] = C;
       // printf("%d\n", add[rt]);
        return ;
    }
    int m = (l+r)>>1;
    PushDown(rt, m-l+1, r-m);
    if(L <= m)  Update(L, R, C, l, m, rt<<1);
    if(R > m)   Update(L, R, C, m+1, r, rt<<1|1);
    PushUp(rt);
}
int main()
{
  // ifstream infile;
    //infile.open("D://input.txt", ios::in);
    int T, t = 0;
   //infile >> T;
    scanf("%d", &T);
    while(t++ < T){
        int N, Q;
        scanf("%d", &N);
        memset(add, 0, sizeof(add));
        //infile >> N;
        for(int i = 1;i <= N;++i)    A[i] = 1;
        scanf("%d", &Q);
        build(1, N, 1);
        for(int i = 0;i < Q;++i){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            Update(a, b, c, 1, N, 1);
        }
        printf("Case %d: The total value of the hook is %d.\n", t, sum[1]);
    }
    return 0;
}