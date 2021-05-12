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
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int MAXN = 210;
const int MAXM = 100010;
int dp[MAXN][MAXN] = {0}, M[MAXN][MAXN] = {0};
int s[MAXN];
int main()
{
    int n, k, m;
    scanf("%d %d %d", &n, &k, &m);
    for(int i = 1;i <= m;++i) scanf("%d", &s[i]);
    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= n;++j) scanf("%d", &M[i][j]);
    int ans = 0;
    for(int i = 1;i <= m;++i)
        for(int j = 0;j <= k;++j){
            if(i - j < 0) continue;
            for(int d = 0;d <= j;++d){
                int pre = i - d - 1;
                if(pre < 0) break;
                dp[i][j] = max(dp[i][j], dp[pre][j-d] + M[s[pre]][s[i]]);
                ans = max(ans, dp[i][j]);
            }
        }
    printf("%d\n", ans);
    return 0;
}