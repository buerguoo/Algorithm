/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:15ms
memory:1752kb

Data:2021-04-12 23:12:27
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
const int MAXN = 2010;
const int MAXM = 100010;
int dp[MAXN];
int d[MAXN], s[MAXN];
int main()
{
    int Case;
    int K;
    scanf("%d", &Case);
    while(Case--){
        scanf("%d", &K);
        for(int i = 1;i <= K;++i) scanf("%d", &s[i]);
        for(int i = 1;i < K;++i) scanf("%d", &d[i]);
        dp[0] = 0;
        dp[1] = s[1];
        for(int i = 2;i <= K;++i)
            dp[i] = min(dp[i-2]+d[i-1], dp[i-1]+s[i]);
        int hour = 8, minute = 0, second = 0;
        second += dp[K] % 60;
        minute += (dp[K] / 60) % 60;
        hour += dp[K] / 60 / 60 % 12;
        printf("%02d:%02d:%02d", hour, minute, second);
        if(dp[K]/60/60/12 > 0) printf(" pm\n");
        else printf(" am\n");
    }
    return 0;
}