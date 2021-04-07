/*
Time limit:1000ms
Memory limit:32768Kb

Author:buerguoo
Time:390ms
memory:2932kB

Data:2021-04-07 23:03:42
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
const int MAXN = 1000100;
const int MAXM = 100010;
int dp[MAXN], dp2[MAXN], a[MAXN];
int main()
{
    int n, m;
    int tmp = 0;
    while(~scanf("%d %d", &m, &n)){
        for(int i = 1;i <= n;++i){
            scanf("%d", &a[i]);
            dp[i] = 0;
            dp2[i] = 0;
        }   
        for(int i = 1;i <= m;++i){
            tmp = -INF;
            for(int j = i;j <= n;++j){
                dp[j] = max(dp[j-1]+a[j], dp2[j-1]+a[j]);
                dp2[j-1] = tmp;                
                tmp = max(dp[j], tmp);
            }
        }
        printf("%d\n", tmp);
    }
    return 0;
}