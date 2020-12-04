/*
Author:buerguoo
name:HDU1166
Time:TLE
memory:

Data:2020-11-22 17:41:34
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
const int MAXN = 50010;
int A[MAXN], n, N;
void Update(int L, int C)
{
    A[L] += C;
}
int Query(int L, int R)
{
    int ans = 0;
    for(int i = L;i <= R;++i)
        ans += A[i];

    return ans;
}
int main()
{
    int T, t=0;
    scanf("%d", &T);
    while(t++ < T){
        scanf("%d", &n);
        for(int i = 1;i <= n;++i)
            scanf("%d", &A[i]);
        printf("Case %d:\n", t);
        char order[10];
        scanf("%s", order);
        while(order[0] != 'E'){
            int L, R, C;
            switch (order[0])
            {
            case 'Q':
                scanf("%d%d", &L, &R);
                printf("%d\n", Query(L, R));
                break;
            case 'A':
                scanf("%d%d", &L, &C);
                Update(L, C); 
                break;
            case 'S':
                scanf("%d%d", &L, &C);
                Update(L, -C);
                break;
            }
            scanf("%s", order);
        }
    }
    return 0;
}
