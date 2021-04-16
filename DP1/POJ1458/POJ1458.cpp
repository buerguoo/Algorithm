/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:1084Kb
memory:0ms

Data:2021-04-16 23:56:38
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
const int MAXN = 500;
const int MAXM = 100010;
int dp[MAXN][MAXN];
char A[MAXN], B[MAXN];
int main()
{
    while(~scanf("%s %s", A, B)){
        int len1 = strlen(A);
        int len2 = strlen(B);
        memset(dp, 0, sizeof(dp));
        for(int i = 1;i <= len1;++i)
            for(int j = 1;j <= len2;++j){
                if(A[i-1] == B[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        printf("%d\n", dp[len1][len2]);
    }
    return 0;
}