/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:
memory:

Data:
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
const int MAXN = 25;
const int MAXM = 210;
int dp[MAXN], dp1[MAXN];
int p[MAXM], d[MAXM];
int pre[MAXM];
void output(int x)
{
    if(!x) return ;
    output(pre[x]);
    printf("%d ", x);
}
int main()
{
    int n, m;
    int Case = 0;
    while(~scanf("%d %d", &n, &m) && (n || m)){
        for(int i = 1;i <= n;++i) scanf("%d %d", &p[i], &d[i]);
        dp[1] = d[1], dp1[1] = p[1];
        memset(pre, 0, sizeof(pre));
        for(int i = 1;i <= n;++i){
            for(int j = m;j > 1;--j)
                if(abs(dp[j-1]-dp1[j-1]) > abs(dp[j-1]+d[i]-dp1[j-1]-p[i])){
                    dp[j] = dp[j-1] + d[i];
                    dp1[j] = dp1[j-1] + p[i];
                    //pre[j] = i;
                }
                if(abs(dp[1]-dp1[1]) > abs(d[i]-p[i])){
                    dp[1] = d[i];
                    dp1[1] = p[i];
                }
        }
        printf("sum = %d %d\n", dp1[m], dp[m]);
    }
    return 0;
}