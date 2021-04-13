/*
Time limit:1000ms
Memory limit:32768kb

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
int dp[MAXN], pre[MAXN];
struct mouse{
    int w, p;
    bool operator< (const mouse &a)const{
        return w<a.w;
    }
}mice[MAXN];
void output(int x)
{
    if(!x) return ;
    output(pre[x]);
    printf("%d\n", x);
}
int main()
{
    int n = 1;
    while(~scanf("%d %d", &mice[n].w, &mice[n].p), n++){
        if(n == 10) break;
    }
        
        sort(mice+1, mice+n);
        mice[0].p = 0, mice[0].w = 0;
        dp[0] = 0;
        for(int i = 1;i <= n;++i)
            for(int j = 0;j < i;++j)
                if(mice[i].w > mice[j].w && mice[i].p < mice[j].p){
                    dp[i] = dp[j] + 1;
                    pre[i] = j;
                }
        int k = -1, Max = 0;
        for(int i = 1;i <= n;++i)
            if(Max < dp[i]){
                Max = dp[i];
                k = i;
            }
        printf("%d\n", Max);
        output(k);
        
    return 0;
}