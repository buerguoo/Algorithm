/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:16ms
memory:108kB

Data:2021-04-25 23:35:03
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
int dp[MAXN];
struct interv{
    int a, b;
    int e;
    bool operator<(const interv &r) const{
        return a < r.a;
    }
}I[MAXN];
int main()
{
    int n, m, R;
    while(~scanf("%d %d %d", &n, &m, &R)){
        for(int i = 1;i <= m;++i)   scanf("%d %d %d", &I[i].a, &I[i].b, &I[i].e);
        sort(I+1, I+1+m);
        I[0].a = I[0].b = -R;
        I[0].e = 0;
        dp[0] = 0;
        int Max = 0;
        for(int i = 1;i <= m;++i){
            dp[i] = 0;
            for(int j = 0;j < i;++j)
                if(I[j].b + R <= I[i].a)
                    dp[i] = max(dp[i], dp[j] + I[i].e);
            Max = max(Max, dp[i]);
        }
        printf("%d\n", Max);
    }
    return 0;
}