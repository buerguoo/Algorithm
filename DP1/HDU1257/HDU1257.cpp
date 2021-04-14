/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:46ms
memory:1756kb

Data:2021-04-14 16:58:29
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
const int MAXN = 10010;
const int MAXM = 100010;
int dp[MAXN], a[MAXN];
int main()
{
    int n;
    while(~scanf("%d", &n)){
        for(int i = 1;i <= n;++i)   scanf("%d", &a[i]);
        dp[0] = 0;
        for(int i = 1;i <= n;++i){
            dp[i] = 0;
            for(int j = 0;j < i;++j)
                if(a[i] > a[j])
                    dp[i] = max(dp[i], dp[j]+2);
        }
        int ans = 0;
        for(int i = 1;i <= n;++i)
            ans = max(ans, dp[i]);
        printf("%d\n", ans);
    }
    return 0;
}