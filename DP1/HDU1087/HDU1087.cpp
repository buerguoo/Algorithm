/*
Time limit:
Memory limit:

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
const int MAXN = 1010;
const int MAXM = 100010;
int dp[MAXN], a[MAXN];
int main()
{
    int n;
    while(~scanf("%d", &n) && n){
        for(int i = 1;i <= n;++i) scanf("%d", &a[i]);
        dp[0] = 0;
        for(int i = 1;i <= n;++i){
            dp[i] = a[i];
            for(int j = 1;j < i;++j)
                if(a[i] > a[j])
                    dp[i] = max(dp[i], dp[j]+a[i]);
        }
        int ans = 0;
        for(int i = 1;i <= n;++i) ans = max(ans, dp[i]);
        printf("%d\n", ans);
    }
    return 0;
}