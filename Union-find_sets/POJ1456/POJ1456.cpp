#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <algorithm>
using namespace std;
//并查集
const int MAXN = 10010;
int F[MAXN];
int find(int x)
{
    if(F[x] == -1)  return x;
    int tmp = find(F[x]);
    return F[x] = tmp;  
}
struct Staff
{
    int c, d;
    bool operator < (const Staff &r) const{
        return c > r.c;
    }
}S[MAXN];
int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        int MaxDay = 0;
        memset(F, -1, sizeof(F));
        for(int i = 0;i < n;++i){
            scanf("%d%d", &S[i].c, &S[i].d);
            //if(S[i].d > MaxDay) MaxDay = S[i].d;
        }
        sort(S, S+n);
        int ans = 0;
        for(int i = 0;i < n;++i){
            int d = find(S[i].d);
            if(d > 0){
                F[d] = d-1;
                ans += S[i].c;
            }
        }
        printf("%d\n", ans);
    }
}