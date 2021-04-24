
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1005;
int dp[maxn][maxn];
char a[maxn][maxn];
int main()
{
    int n;
    while(~scanf("%d",&n),n)
    {
        memset(dp,0,sizeof(dp));
        for(int i = 0; i < n; i++)
            scanf("%s",&a[i]);
        int ans = 1;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n ; j++)
            {
                if(i == 0 || j == n-1)    //以往我都是在前面for循环给dp赋值，看了kuangbin的博客，又学了一招
                {
                    dp[i][j] = 1;
                    continue;
                }
                int ti = i, tj = j;
                while(ti >= 0 && tj <= n - 1 && a[ti][j] == a[i][tj] )   //这里有个细节，就是如果不相同ti也已经--了，所以ti总是比相同的长度少1，所以下面可
                {                                                       //以直接i-ti，如果ti代表相同的长度应该是i-ti+1
                    tj++;
                    ti--;
                }
                ti = i - ti;
                if(dp[i-1][j+1]+1 <= ti)  dp[i][j] = dp[i-1][j+1] + 1;
                else dp[i][j] = ti;
                ans = max(ans,dp[i][j]);
            }
        printf("%d\n",ans);
    }
    return 0;
}