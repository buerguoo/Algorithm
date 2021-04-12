/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:15ms
memory:2112kb

Data:2021-04-12 21:45:37
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
const int MAXN = 15;
const int MAXM = 1<<15;
int dp[MAXM], pre[MAXM], T[MAXM];
struct homework{
    int deadline, duration;
    char name[120];
}H[MAXN];
void output(int x)
{
    if(x == 0) return ;
    output(x^(1<<pre[x]));
    printf("%s\n", H[pre[x]].name);
}
int main()
{
    int Case, n;
    scanf("%d", &Case);
    while(Case--){
        scanf("%d", &n);
        for(int i = 0;i < n;++i){
            scanf("%s", H[i].name);
            scanf("%d %d", &H[i].deadline, &H[i].duration);
        }
        dp[0] = 0;
        memset(pre, 0, sizeof(pre));
        for(int i = 1;i < (1<<n);++i){
            dp[i] = 1<<28;
            for(int j = n-1;j >= 0;--j){
                if(!(i&(1<<j))) continue;
                int tt = i^(1<<j);
                int reduce = -H[j].deadline + T[tt] + H[j].duration;
                if(reduce < 0) reduce = 0;
                if(dp[tt] + reduce < dp[i]){
                    dp[i] = dp[tt] + reduce;
                    T[i] = T[tt] + H[j].duration;
                    pre[i] = j;
                }
            }
        }
        printf("%d\n", dp[(1<<n)-1]);
        output((1<<n)-1);
    }
    return 0;
}