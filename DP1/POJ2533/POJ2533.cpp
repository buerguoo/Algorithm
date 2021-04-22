/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:0ms
memory:112Kb

Data:2021-04-22 22:50:38
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
int a[MAXN], dp[MAXN];
int main()
{
    int n;
    while(~scanf("%d", &n)){
        for(int i = 1;i <= n;++i) scanf("%d", &a[i]);
        dp[0] = 0;
        for(int i = 1;i <= n;++i){
            dp[i] = 1;
            for(int j = 1;j < i;++j)
                if(a[i] > a[j])
                    dp[i] = max(dp[i], dp[j]+1);
        }
        int Max = 0;
        for(int i = 1;i <= n;++i)
            Max = max(Max, dp[i]);
        printf("%d\n", Max);
    }
    return 0;
}
