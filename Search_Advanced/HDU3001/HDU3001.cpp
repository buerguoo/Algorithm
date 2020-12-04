#include <iostream>
#include <algorithm>
using namespace std;
const int INF = 99999999;
int three[11],digit[60000][11];
int dp[60000][11],tu[11][11];
int n,m;

//采用DP+三进制

void Init()
{
    three[0] = 1;
    for(int i = 1;i < 11;++i)
        three[i] = three[i-1] * 3;
    for(int i = 0;i < three[10];++i)
        {
            int tp = i;
            for(int j = 0;j < 11;++j)
            {
                digit[i][j] = tp%3;
                tp /= 3;
            }
        }
            
}

int main()
{
    Init();
    while(~scanf("%d%d",&n,&m))
    {
        for(int i = 0;i < three[n];++i)
            for(int j = 0;j < 11;++j)  
                dp[i][j] = INF;
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j)
                tu[i][j] = INF;
        for(int i = 0;i < n;++i)
            dp[three[i]][i] = 0;
        
        while(m--)
        {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            tu[a-1][b-1] = tu[b-1][a-1] = min(tu[a-1][b-1],c);
        }
        int ans = INF;

        for(int i = 0;i < three[n];++i)
        {
            bool flag = 1;
            for(int j = 0;j < n;++j)
            {
                if(!digit[i][j])    flag = 0;
                if(dp[i][j] != INF)
                {
                    for(int k = 0;k < n;++k)
                        if(tu[j][k]!=INF && digit[i][k] != 2)
                            dp[i+three[k]][k] = min(dp[i+three[k]][k], dp[i][j]+tu[j][k]);
                }
            }

            if(flag)
                for(int j = 0;j < n;++j)
                    ans = min(ans, dp[i][j]);
        }
        
        if(ans == INF)
            printf("-1\n");
        else 
            printf("%d\n",ans);
        
    }
}