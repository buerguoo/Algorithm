/*
Author:buerguoo
name:HDU1754
Time:780ms
memory:4588KB

Data:2020-11-22 21:48:43
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
using namespace std;
//并查集
const int MAXN = 2e5+10;
int A[MAXN];
int sum[MAXN<<2];//懒得改了
void Update(int L, int C, int l, int r, int rt)
{
    A[L] = C;
}
int Query(int L, int R, int l, int r, int rt)
{
    if(L <= l && R >= r)
        return sum[rt];
    int Max = 0;
    int m = (l+r)>>1;
    if(L <= m)  Max = max(Query(L, R, l, m, rt<<1), Max);
    if(R > m)   Max = max(Query(L, R, m+1, r, rt<<1|1), Max);

    return  Max; 
}
int main()
{
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        for(int i = 1;i <= n;++i)
            scanf("%d", &A[i]);
        char o[2];
        int a, b;
        build(1, n, 1);
        for(int i = 0;i < m;++i){
            scanf("%s%d%d", o, &a, &b);
        if(o[0] == 'Q')    printf("%d\n", Query(a, b, 1, n, 1));
        else if(o[0] == 'U')   Update(a, b, 1, n, 1);
        }
    }

    return 0;
}