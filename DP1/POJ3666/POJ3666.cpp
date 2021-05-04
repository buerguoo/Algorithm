/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:47ms
memory:144kB

Data:2021-05-04 23:23:54
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
int A[MAXN], B[MAXN];
int dp[2][MAXN];
int main()
{
    int N;
    while(~scanf("%d", &N)){
        for(int i = 0;i < N;++i)    scanf("%d", &A[i]);
        memcpy(B, A, N*sizeof(int));
        sort(B, B+N);
        for(int i = 0;i < N;++i)    dp[0][i] = abs(A[0]-B[i]);
        int pre, cur;
        int pre_min_cost;
        for(int i = 1;i < N;++i){
            cur = i & 0x1;
            pre = (i-1) & 0x1;
            pre_min_cost = dp[pre][0];
            for(int j = 0;j < N;++j){
                pre_min_cost = min(pre_min_cost, dp[pre][j]);
                dp[cur][j] = pre_min_cost + abs(A[i] - B[j]);
            }
        }
        cur = (N-1) & 0x1;
        printf("%d\n", *min_element(dp[cur], dp[cur]+N));
    }
    return 0;
}
