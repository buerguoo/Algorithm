/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:46ms
memory:1772kb

Data:2021-04-12 22:21:33
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
const int MAXN = 510;
const int MAXM = 10010;
int w[MAXN], c[MAXN];
int dp[MAXM];
int main()
{
    int Case;
    int w1, w2, n;
    int W;
    scanf("%d", &Case);
    while(Case--){
       scanf("%d %d", &w1, &w2);
       scanf("%d", &n);
       for(int i = 1;i <= n;++i) scanf("%d %d", &c[i], &w[i]);
       W = w2 - w1;
       dp[0] = 0;
        for(int j = 1;j <= W;++j)    dp[j] = INF;
       for(int i = 1;i <= n;++i){
            for(int j = w[i];j <= W;++j)
                dp[j] = min(dp[j], dp[j-w[i]]+c[i]);
       }
       if(W == 0 || dp[W] == INF){
           printf("This is impossible.\n");
           continue;
       }
       printf("The minimum amount of money in the piggy-bank is %d.\n", dp[W]);
    }
    return 0;
}
